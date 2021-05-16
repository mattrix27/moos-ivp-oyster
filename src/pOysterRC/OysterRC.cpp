#include "MBUtils.h"

#include "OysterRC.h"

using namespace std;

OysterRC::OysterRC()
{
    m_debugMode = false;
    m_safety = "UP";
    m_flip = "UP";
    m_reset = "UP";
    m_start = "UP";
  
    m_RCOutVal = "";
    m_RCOutName = "RC_COMMAND";
    m_RCOutFlip = "RC_FLIP";
    m_RCOutReset = "RC_RESET";
    m_RCOutStart = "RC_START";
    m_NMEAOut    = "NMEA_TO_SEND";
    m_dbl_thres = 3*pow(10,-5); 
}

bool OysterRC::OnNewMail(MOOSMSG_LIST &NewMail)
{
    AppCastingMOOSApp::OnNewMail(NewMail);

    MOOSMSG_LIST::iterator p;
    for (p=NewMail.begin(); p!=NewMail.end(); ++p) {
      CMOOSMsg & rMsg = *p;
      string msgKey = rMsg.GetKey();
      
      // Check if incoming RANGE message exists in the axis map
        //      - Double value means it's a single value
        //      - String value means it's a value and a dependent value
	  if (m_ranges.count(msgKey)) {
        if (rMsg.IsDouble())    m_ranges[msgKey].SetInputValue(rMsg.GetDouble());
        else                    m_ranges[msgKey].SetInputValues(rMsg.GetString()); }

      // Check if incoming TRIGGER message exists in the button map
      //      - Handle double or string messages
      else if (m_triggers.count(msgKey)) {
    	if (rMsg.IsDouble())    m_triggers[msgKey].StoreValueThenPublish(rMsg.GetDouble());
    	else                    m_triggers[msgKey].StoreValueThenPublish(rMsg.GetString()); } 
    }

    return UpdateMOOSVariables(NewMail);
}

bool OysterRC::Iterate()
{
    AppCastingMOOSApp::Iterate();

    PublishOutput();

    AppCastingMOOSApp::PostReport();
    return true;
}

void OysterRC::PublishOutput()
{

    map<std::string, mapTrigger>::iterator itTrig = m_triggers.begin();
    for (; itTrig != m_triggers.end(); ++itTrig) {
        mapTrigger mb = itTrig->second;
        if (mb.GetOut() == "SAFETY") {
            // cout << "AHHHHHHHHHHHHHHHH" << endl;
            m_safety = mb.GetLastValue();
        }
        if (mb.GetOut() == "RC_FLIP") {
            m_flip = mb.GetLastValue();
        }
        if (mb.GetOut() == "RESET") {
            m_reset = mb.GetLastValue();
        }
        if (mb.GetOut() == "START") {
            m_start = mb.GetLastValue();
        }
    }

    if (m_safety == "DOWN") {
        // cout << "DOWN DOWN DOWN DOWN DOWN" << endl;
        if (m_flip == "DOWN") {
            m_Comms.Notify(m_NMEAOut, "FLIP");
        }
        else if (m_reset == "DOWN") {
            m_Comms.Notify(m_NMEAOut, "RESET");
        }
        else if (m_start == "DOWN") {
            m_Comms.Notify(m_NMEAOut, "START");
        }
        

        // Cycle through RANGE definitions
        map<string, mapRange>::iterator it = m_ranges.begin();
        for (; it != m_ranges.end(); ++it) {
            mapRange* r = &it->second;
            if (r->GetPublishName() == "X_DIR") {
                m_x = r->GetNormalizedValue();
            } 
            if (r->GetPublishName() == "Y_DIR") {
                m_y = r->GetNormalizedValue()*-1;
            }
        }

        m_magnitude = min (pow((pow(m_x,2) + pow(m_y,2)), 0.5), 1.0);

        if (m_magnitude <= m_dbl_thres) {
            m_angle = 0.0;
            m_magnitude = 0.0;
        } 

        m_angle = atan2 (m_x, m_y) * 180 / M_PI;
        
        if (m_angle <= 90 && m_angle >= -90) {
            m_forward = true;
        } 
        else if (m_angle > 90) {
            m_forward = false;
            m_angle = abs (m_angle-180.0);
        } 
        else if (m_angle < -90) {
            m_forward = false;
            m_angle = -(180+m_angle);            
        } 

        // cout << "M: " << m_magnitude  << " X: " << m_x << " Y: " << m_y << " ANGLE: " << m_angle << endl;
        PublishRC();
    }
}

void OysterRC::PublishRC()
{
    double left = m_magnitude;
    double right = m_magnitude;
    if (m_angle >= 0 && m_angle <= 45) {
        right -= ((m_angle/45))*m_magnitude;
    }
    else if (m_angle > 45) {
        right = -((m_angle-45)/45)*m_magnitude;
    }
    else if (m_angle < 0 && m_angle >= -45) {
        left -= ((abs(m_angle)/45))*m_magnitude;
    }
    else if (m_angle < -45) {
        left = -(((abs(m_angle)-45))/45)*m_magnitude;
    }

    if (!m_forward) {
        right *= -1;
        left *= -1;
    }
    m_RCOutVal = "LEFT=" + to_string(left) + "," + "RIGHT=" + to_string(right);

    m_Comms.Notify(m_RCOutName, m_RCOutVal);
}



bool OysterRC::OnConnectToServer()
{
    return true;
}

bool OysterRC::RegisterForMOOSMessages()
{
    AppCastingMOOSApp::RegisterVariables();

    map<string, mapRange>::iterator it = m_ranges.begin();

    // Register for axis input messages
    for (; it != m_ranges.end(); ++it)
        m_Comms.Register(it->second.GetSubscribeName(), 0.0);

    // Button input messages are registered in the mapButton class

    return RegisterMOOSVariables();
}

bool OysterRC::OnStartUp()
{
    AppCastingMOOSApp::OnStartUp();

    STRING_LIST sParams;
    if (!m_MissionReader.GetConfiguration(GetAppName(), sParams))
        reportConfigWarning("No config block found for " + GetAppName());

    bool bHandled = true;
    STRING_LIST::iterator p;
    for (p = sParams.begin(); p != sParams.end(); p++) {
        string orig     = *p;
        string line     = *p;
        string param    = toupper(biteStringX(line, '='));
        string value    = line;

        if (param == "RANGE")
            bHandled = SetParam_RANGE(value);
        else if (param == "TRIGGER")
            bHandled = SetParam_TRIGGER(value);
        else if (param == "DEBUG_MODE") {
            m_debugMode =  (toupper(value) == "TRUE");
            bHandled = true; }
        else if (param == "DEBUG_AXIS0")
            bHandled = SetParam_DEBUG_AXIS0(value);
        else if (param == "DEBUG_AXIS1")
            bHandled = SetParam_DEBUG_AXIS1(value);
        else if (param == "OUT_MSG")
            m_RCOutName = value;
        else
            reportUnhandledConfigWarning(orig); }

    RegisterForMOOSMessages();
    RegisterVariables();

    // OnStartup() must always return true
    //    - Or else it will quit during launch and appCast info will be unavailable
    return true;
}

// RANGE = in_msg=x, in_min=0.0, in_max=0.0, out_msg=y, out_min=0.0, out_max=0.0
                // in_msg     Message name for incoming range values
                // in_min     Minimum value on the input range
                // in_max     Maximum value on the input range
                // out_msg    Mapped value published to this message
                // out_min    Minimum value input range is mapped to
                // out_max    Maximum value input range is mapped to
// Example:
// RANGE = in_msg=JOY_AXIS_2, in_min=-1000, in_max=1000, out_msg=DESIRED_RUDDER, out_min=-40, out_max=40
bool OysterRC::SetParam_RANGE(string sVal)
{
	if (sVal.empty()) {
		reportConfigWarning("RANGE cannot not be blank.");
		return true; }
	mapRange ma = mapRange(sVal);
	if (ma.IsValid())   m_ranges[ma.GetSubscribeName()] = ma;
	else                reportConfigWarning("Error: " + ma.GetErrorString());
    return true;
}

// TRIGGER = in_msg=w, trigger=x, out_msg=y, out_val=z
                  // in_msg     Message name for incoming switch value
                  // trigger    When in_msg contents change to match this trigger,
                  //              the out_msg will be published.
                  //              String/numeric agnostic.
                  // out_msg    Message name for resulting publication.
                  // out_val    Resulting publication posts this value.
                  //              If value is a numeric (within '+-.01234567889'),
                  //              published message is a double. Otherwise, a
                  //              string is published. To publish a numeric as a
                  //              string, put the number in quotes.");
   // Examples:
   //    TRIGGER  = JOY_BUTTON_4, 1, ALL_STOP=true
   //    TRIGGER  = JOY_BUTTON_7, off, VEHICLE_NUMBER=\"3\"
bool OysterRC::SetParam_TRIGGER(string sVal)
{
	if (sVal.empty()) {
		reportConfigWarning("SWITCH cannot not be blank.");
		return true; }

	mapTrigger mb = mapTrigger(&m_Comms, sVal);
	if (mb.IsValid())   m_triggers[mb.GetKey()] = mb;
	else                reportConfigWarning("Error: " + mb.GetError());
	return true;
}

bool OysterRC::SetParam_DEBUG_AXIS0(string sVal)
{
    if (sVal.empty()) {
        reportConfigWarning("DEBUG_AXIS0 cannot not be blank.");
        return true; }
    m_strDebug0 = sVal;
    return true;
}

bool OysterRC::SetParam_DEBUG_AXIS1(string sVal)
{
    if (sVal.empty()) {
        reportConfigWarning("DEBUG_AXIS1 cannot not be blank.");
        return true; }
    m_strDebug1 = sVal;
    return true;
}

bool OysterRC::buildReport()
{
    m_msgs << "FLIP: " << m_flip << endl;
    m_msgs << "DRIVE COMMMAND: " << m_RCOutVal << endl;

    return true;
}

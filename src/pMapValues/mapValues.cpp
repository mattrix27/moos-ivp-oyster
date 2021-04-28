/*
 * mapValues.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: Alon Yaari
 */

#include "MBUtils.h"

#include "mapValues.h"

using namespace std;

mapValues::mapValues()
{
    m_debugMode = false;
}

bool mapValues::OnNewMail(MOOSMSG_LIST &NewMail)
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
			else                    m_triggers[msgKey].StoreValueThenPublish(rMsg.GetString()); } }

    return UpdateMOOSVariables(NewMail);
}

bool mapValues::Iterate()
{
    AppCastingMOOSApp::Iterate();

    PublishOutput();

    AppCastingMOOSApp::PostReport();
    return true;
}

void mapValues::PublishOutput()
{
    // Cycle through RANGE definitions
    map<string, mapRange>::iterator it = m_ranges.begin();
    for (; it != m_ranges.end(); ++it) {
        mapRange* r = &it->second;

        // Set the current trigger value when necessary
        if (r->HasTrigger()) {
            string triggerName = r->GetTriggerMessageName();
            string triggerVal = "No published message for " + triggerName;
            if (m_triggers.count(triggerName))
                triggerVal = m_triggers[triggerName].GetLastValue();
            r->SetTriggerValue(triggerVal); }
        r->ConditionalPublish(&m_Comms); }

    if (m_debugMode) {
        stringstream strCircle;
        strCircle << "x=0,y=0,radius=100.0,active=true,vertex_size=0,edge_color=white,edge_size=2,label=strcircle";
        m_Comms.Notify("VIEW_CIRCLE", strCircle.str());

        stringstream strFullBox;
        strFullBox << "pts={100,100:100,-100:-100,-100:-100,100},active=true,vertex_size=0,edge_color=white,edge_size=2,label=fullbox";
        m_Comms.Notify("VIEW_POLYGON", strFullBox.str());

        { stringstream strDeadBox;
        double tb = m_ranges[m_strDebug0].GetDeadZone() * 100.0;
        double lr = m_ranges[m_strDebug1].GetDeadZone() * 100.0;
        strDeadBox << "pts={";
        strDeadBox <<        lr << ","  << tb << ":";
        strDeadBox <<        lr << ",-" << tb << ":";
        strDeadBox << "-" << lr << ",-" << tb << ":";
        strDeadBox << "-" << lr << "," << tb;
        strDeadBox << "},active=true,label=deadZone,vertex_size=0,edge_color=gray,edge_size=2";
        m_Comms.Notify("VIEW_POLYGON", strDeadBox.str()); }

        { stringstream strSatBox;
        double tb = 100.0 - m_ranges[m_strDebug0].GetSaturation() * 100.0;
        double lr = 100.0 - m_ranges[m_strDebug1].GetSaturation() * 100.0;
        strSatBox << "pts={";
        strSatBox <<        lr << ","  << tb << ":";
        strSatBox <<        lr << ",-" << tb << ":";
        strSatBox << "-" << lr << ",-" << tb << ":";
        strSatBox << "-" << lr << "," << tb;
        strSatBox << "},active=true,label=saturation,vertex_size=0,edge_color=gray,edge_size=2";
        m_Comms.Notify("VIEW_POLYGON", strSatBox.str()); }

        { stringstream strIn;
        strIn << "x="   << m_ranges[m_strDebug0].GetInputValue() * 100.0 / m_ranges[m_strDebug0].GetInMax();
        strIn << ",y="  << m_ranges[m_strDebug1].GetInputValue() * 100.0 / m_ranges[m_strDebug1].GetInMax();
        strIn << ",active=true,label=joyIn,label_color=yellow,vertex_color=yellow,vertex_size=4";
        m_Comms.Notify("VIEW_POINT", strIn.str()); }

        { stringstream strNorm;
        strNorm << "x="   << m_ranges[m_strDebug0].GetNormalizedValue() * 100.0;
        strNorm << ",y="  << m_ranges[m_strDebug1].GetNormalizedValue() * 100.0;
        strNorm << ",active=true,label=joyNorm,label_color=red,vertex_color=red,vertex_size=4";
        m_Comms.Notify("VIEW_POINT", strNorm.str()); }

        { stringstream strOut;
        double xMax = fabs(m_ranges[m_strDebug0].GetOutMax());
        double xMin = fabs(m_ranges[m_strDebug0].GetOutMin());
        double xUse = (xMax > xMin ? xMax : xMin);
        double x = (xUse == 0.0 ? 0.0 :  m_ranges[m_strDebug0].GetOutputMappedValue() * 100.0 / xUse);
        strOut << "x=" << x;
        double yMay = fabs(m_ranges[m_strDebug1].GetOutMax());
        double yMin = fabs(m_ranges[m_strDebug1].GetOutMin());
        double yUse = (yMay > yMin ? yMay : yMin);
        double y = (yUse == 0.0 ? 0.0 :  m_ranges[m_strDebug1].GetOutputMappedValue() * 100.0 / yUse);
        strOut << ",y=" << y;
        strOut << ",active=true,label=joyOut,label_color=green,vertex_color=green,vertex_size=4";
        m_Comms.Notify("VIEW_POINT", strOut.str());

        { stringstream strLabelL, strLabelR, strLabelT, strLabelB;
        strLabelL << "label=" << -1 * yUse << ",x=0"    << ",y=-100" << ",active=true,label_color=green,scale=5,vertex_color=green,vertex_size=0";
        m_Comms.Notify("VIEW_POINT", strLabelL.str());
        strLabelR << "label=" <<      yUse << ",x=0"    << ",y=100"  << ",active=true,label_color=green,vertex_color=green,vertex_size=0";
        m_Comms.Notify("VIEW_POINT", strLabelR.str());
        strLabelT << "label=" << -1 * xUse << ",x=-110" << ",y=0"    << ",active=true,label_color=green,vertex_color=green,vertex_size=0";
        m_Comms.Notify("VIEW_POINT", strLabelT.str());
        strLabelB << "label=" <<      xUse << ",x=110"  << ",y=0"    << ",active=true,label_color=green,vertex_color=green,vertex_size=0";
        m_Comms.Notify("VIEW_POINT", strLabelB.str());
        } } }
}

bool mapValues::OnConnectToServer()
{
    return true;
}

bool mapValues::RegisterForMOOSMessages()
{
    AppCastingMOOSApp::RegisterVariables();

    map<string, mapRange>::iterator it = m_ranges.begin();

    // Register for axis input messages
    for (; it != m_ranges.end(); ++it)
        m_Comms.Register(it->second.GetSubscribeName(), 0.0);

    // Button input messages are registered in the mapButton class

    return RegisterMOOSVariables();
}

bool mapValues::OnStartUp()
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
bool mapValues::SetParam_RANGE(string sVal)
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
bool mapValues::SetParam_TRIGGER(string sVal)
{
	if (sVal.empty()) {
		reportConfigWarning("SWITCH cannot not be blank.");
		return true; }

	mapTrigger mb = mapTrigger(&m_Comms, sVal);
	if (mb.IsValid())   m_triggers[mb.GetKey()] = mb;
	else                reportConfigWarning("Error: " + mb.GetError());
	return true;
}

bool mapValues::SetParam_DEBUG_AXIS0(string sVal)
{
    if (sVal.empty()) {
        reportConfigWarning("DEBUG_AXIS0 cannot not be blank.");
        return true; }
    m_strDebug0 = sVal;
    return true;
}

bool mapValues::SetParam_DEBUG_AXIS1(string sVal)
{
    if (sVal.empty()) {
        reportConfigWarning("DEBUG_AXIS1 cannot not be blank.");
        return true; }
    m_strDebug1 = sVal;
    return true;
}

bool mapValues::buildReport()
{
	int numAxes = m_ranges.size();
    m_msgs << "--- Range definitions ---" << endl;
	map<std::string, mapRange>::iterator itAxes = m_ranges.begin();
    for (; itAxes != m_ranges.end(); ++itAxes) {
    	mapRange ma = itAxes->second;
    	m_msgs << endl << ma.GetAppCastSetupString() << endl; }

	int numButtons = m_triggers.size();
    m_msgs << "--- Trigger definitions ---" << endl;
    map<std::string, mapTrigger>::iterator itButtons = m_triggers.begin();
    for (; itButtons != m_triggers.end(); ++itButtons) {
        m_msgs << endl;
    	mapTrigger mb = itButtons->second;
    	m_msgs <<            " " << mb.GetAppCastMsg() << endl; }

	m_msgs << "--- Live Range Data ---" << endl << endl;
	itAxes = m_ranges.begin();
    for (; itAxes != m_ranges.end(); ++itAxes) {
        mapRange ma = itAxes->second;
        m_msgs << ma.GetAppCastStatusString() << endl; }
    m_msgs << endl;

    m_msgs << "--- Live Trigger Data ---" << endl << endl;
    map<std::string, mapTrigger>::iterator itTrig = m_triggers.begin();
    for (; itTrig != m_triggers.end(); ++itTrig) {
        m_msgs << endl;
        mapTrigger mb = itTrig->second;
        m_msgs << mb.GetAppCastStatusString() << endl;
    }

    return true;
}

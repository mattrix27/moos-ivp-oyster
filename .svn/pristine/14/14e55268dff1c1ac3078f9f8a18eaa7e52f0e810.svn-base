/************************************************************/
/*    NAME: Carter Fendley                                  */
/*    ORGN: MIT                                             */
/*    FILE: AttackCommander.cpp                             */
/*    DATE: August 10th, 2016                               */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "AttackCommander.h"
#include <math.h>

using namespace std;

//---------------------------------------------------------
// Constructor

AttackCommander::AttackCommander()
{
  m_vteam = "NOT_SET";
  m_vname = "NOT_SET";

  m_path_update_var = "NOT_SET";

  m_vdist_thresh = 50;

  m_reports_recived = 0;
  m_last_path = "NOT_SET";
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool AttackCommander::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();

#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString(); 
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif

     if(key == "NODE_REPORT" || key == "NODE_REPORT_LOCAL"){
       if(msg.GetString().find("X=") != std::string::npos && msg.GetString().find("Y=") != std::string::npos){
         m_reports_recived++;
         std::string vehicle = tokStringParse(msg.GetString(), "NAME", ',', '=');
         m_vreports[vehicle] = msg.GetString();
       }
     }

     else if(key != "APPCAST_REQ") // handle by AppCastingMOOSApp
       reportRunWarning("Unhandled Mail: " + key);
   }
	
   return(true);
}

XYPoint AttackCommander::getCordsFromReport(std::string report)
{
  string xStr = tokStringParse(report, "X", ',', '=');
  string yStr = tokStringParse(report, "Y", ',', '=');
  double x = atof(xStr.c_str());
  double y = atof(yStr.c_str());
  return XYPoint(x, y);
}

double AttackCommander::distance(double x1, double y1, double x2, double y2)
{
  return sqrt(pow((x2-x1),2.0)+pow((y2-y1),2.0));
}

double AttackCommander::distance(XYPoint point1, XYPoint point2){
  return distance(point1.x(), point1.y(), point2.x(), point2.y());
}

double AttackCommander::distance(std::string report1, std::string report2)
{
  return distance(getCordsFromReport(report1), getCordsFromReport(report2));
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool AttackCommander::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool AttackCommander::Iterate()
{
  AppCastingMOOSApp::Iterate();
  if(m_vreports.find(m_vname) != m_vreports.end()){
    XYPoint localPos = getCordsFromReport(m_vreports[m_vname]);
 
    cout << "ASDASDA" << endl;
    double distanceToFlag;
    double distanceToHome;

    if(m_vteam == "red"){
      distanceToFlag = distance(localPos, m_blue_flag);
      distanceToHome = distance(localPos, m_red_flag);
    }else if(m_vteam == "blue"){
      distanceToFlag = distance(localPos, m_red_flag);
      distanceToHome = distance(localPos, m_blue_flag);
    }
    
    if(distanceToFlag > distanceToHome){

      std::vector<std::string> closeVehicals;

      std::map<std::string, std::string>::iterator it;
      for(it=m_vreports.begin(); it!=m_vreports.end(); it++){
	if(it->first != m_vname){
	  if(m_vdist_thresh > distance(m_vreports[m_vname], it->second)){
	    std::string myGroup = tokStringParse(m_vreports[m_vname], "GROUP", ',', '=');
	    std::string remoteGroup = tokStringParse(m_vreports[it->first], "GROUP", ',', '=');
	    if(remoteGroup == myGroup){
	      closeVehicals.push_back(it->first);
	    }
	  }
	}
      }
    
      if(0 != closeVehicals.size()){
	double dist = distance(m_waypt_line.get_vx(0), m_waypt_line.get_vy(0), m_waypt_line.get_vx(1), m_waypt_line.get_vx(1));
	double distPerVehical = dist/closeVehicals.size();

	double waypt_line_vector[2];
	waypt_line_vector[0] = m_waypt_line.get_vx(1) - m_waypt_line.get_vx(0);
	waypt_line_vector[1] = m_waypt_line.get_vy(1) - m_waypt_line.get_vy(0);

	std::vector<double> distPerVehicalVector;
	distPerVehicalVector.push_back((waypt_line_vector[0]/dist)*distPerVehical);
	distPerVehicalVector.push_back((waypt_line_vector[1]/dist)*distPerVehical);

	XYSegList path;
	XYPoint closestPoint;
	
	XYPoint startingPoint = XYPoint(m_waypt_line.get_vx(0),m_waypt_line.get_vy(0));
	std::vector<XYPoint> points;
	std::vector<std::string> vnames;
	
	
	for(int i=0; i<=closeVehicals.size(); i++){
	  XYPoint currentPoint = startingPoint;
	  currentPoint.shift_x(distPerVehicalVector.at(0)*i);
	  currentPoint.shift_y(distPerVehicalVector.at(1)*i);
	  points.push_back(currentPoint);
	}
	
	closeVehicals.push_back(m_vname);

	for(int i=0; i<points.size(); i++){
	  reportEvent(points.at(i).get_spec());
	  double minDist;
	  int closest_v;
	  
	  for(int j=0; j<closeVehicals.size(); j++){
	    if(j == 0){
	      minDist = distance(getCordsFromReport(m_vreports[closeVehicals.at(j)]), points.at(i));
	      closest_v = j;
	      continue;
	    }
	    
	    double d = distance(getCordsFromReport(m_vreports[closeVehicals.at(j)]), points.at(i));
	    if(d < minDist){
	      minDist = d;
	      closest_v = j;
	    }
	  }
	  
	  if(closeVehicals.at(closest_v) == m_vname){
	    closestPoint = points.at(i);
	    break;
	  }
	 
	 closeVehicals.erase(closeVehicals.begin() + closest_v);
	}
	/*
	for(int i=1; i<=closeVehicals.size(); i++){
	  XYPoint currentPoint = startingPoint;
	  currentPoint.shift_x(distPerVehicalVector.at(0)*i);
	  currentPoint.shift_y(distPerVehicalVector.at(1)*i);
	  
	  double closestVehical = true;
	  double minDist = distance(getCordsFromReport(m_vreports[m_vname]), currentPoint);
	  std::map<std::string, std::string>::iterator it;
	  for(it=m_vreports.begin(); it!=m_vreports.end(); it++){
	    if(it->first != m_vname){
	      double d = distance(getCordsFromReport(m_vreports[it->first]), currentPoint);
	      if(d < minDist)
		closestVehical =false;
	    }
	  }

	  if(closestVehical){
	    closestPoint = currentPoint;
	    break;
	  }
	  
	  
	  if(i==0){
	    minDist = distance(getCordsFromReport(m_vreports[m_vname]), currentPoint);
	    closestPoint = currentPoint;
	    continue;
	  }
	
	  double d = distance(getCordsFromReport(m_vreports[m_vname]), currentPoint);
	  if(d<minDist){
	    closestPoint = currentPoint;
	    minDist = d;
	  }
	  
	}
	*/

	path.add_vertex(closestPoint);
	if(m_vteam == "red"){
	  path.add_vertex(m_blue_flag);
	}else if(m_vteam == "blue"){
	  path.add_vertex(m_red_flag);
	}
	std::string sPath = path.get_spec();
	if(sPath != m_last_path){
	  m_Comms.Notify(m_path_update_var, "points = "+sPath);
	  reportEvent("Current Path: "+ sPath);
	}
      }
    }
  }else{
    std::string sPath;
    if(m_vteam == "red"){
      sPath = m_blue_flag.get_spec();
    }else if(m_vteam == "blue"){
      sPath = m_red_flag.get_spec();
    }
    
    if(sPath != m_last_path){
       m_Comms.Notify(m_path_update_var, "points = "+sPath);
       reportEvent("Current Path: "+ sPath);
    }
  }

  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool AttackCommander::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  STRING_LIST sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(!m_MissionReader.GetConfiguration(GetAppName(), sParams))
    reportConfigWarning("No config block found for " + GetAppName());

  STRING_LIST::iterator p;
  for(p=sParams.begin(); p!=sParams.end(); p++) {
    string orig  = *p;
    string line  = *p;
    string param = toupper(biteStringX(line, '='));
    string value = line;
    double dval = atof(value.c_str());

    bool handled = false;
    if(param == "VTEAM") {
      m_vteam = value;
      handled = true;
    }
    else if(param == "VNAME") {
      m_vname = value;
      handled = true;
    }else if(param == "UPDATE_VAR"){
      m_path_update_var = value;
      handled = true;
    }else if(param == "RED_ZONE"){
      m_red_zone_bounds = string2SegList(value);
      handled = true;
    }else if(param == "BLUE_ZONE"){
      m_blue_zone_bounds = string2SegList(value);
      handled = true;
    }else if(param == "RED_FLAG"){
      m_red_flag = string2Point(value);
      handled = true;
    }else if(param == "BLUE_FLAG"){
      m_blue_flag = string2Point(value);
      handled = true;
    }else if(param == "WAYPT_LINE"){
      m_waypt_line = string2SegList(value);
      handled = true;
    }else if(param == "VDIST_THRESH"){
      cout << ""<< value << "" << endl;
      m_vdist_thresh = dval;
      handled = true;
    }
    
    if(!handled)
      reportUnhandledConfigWarning(orig);
  }

  if(m_vteam == "NOT_SET"){
    reportConfigWarning("VTEAM is not set");
  }
  if(m_vname == "NOT_SET"){
    reportConfigWarning("VNAME is not set");
  }
  if(m_path_update_var == "NOT_SET"){
    reportConfigWarning("UPDATE_VAR is not set");
  }
  if(m_red_zone_bounds.size() != 4 || m_blue_zone_bounds.size() != 4){
    reportConfigWarning("\"red_zone\" and \"blue_zone\" must be defined with 4 points each");
  }
  /*
  if(m_red_flag.size() != 1 || m_blue_flag.size() != 1){
    reportConfigWarning("\"red_flag\" and  \"blue_flag\" must be defined with 1 point each");
  }
  */
  if(m_waypt_line.size() != 2){
    reportConfigWarning("\"waypt_line\" must be defined with 2 points");
  }
  
  registerVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void AttackCommander::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register("NODE_REPORT", 0);
  Register("NODE_REPORT_LOCAL", 0);
 
}


//------------------------------------------------------------
// Procedure: buildReport()

bool AttackCommander::buildReport() 
{
  m_msgs << "vname: " << m_vname << endl;
  m_msgs << "vteam: " << m_vteam << endl;
  m_msgs << "update varable: " << m_path_update_var << endl << endl;

  m_msgs << "red zone: " << m_red_zone_bounds.get_spec() << endl;
  m_msgs << "blue zone: " << m_blue_zone_bounds.get_spec() << endl;
  m_msgs << "red flag: " << m_red_flag.get_spec() << endl;
  m_msgs << "blue flag: " << m_blue_flag.get_spec() << endl;
  m_msgs << "waypt line" << m_waypt_line.get_spec() << endl << endl;

  m_msgs << "Reports recived: " << m_reports_recived << endl;
  //m_msgs << "SIZE:" << m_vreports.size() << endl;

  std::map<std::string, std::string>::iterator it;
  for(it=m_vreports.begin(); it!=m_vreports.end(); it++){
    m_msgs << "Tracking vehicle: " << it->first << endl;
  }

  return(true);
}

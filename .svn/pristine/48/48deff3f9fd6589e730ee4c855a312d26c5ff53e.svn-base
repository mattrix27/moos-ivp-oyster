/************************************************************/
/*   NAME: Mike Benjamin                                    */
/*   ORGN: Dept of Mechanical Eng / CSAIL, MIT Cambridge MA */
/*   FILE: FlagStrategy.cpp                                 */
/*   DATE: August 18th, 2015                                */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "FlagStrategy.h"
#include "XYFormatUtilsMarker.h"
#include "XYSegList.h"

using namespace std;

//---------------------------------------------------------
// Constructor

FlagStrategy::FlagStrategy()
{
  m_flag_summaries_received = 0;
  m_flag_summary_tstamp = 0;

  m_nav_x_set = false;
  m_nav_y_set = false;
  m_nav_x = 0;
  m_nav_y = 0;
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool FlagStrategy::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key   = msg.GetKey();
    string sval  = msg.GetString(); 
    double dval  = msg.GetDouble();

#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity();
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif

    bool handled = false;
    if(key == "FLAG_SUMMARY") 
      handled = handleMailFlagSummary(sval);
    else if(key == "NAV_X") {
      m_nav_x = dval;
      m_nav_x_set = true;
    }
    else if(key == "NAV_Y") {
      m_nav_y = dval;
      m_nav_y_set = true;
    }	
    else 
      reportRunWarning("Unhandled Mail: " + key);
  }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool FlagStrategy::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool FlagStrategy::Iterate()
{
  AppCastingMOOSApp::Iterate();
  // Do your thing here!
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool FlagStrategy::OnStartUp()
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

    bool handled = false;
    if(param == "FLAG_SUMMARY") {
      handled = handleMailFlagSummary(value);
    }
    else if(param == "BAR") {
      handled = true;
    }

    if(!handled)
      reportUnhandledConfigWarning(orig);

  }

  cout << "Successfully started" << endl;
  registerVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void FlagStrategy::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register("FLAG_SUMMARY", 0);
  Register("NAV_X", 0);
  Register("NAV_Y", 0);
}

//---------------------------------------------------------
// Procedure: handleMailFlagSummary
//   Example: "label=one,x=8,y=4,grab_dist=10,ownedby=none #
//             label=two,x=2,y=9,grab_dist=10,ownedby=henry"

bool FlagStrategy::handleMailFlagSummary(string str)
{
  // Part 1: Process the summary making a new vector of flags for now.
  vector<XYMarker> new_flags;
  vector<string> svector = parseString(str, '#');
  for(unsigned int i=0; i<svector.size(); i++) {
    string flag_spec = svector[i];
    XYMarker flag = string2Marker(flag_spec);
    if(flag.is_set_x() && flag.is_set_y() && (flag.get_label() != "")) 
      new_flags.push_back(flag);
    else
      reportRunWarning("Ivalid Flag Summary: " + flag_spec);
  }

  bool flagset_modified = false;

  // Part 2: Using the flag label as a key, update old flags based on
  // new flags, and note if any flag has been modified.  
  for(unsigned int i=0; i<new_flags.size(); i++) {
    XYMarker new_flag = new_flags[i];
    for(unsigned int j=0; j<m_flags.size(); j++) {
      if(new_flag.get_label() == m_flags[j].get_label()) {
	if(!flagsMatch(new_flag, m_flags[j])) {
	  m_flags[j] = new_flag;
	  flagset_modified = true;
	}
      }
    }
  }

  // Part 3: Using the flag label as a key, determine if the old set
  // of flags have all the new flags.
  for(unsigned int i=0; i<m_flags.size(); i++) {
    bool found = false;
    for(unsigned int j=0; j<new_flags.size(); j++) {
      if(m_flags[i].get_label() == new_flags[j].get_label()) 
	found = true;
    }
    if(!found) {
      // New flagset missing a previously known flag
      flagset_modified = true; // 
    }
  }

  // Part 4: Using the flag label as a key, determine if the new set
  // of flags have all the old flags.
  for(unsigned int i=0; i<new_flags.size(); i++) {
    bool found = false;
    for(unsigned int j=0; j<m_flags.size(); j++) {
      if(new_flags[i].get_label() == m_flags[j].get_label()) 
	found = true;
    }
    if(!found) {
      // New flagset contains a previously unknown flag
      flagset_modified = true; 
      m_flags.push_back(new_flags[i]);
    }
  }

  // Increment the counter and timestamp of the latest summary
  m_flag_summaries_received++;
  m_flag_summary_tstamp = m_curr_time - m_start_time;

  if(flagset_modified)
    generateSearchPath();
  
  return(flagset_modified);
}


//------------------------------------------------------------
// Procedure: generateSearchPath

bool FlagStrategy::generateSearchPath()
{
  if(!m_nav_x_set || !m_nav_y_set)
    return(false);

  XYSegList segl;
  unsigned int flags_size = m_flags.size();
  vector<bool> flags_marked(flags_size, false);
  
  bool done = false;
  while(!done) {
    int     closest_ix   = -1;
    double  closest_dist = 0;
    for(unsigned int i=0; i<m_flags.size(); i++) {
      if(!flags_marked[i] && m_flags[i].get_owner()=="") {
	double x = m_flags[i].get_vx();
	double y = m_flags[i].get_vy();
	double dist = hypot(m_nav_x-x, m_nav_y-y);
	if((closest_ix < 0) || (dist < closest_dist)) {
	  closest_ix = i;
	  closest_dist = dist;
	}
      }
    }

    m_search_path_debug1 += "," + intToString(closest_ix);

    if(closest_ix == -1)
      done = true;
    else {
      unsigned int ix = (unsigned int)(closest_ix);
      flags_marked[ix] = true;
      double next_x = m_flags[ix].get_vx();
      double next_y = m_flags[ix].get_vy();
      segl.add_vertex(next_x, next_y);
    }
  }

  if(segl.size() == 0) {
    m_search_path = "empty";
    Notify("FLAG_PATH", "");
    Notify("FLAGS_TO_GRAB", "false");
  }
  else {
    string segl_spec = segl.get_spec();
    string pts = tokStringParse(segl_spec, "pts", ',', '=');
    m_search_path = segl_spec;
    Notify("FLAG_PATH", "polygon="+segl_spec);
    Notify("FLAGS_TO_GRAB", "true");
  }
    
  return(true);
}

//------------------------------------------------------------
// Procedure: flagsMatch

bool FlagStrategy::flagsMatch(const XYMarker& ma, const XYMarker& mb) const
{
  if(ma.get_vx() != mb.get_vx())
    return(false);
  if(ma.get_vy() != mb.get_vy())
    return(false);
  if(ma.get_range() != mb.get_range())
    return(false);
  if(ma.get_owner() != mb.get_owner())
    return(false);
  return(false);
}

//------------------------------------------------------------
// Procedure: buildReport()

bool FlagStrategy::buildReport() 
{
  string s_last_summary_tstamp = "n/a";
  if(m_flag_summary_tstamp > 0)
    s_last_summary_tstamp = doubleToString(m_flag_summary_tstamp,2);
  
  m_msgs << "Flag Summaries Received: " << m_flag_summaries_received;
  m_msgs << " (" << s_last_summary_tstamp << ")" << endl << endl;


  ACTable actab(5);
  actab << "Label | OwnedBy | X | Y | GrabDist";
  actab.addHeaderLines();

  for(unsigned int i=0; i<m_flags.size(); i++) {
    string label, ownedby, s_x, s_y, s_range;
    label   = m_flags[i].get_label();
    ownedby = m_flags[i].get_owner();
    s_x = doubleToStringX(m_flags[i].get_vx(),2);
    s_y = doubleToStringX(m_flags[i].get_vy(),2);
    s_range = doubleToStringX(m_flags[i].get_range(),2);
    actab << label << ownedby << s_x << s_y << s_range;
  }


  m_msgs << actab.getFormattedString();
  m_msgs << endl;
  
  m_msgs << "Search path:" << m_search_path << endl;
  m_msgs << "Search pathD1:" << m_search_path_debug1 << endl;
  m_msgs << "Search pathD2:" << m_search_path_debug2 << endl;

  return(true);
}

/************************************************************/
/*    NAME: Carter Fendley                                  */
/*    ORGN: MIT                                             */
/*    FILE: NetMon.cpp                                    */
/*    DATE: 08/01                                           */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "NetMon.h"
#include <stdio.h>
#include <ncurses.h>

using namespace std;

//---------------------------------------------------------
// Constructor

NetMon::NetMon()
{
  m_max_x = -1;
  m_max_y = -1;
}

//---------------------------------------------------------
// Destructor

NetMon::~NetMon()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool NetMon::OnNewMail(MOOSMSG_LIST &NewMail)
{
  MOOSMSG_LIST::iterator p;
   
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;

#if 0 // Keep these around just for template
    string key   = msg.GetKey();
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString(); 
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool NetMon::OnConnectToServer()
{
   // register for variables here
   // possibly look at the mission file?
   // m_MissionReader.GetConfigurationParam("Name", <string>);
   // m_Comms.Register("VARNAME", 0);
	
   RegisterVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool NetMon::isHostUp(string ip){
  string cmd = "ping -c 1 -t 1 ";
  cmd += ip;
  cmd += " &> /dev/null";
  int r = system(cmd.c_str());
  return r == 0;
}

string NetMon::genNameStr(string name, string ip){
  stringstream name_ss;
  name_ss << " | " << name << ((name == "") ? "" : "(") << ip << ((name == "") ? ": " : "): ");
  return name_ss.str();
}

string NetMon::genStatusStr(bool up){
  stringstream status_ss;
  status_ss << ((up) ? "  Host Up  " : " Host Down ");
  return status_ss.str();
}

int NetMon::writeStatus(int y, int x, string name, string ip, bool up){
  string name_str = genNameStr(name, ip);
  string status_str = genStatusStr(up);

  if(name_str.size() + status_str.size() > m_max_x){
    return -1;
  }

  attron(A_NORMAL);
  mvprintw(y, x, name_str.c_str());
  attroff(A_NORMAL);

  if (up)
    attron(COLOR_PAIR(1));
  else
    attron(COLOR_PAIR(2));
  mvprintw(y, x+(m_max_dstring_size-status_str.size()), status_str.c_str());
  attroff(COLOR_PAIR(2));
  attroff(COLOR_PAIR(1));

  return 0; 
}

int NetMon::writeStatus(int y, int x, string ip, bool up){
  return writeStatus(y, x, "", ip, up);
}

void NetMon::updateMaxStatusLength(){
  int g = 0;
  int g_status = 0;
  int g_name = 0;

  for(map<string, vector<array<string,2> > >::iterator it = m_group_map.begin(); it != m_group_map.end(); it++){
    for(vector<array<string,2> >::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
      array<string,2> name_ip = *it2;
      string name_str = genNameStr(name_ip[0], name_ip[1]);
      string status_str = genStatusStr(true);
      string out = name_str + status_str;

      if(name_str.size() > g_name)
        g_name = name_str.size();
      if(status_str.size() > g_status)
        g_status = status_str.size();
      if (out.size() > g)
        g = out.size();
    }
  }

  m_max_dstring_size = g;
  m_max_status_len = g_status;
  m_max_name_len = g_name;
}

string NetMon::genDebugStr(){
  stringstream ss;
  ss << "NetMon v0.1 "<< "max_y=" << m_max_y << ",max_x=" << m_max_x \
  << ",max_dstring_size=" << m_max_dstring_size << ",max_name_len=" << m_max_name_len \
  << ",max_status_len=" << m_max_status_len << ",m_dstring_per_line=" << m_dstring_per_line;
  return ss.str();
}

bool NetMon::Iterate()
{ 
  mvprintw(1,1, "Test");
  int nm_x, nm_y; //nm = new_max
  getmaxyx(stdscr, nm_y, nm_x);
  if(nm_x != m_max_x | nm_y != m_max_y){
    m_max_x = nm_x;
    m_max_y = nm_y;

    updateMaxStatusLength();
    m_dstring_per_line = (int) floor((m_max_x*1.0)/(m_max_dstring_size*1.0));
    
    //If term too small just print and see what happens
    if(m_dstring_per_line == 0)
      m_dstring_per_line = 1;

    wclear(stdscr);
    refresh();
  }
  
  mvprintw(0,0, genDebugStr().c_str());

  int y = 2;
  int status_c = 0;
  for(map<string, vector<array<string,2> > >::iterator it = m_group_map.begin(); it != m_group_map.end(); it++){
    stringstream ss;
    ss << "============ " << it->first << " ===========";
    mvprintw(y, 0, ss.str().c_str());
    y++;

    for(vector<array<string,2> >::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
      status_c++;

      if(status_c > m_dstring_per_line){
        status_c = 1;
        y++;
      }

      array<string,2> name_ip = *it2;

      stringstream debug1;
      debug1 << name_ip[0] << ":" << name_ip[1] << ":" << status_c << ":" << y;
      mvprintw(m_max_y-1,0, debug1.str().c_str());
      refresh();

      int r = writeStatus(y, (status_c-1)*m_max_dstring_size, name_ip[0], name_ip[1], isHostUp(name_ip[1]));

      refresh();
    }
    y +=2;
    status_c = 0;
  }

  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool NetMon::OnStartUp()
{
  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    list<string>::iterator p;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string line  = *p;
      string param = tolower(biteStringX(line, '='));
      string value = line;
      
      if(param == "add_ip") {
        string group = tokStringParse(line, "group", ',', '=');
        if(group == ""){
          group = "IP Watches";
        }
        string ip = tokStringParse(line, "ip", ',', '=');
        if(ip == ""){
          //Handle errors in config
        }
        string name = tokStringParse(line, "name", ',', '=');
       
        array<string,2> name_ip;
        name_ip[0] = name;
        name_ip[1] = ip;

        m_group_map[group].push_back(name_ip);

      }
    }
  }
  
  setupScreen();

  RegisterVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void NetMon::RegisterVariables()
{
  // Register("FOOBAR", 0);
}

void NetMon::setupScreen(){
  initscr();
  start_color();
  
  init_pair(1, COLOR_BLACK, COLOR_GREEN);
  init_pair(2, COLOR_BLACK, COLOR_RED);

  mvprintw(1,1, "Test2");
  refresh();
}

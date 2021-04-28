/************************************************************/
/*    NAME: Oliver MacNeely                                              */
/*    ORGN: MIT                                             */
/*    FILE: PingDisplay.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "PingDisplay.h"
#include "XYFormatUtilsConvexGrid.h"
#include "ACTable.h"
#include "NodeRecord.h"
#include "NodeRecordUtils.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//---------------------------------------------------------
// Procedure: OnNewMail

bool PingDisplay::OnNewMail(MOOSMSG_LIST &NewMail)
{

  MOOSMSG_LIST::iterator p;	
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
	
    string key   = msg.GetKey();
    string sval  = msg.GetString(); 
    //double dval  = msg.GetDouble();
    //double mtime = msg.GetTime();
    //bool   mdbl  = msg.IsDouble();
    //bool   mstr  = msg.IsString();
    //string msrc  = msg.GetSource();

    if (key == "PING_RESPONSE") {
	
      m_Comms.Notify("DEBUG", "ping received");
      handleReceivedPing(sval);

    } 

  }

  return(true);

}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool PingDisplay::OnConnectToServer()
{
  registerVariables();  
  return(true);
}


//---------------------------------------------------------
// Procedure: Iterate()

bool PingDisplay::Iterate()
{
  postGrid();

  
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()

bool PingDisplay::OnStartUp()
{

  CMOOSApp::OnStartUp();

  string grid_config;

  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    
    list<string>::reverse_iterator p;
    for(p=sParams.rbegin(); p!=sParams.rend(); p++) {
      string config_line = *p;
      string param = toupper(biteStringX(config_line, '='));
      string value = config_line;

      if(param == "GRID_CONFIG") {
	unsigned int len = grid_config.length();
	if((len > 0) && (grid_config.at(len-1) != ','))
	  grid_config += ",";
	grid_config += value;
      }

      if(param == "height") {

	int height = stoi(value);

    }

      if(param == "level") {

	int level = stoi(value);

      }

      if(param == "weight") {

	int weight = stoi(value);

      }

  }
  }


  m_grid = string2ConvexGrid(grid_config);
  m_Comms.Notify("grid_size", m_grid.size());

  m_grid.set_label("psg");
  registerVariables();
  return(true);
}

//------------------------------------------------------------
// Procedure: registerVariables

void PingDisplay::registerVariables()
{

  Register("PING_RESPONSE", 0);
  Register("CELL", 0);
  
}


//------------------------------------------------------------
// Procedure: handleNodeReport

void PingDisplay::handleReceivedPing(string str)
{

  m_Comms.Notify("string", str);

  double posx = stoi(tokStringParse(str, "x", ',', '='));
  double posy = stoi(tokStringParse(str, "y", ',', '='));
  
  m_Comms.Notify("x", posx);
  m_Comms.Notify("y", posy);

  m_Comms.Notify("handling", "true");

  unsigned index, gsize = m_grid.size();
  for(index=0; index<gsize; index++) {
    bool contained = m_grid.ptIntersect(index, posx, posy);
    m_Comms.Notify("contained", contained);
    m_Comms.Notify("index", index);
    if (contained == 1) {
    
      //not reaching this section...checking bool contained
      m_Comms.Notify("About to make map", "true");    
      createHeatMap(index, level);
      m_Comms.Notify("Made map", "true");

    }

  }

}

void PingDisplay::createHeatMap(unsigned int point, int levels) 
	{
	  int array_side_length = (levels*2) +1;
	 
	  std::vector<float> column(array_side_length, 0);

	  std::vector<std::vector<float> > array(array_side_length,column);

	   array[levels][levels] = 1;

	   for (int Xcounter = 0; Xcounter <= levels; Xcounter++) {

	     array[(levels+Xcounter)][levels] = pow(0.5, Xcounter);
	     array[(levels-Xcounter)][levels] = pow(0.5, Xcounter);

	      for (int Ycounter = 0; Ycounter <= (levels-Xcounter);Ycounter++) {
	        
		array[(levels+Xcounter)][(levels+Ycounter)] = pow(0.5, (Ycounter+Xcounter));
		array[(levels+Xcounter)][(levels-Ycounter)] = pow(0.5, (Ycounter+Xcounter));

	      }

	      for (int Ycounter = 0; Ycounter <= (levels-Xcounter);Ycounter++) {
	        
		array[(levels-Xcounter)][(levels+Ycounter)] = pow(0.5, (Ycounter+Xcounter));
		array[(levels-Xcounter)][(levels-Ycounter)] = pow(0.5, (Ycounter+Xcounter));

	      }

	   } 

	   postArray(array, point, levels, array_side_length);

	}

//------------------------------------------------------------------------------
void PingDisplay::postArray(std::vector<std::vector<float> > square, unsigned int center, int layers, int length) {

	int temporary_val = 0;	

          for (int Xcount = 0; Xcount != length; Xcount++) {

	    for (int Ycount = 0; Ycount != length; Ycount++) {
	    
	      int Ydiff = abs (layers - Ycount);
	      int Xdiff = abs (layers - Xcount);
	    
	      if (Xcount < layers) {

	        temporary_val = center - (height*Xdiff);  

	      } else { temporary_val = center + (height*Xdiff);}

	      if (Ycount < layers) {

	        temporary_val -= Ydiff;

	      } else { temporary_val += Ydiff;}

	      if ((Ycount == layers) && (Xcount == layers)) { temporary_val = center;}
             
	      m_Comms.Notify("square", (weight*square[Ycount][Xcount]));
	      m_Comms.Notify("curr", m_grid.getVal(temporary_val));
	      m_Comms.Notify("temp", temporary_val);

	      if (square[Ycount][Xcount] > 0) {
		
	      double average = ((weight*square[Ycount][Xcount]) + m_grid.getVal(temporary_val))/2;  
	      //m_grid.setVal(temporary_val, (40*square[Ycount][Xcount]));
	        m_grid.incVal(temporary_val, (square[Ycount][Xcount]));			
	      }
	      

	     // m_grid.incVal(temporary_val, floor(4*square[Ycount][Xcount]));	      
	     	    }
	  
	  }
	  
	}



//------------------------------------------------------------
// Procedure: postGrid

void PingDisplay::postGrid()
{
  string spec = m_grid.get_spec();
  Notify("VIEW_GRID", spec);
}

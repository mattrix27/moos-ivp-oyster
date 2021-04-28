/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Eng / CSAIL, MIT Cambridge MA     */
/*    FILE: CatHandler.cpp                                       */
/*    DATE: Apr 21st, 2017                                       */
/*****************************************************************/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "MBUtils.h"
#include "CatHandler.h"
#include "FileBuffer.h"

using namespace std;

//--------------------------------------------------------
// Procedure: handle
//     Notes: 

bool CatHandler::handle()
{
  for(unsigned int i=0; i<m_files.size(); i++) {
    vector<string> lines = fileBuffer(m_files[i]);
    for(unsigned int j=0; j<lines.size(); j++) {
      string line = stripBlankEnds(lines[j]);
      if(line.length() != 0) {
	string key_type = biteStringX(line, ' ');
	string key      = biteStringX(line, ' ');
	string key_mach = line;

	// cout << "From file:" << m_files[i] << ", mach:" << key_mach << endl;

	m_map_key_to_type[key] = key_type;
	m_map_key_to_mach[key] = key_mach;
      }
    }
  }

  map<string,string>::iterator p;
  for(p=m_map_key_to_type.begin(); p!=m_map_key_to_type.end(); p++) {
    string key = p->first;
    string key_type = p->second;
    string key_mach = m_map_key_to_mach[key];

    cout << key_type << " " << key << " " << key_mach << endl << endl;
  }  

  return(true);
}

//--------------------------------------------------------
// Procedure: addFile()

bool CatHandler::addFile(string filename)
{
  if(!okFileToRead(filename))
    return(false);

  m_files.push_back(filename);
  return(true);
}


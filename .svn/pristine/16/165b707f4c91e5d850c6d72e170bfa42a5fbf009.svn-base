/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Eng / CSAIL, MIT Cambridge MA     */
/*    FILE: CatHandler.h                                         */
/*    DATE: April 21st, 2017                                     */
/*****************************************************************/

#ifndef CATKEYS_HEADER
#define CATKEYS_HEADER

#include <string>
#include <map>

class CatHandler
{
 public:
  CatHandler() {};
  ~CatHandler() {};

  bool addFile(std::string);
  bool handle();

 protected: // State Variables

  std::map<std::string, std::string> m_map_key_to_type;
  std::map<std::string, std::string> m_map_key_to_mach;

  std::vector<std::string> m_files;
  
};

#endif


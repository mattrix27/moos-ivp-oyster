/*****************************************************************/
/*    NAME: Michael "Misha" Novitzky                             */
/*    ORGN: Dept of Mechanical Eng / CSAIL, MIT Cambridge MA     */
/*    FILE: BHV_SimpleDefend.h                                   */
/*    DATE: March 15th 2016  (For purposes of simple flag defense)*/
/*                                                               */
/* This program is free software; you can redistribute it and/or */
/* modify it under the terms of the GNU General Public License   */
/* as published by the Free Software Foundation; either version  */
/* 2 of the License, or (at your option) any later version.      */
/*                                                               */
/* This program is distributed in the hope that it will be       */
/* useful, but WITHOUT ANY WARRANTY; without even the implied    */
/* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR       */
/* PURPOSE. See the GNU General Public License for more details. */
/*                                                               */
/* You should have received a copy of the GNU General Public     */
/* License along with this program; if not, write to the Free    */
/* Software Foundation, Inc., 59 Temple Place - Suite 330,       */
/* Boston, MA 02111-1307, USA.                                   */
/*****************************************************************/
 
#ifndef BHV_SIMPLE_DEFEND_HEADER
#define BHV_SIMPLE_DEFEND_HEADER

#include <string>
#include "IvPBehavior.h"
#include "XYPoint.h"
#include "NodeRecordUtils.h"

class BHV_SimpleDefend : public IvPBehavior {
public:
  BHV_SimpleDefend(IvPDomain);
  ~BHV_SimpleDefend() {};
  
  bool         setParam(std::string, std::string);
  void         onIdleState();
  IvPFunction* onRunState();

protected:
  void         postViewPoint(bool viewable=true);
  IvPFunction* buildFunctionWithZAIC();
  IvPFunction* buildFunctionWithReflector();

protected: // Configuration parameters
  double       ratio;
  double       m_max_defend_radius;
  double       m_arrival_radius;
  double       m_desired_speed;
  XYPoint      m_nextpt;
  XYPoint      m_target_pt;
  XYPoint      m_goToPt;
  std::string  m_ipf_type;

protected: // State variables
  double   m_osx;
  double   m_osy;
  map<std::string, NodeRecord> m_contact_list;
};

#ifdef WIN32
	// Windows needs to explicitly specify functions to export from a dll
   #define IVP_EXPORT_FUNCTION __declspec(dllexport) 
#else
   #define IVP_EXPORT_FUNCTION
#endif

extern "C" {
  IVP_EXPORT_FUNCTION IvPBehavior * createBehavior(std::string name, IvPDomain domain) 
  {return new BHV_SimpleDefend(domain);}
}
#endif










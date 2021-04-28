/************************************************************/
/*    NAME: Conlan Cesar                                              */
/*    ORGN: MIT                                             */
/*    FILE: Record2.h                                          */
/*    DATE:                             */
/************************************************************/

#ifndef Record2_HEADER
#define Record2_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include <portaudio.h>
#include <sndfile.h>

class Record2 : public AppCastingMOOSApp
{
 public:
   Record2();
   ~Record2();
    struct CallbackDataStruct {
        bool shouldRecord = false;
        SNDFILE *outfile;
    } paCallbackData;

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected:
   bool buildReport();
   void registerVariables();
    void closeAudioFile();

 private: // Configuration variables
    std::string m_MOOSVarToWatch = "SPEECH_ACTIVE";
    std::string m_MOOSValueToWatch = "TRUE";
    std::string file_save_prefix = "file_";
    std::string dir_save_prefix = "pRecord2_saves";
    std::string dir_save_full = "pRecord2_saves";

 private: // State variables
    uint8_t count = 0;
    PaStream* audioStream;
};

#endif 

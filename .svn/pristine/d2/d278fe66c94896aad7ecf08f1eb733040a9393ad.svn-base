/************************************************************/
/*    NAME: Conlan Cesar                                    */
/*    ORGN: MIT                                             */
/*    FILE: Record2.cpp                                     */
/*    DATE: Late Summer 2018                                */
/************************************************************/

/*
 * Thanks to https://github.com/illuusio/linux-audio-example/blob/master/portaudio/libsndfile_port_rec.c,
 * MumbleClient, and the OG pRecord
 */

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "Record2.h"

using namespace std;

const int NUM_CHANNELS = 1;
const int SAMPLE_RATE = 48000;
const int FRAMES_PER_BUFFER = 512;
SF_INFO sfinfo;

static int paCallback(const void *_inputBuffer,
                      void *_outputBuffer,
                      unsigned long framesPerBuffer,
                      const PaStreamCallbackTimeInfo* /*timeInfo*/,
                      PaStreamCallbackFlags /*statusFlags*/,
                      void *userData) {
  // Recast the bits lost in transport
  const auto *paData = (const Record2::CallbackDataStruct*) userData;
  auto *inputBuffer = (float*) _inputBuffer;
  long writeCount = 0;

  // Dump the input into the send buffer
  if(paData->shouldRecord) {
    writeCount = sf_write_float(paData->outfile, inputBuffer, framesPerBuffer * NUM_CHANNELS);

    if(writeCount <= 0) {
      printf("Can't write to file!\n");
      return paComplete;
    }
  } else {
    return paComplete;
  }

  return paContinue;
}


//---------------------------------------------------------
// Constructor

Record2::Record2()
{
}

//---------------------------------------------------------
// Destructor

Record2::~Record2()
{

  closeAudioFile();
  Pa_Terminate();


}

void Record2::closeAudioFile() {
  this->paCallbackData.shouldRecord = false;
  Pa_CloseStream(audioStream);
  sf_write_sync(this->paCallbackData.outfile);
  sf_close(paCallbackData.outfile); // Close the old file

  Notify("AUDIO_FILE_ENDING", count);
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool Record2::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();
    string sval  = msg.GetString();

#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString(); 
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif

     if(key == m_MOOSVarToWatch) {
       if (sval == m_MOOSValueToWatch) {
         if (this->paCallbackData.shouldRecord) return true; // Something is already being recorded, abort

         this->paCallbackData.shouldRecord = true;
         count++;

         string fileName = "./" + dir_save_full + "/" + file_save_prefix + intToString(count) + ".wav";

         // Open the new one
         if (!(paCallbackData.outfile = sf_open(fileName.c_str(), SFM_WRITE, &sfinfo))) {
           reportRunWarning("Unable to open output file " + fileName + ": " + sf_strerror(paCallbackData.outfile));
         } else {
           auto err = Pa_StartStream(audioStream);
           if (err) {
             string errText = "Error starting audio engine: ";
             errText.append(Pa_GetErrorText(err));
             reportRunWarning(errText);
           }
         }

         Notify("AUDIO_FILE_RECORDING", fileName);
       } else {
         closeAudioFile();
       }
     }

     else if(key != "APPCAST_REQ" && key != "SPEECH_ACTIVE")
       reportRunWarning("Unhandled Mail: " + key);
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool Record2::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool Record2::Iterate()
{
  AppCastingMOOSApp::Iterate();
  // Do your thing here!
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool Record2::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  Pa_Initialize();

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

    bool handled = true;
    if(param == "MOOS_VAR_WATCH") {
      //assume a variable in string form
      m_MOOSVarToWatch = value;
    } else if(param == "MOOS_VALUE_WATCH") {
      //assume a variable in string form
      m_MOOSValueToWatch = value;
    } else if(param == "SAVE_FILE_PREFIX"){
      file_save_prefix = value;
    } else if(param == "SAVE_DIR_PREFIX") {
      dir_save_prefix = value;
    } else {
      handled = false;
    }

    if(!handled)
      reportUnhandledConfigWarning(orig);

  }

  // We borrow pLogger's method of adding timestamp to logging
  // TODO use printf to allow for custom date placement
  struct tm *Now;
  time_t aclock;
  time( &aclock );

  Now = localtime( &aclock );

  stringstream ss;
  ss << dir_save_prefix << "_" << Now->tm_mday << "_" << Now->tm_mon+1 << "_";
  ss << Now->tm_year+1900 << "_____" << Now->tm_hour << "_" << Now->tm_min << "_" << Now->tm_sec;

  //Let's create the directory where files saves will happen
  int result_dir_create = 0;
  std::string sys_call;
  sys_call = "mkdir -p " + ss.str();
  result_dir_create = system(sys_call.c_str());

  dir_save_full = ss.str();

  if(result_dir_create!=0) {
    reportConfigWarning("Error creating save directory: " + dir_save_full);
    return false;
  }

  sfinfo.channels = NUM_CHANNELS;
  sfinfo.samplerate = SAMPLE_RATE;
  sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_32;

  Pa_OpenDefaultStream(&audioStream,
                       NUM_CHANNELS,
                       0,
                       paFloat32,
                       SAMPLE_RATE,
                       FRAMES_PER_BUFFER,
                       paCallback,
                       &paCallbackData);
  
  registerVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void Record2::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register(m_MOOSVarToWatch, 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool Record2::buildReport() 
{

  m_msgs << "============================================ \n";
  m_msgs << "File: pRecord2                               \n";
  m_msgs << "============================================ \n";
  m_msgs << "Record on MOOS Variable: " << m_MOOSVarToWatch << endl;
  m_msgs << "with Value: " << m_MOOSValueToWatch << endl;
  m_msgs << "Save file prefix: " << file_save_prefix << endl;
  m_msgs << "Save dir prefix: " << dir_save_prefix << endl;
  m_msgs << "Full save dir: " << dir_save_full << endl;
  return(true);
}





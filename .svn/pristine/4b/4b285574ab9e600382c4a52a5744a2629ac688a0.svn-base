/************************************************************/
/*    NAME: Michael "Misha" Novitzky                        */
/*    Original NAME: Oliver MacNeely                        */
/*    ORGN: MIT                                             */
/*    FILE: Record.cpp                                      */
/*    DATE: March 28th 2018                                 */
/*    Original DATE: Summer 2017                            *
 *    Thanks to Syb0rg (https://codereview.stackexchange.com/users/27623/syb0rg) from Stack Overflow for snippets/design from this question:
 *    https://codereview.stackexchange.com/questions/84536/recording-audio-continuously-in-c*/
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "Record.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "portaudio.h"
#include "sndfile.h"
#include <pthread.h>
#include <thread>

using namespace std;

bool STATUS = false; // Declare and initialize global recording status variable
bool END = false;

std::string file_save_prefix = "file_";
std::string dir_save_prefix = "pRecord_saves";
std::string  dir_save_full;
stringstream filename;

PaStream *stream = NULL; //Housekeeping for starting an audio stream, creates a stream pointer for future use
PaError err = Pa_Initialize(); // Initializes the audio library for use

void *recordAudio(void *audioStruct) { // Thread-able function to record audio to memory and then pass this recorded audio to a function that writes it to a .wav

    ThreadParams *threadData = (ThreadParams*) audioStruct; // Cast the passed structure for use within function

    while (!END) { // Sets up loop for audio recording while the app is being used, a false value here ends the loop and the thread by returning null

        if (STATUS) { // Check whether we should be recording now

            if (threadData->buffer_counter == 0) threadData->recording_counter += 1; // if this is the 0th buffer, that means this is a new recording so increment the counter

            threadData->buffer_counter += 1; //increment the buffer counter on each iteration


            err = Pa_ReadStream(stream, threadData->audiobuffer->recording, FRAMES_PER_BUFFER); //read a buffer of audio from the stream

            if (threadData->audiodata->recordedSamples == 0) {
                threadData->audiodata->recordedSamples = (short *) malloc(threadData->audiobuffer->size * (threadData->buffer_counter));
            }
            else {
                threadData->audiodata->recordedSamples = (short *) realloc(threadData->audiodata->recordedSamples, //reallocate recording array to make space for the buffer that was just recorded
                                                                       threadData->audiobuffer->size *
                                                                       (threadData->buffer_counter));
            }

            threadData->audiodata->size = threadData->audiobuffer->size * (threadData->buffer_counter); // update size variable

            memcpy((char *) threadData->audiodata->recordedSamples +                              // copy data previously recorded data and buffer together
                   ((threadData->buffer_counter - 1) * threadData->audiobuffer->size),
                   threadData->audiobuffer->recording,
                   threadData->audiobuffer->size);

        } else if (threadData->buffer_counter != 0) {   // if we aren't recording, check if we just finished recording, if so, write recording to file

          filename.str("");
          filename << "./" << dir_save_full << "/";
          filename << file_save_prefix << threadData->recording_counter << ".wav";
          
          storeWAV(threadData->audiodata, filename.str().c_str());      // store recorded audio in .wav file and free used memory
          //  Notify("AUDIO_FILE_SAVED",filename.str());

          free(threadData->audiodata->recordedSamples);
            threadData->audiodata->recordedSamples = NULL;

            threadData->buffer_counter = 0;

        }

      std::this_thread::sleep_for(std::chrono::nanoseconds(100)); // Don't overload the CPU

    }

    return NULL;


}

const PaDeviceInfo *info = Pa_GetDeviceInfo(Pa_GetDefaultInputDevice()); // declare variable


  struct AudioData data = init(44100, 1, paInt16); // initialize structure



  PaStreamParameters inputParameters = // initialize structure for audio device parameters
    {

     device : Pa_GetDefaultInputDevice(),
     channelCount : data.numberOfChannels,
     sampleFormat : data.formatType,
     suggestedLatency : info->defaultLowInputLatency,
     hostApiSpecificStreamInfo : NULL

    };

struct AudioBuffer buffer = {(short*) malloc(FRAMES_PER_BUFFER* sizeof(short)*NUM_CHANNELS), // declare and initialize structure for holding a buffer of audio
                             FRAMES_PER_BUFFER* sizeof(short)*NUM_CHANNELS};


struct ThreadParams params = {&data, &buffer, 0, 0}; // declare and initialize structure for passing data to thread



//---------------------------------------------------------
// Constructor

Record::Record()

{
  m_MOOSVarToWatch = "SPEECH_BUTTON";

  m_MOOSValueToWatch = "TRUE";
 
  err = Pa_OpenStream(&stream, // open stream (initializes audio stream for further use)
		      &inputParameters,
		      NULL,
		      SAMPLE_RATE,
		      FRAMES_PER_BUFFER,
		      paClipOff,
		      NULL,
		      NULL);

  err = Pa_StartStream(stream);
  if(err != 0) reportRunWarning(Pa_GetErrorText(err)); // starts stream - from now on we can read from or write to the stream

    pthread_t thread; // declares posix thread for running audio capture function

    if (pthread_create(&thread, NULL, recordAudio, &params) != 0) reportRunWarning("Error creating thread"); // initializes thread


    
}

//---------------------------------------------------------
// Destructor

Record::~Record()
{

    END = true;
    Pa_Terminate();

}

//---------------------------------------------------------
// Procedure: OnNewMail

bool Record::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();



      if(key == m_MOOSVarToWatch) { // change global variables depending on whether button has been pressed

          if (msg.GetString() == m_MOOSValueToWatch) {

              STATUS = true; // record

          }
          else {

              STATUS = false; // stop recording
          }

      }
#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString(); 
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif

     else if(key != "APPCAST_REQ") {}  // handled by AppCastingMOOSApp

   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool Record::OnConnectToServer()
{
   registerVariables();

   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool Record::Iterate()
{
  AppCastingMOOSApp::Iterate();

    reportEvent("buffer counter: " + intToString(params.buffer_counter));
    reportEvent("recording counter: " + intToString(params.recording_counter));

    if(filename.str() != "") {
      Notify("AUDIO_FILE_SAVED",filename.str());
      filename.str("");
    }

  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool Record::OnStartUp()
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
    if(param == "PATH") {
    }
    else if(param == "BAR") {
      handled = true;
    }
    else if(param == "MOOS_VAR_WATCH") {
      //assume a variable in string form
      m_MOOSVarToWatch = value;
      handled = true;
    }
    else if(param == "MOOS_VALUE_WATCH") {
      //assume a variable in string form
      m_MOOSValueToWatch = value;
      handled = true;
    }
    else if(param == "SAVE_FILE_PREFIX"){
      file_save_prefix = value;
      handled = true;
    }
    else if(param == "SAVE_DIR_PREFIX") {
      dir_save_prefix = value;
      handled = true;
    }

    if(!handled)
      reportUnhandledConfigWarning(orig);

  }

  //We borrow pLogger's method of adding timestamp to logging
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
  sys_call = "mkdir " + ss.str();
  result_dir_create = system(sys_call.c_str());

  dir_save_full = ss.str();

  if(result_dir_create!=0) {
    reportConfigWarning("Error creating save directory: " + dir_save_prefix);
  }
  
  registerVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void Record::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register(m_MOOSVarToWatch, 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool Record::buildReport() 
{
  m_msgs << "============================================ \n";
  m_msgs << "File:                                        \n";
  m_msgs << "============================================ \n";
  m_msgs << "Record on MOOS Variable: " << m_MOOSVarToWatch << endl;
  m_msgs << "with Value: " << m_MOOSValueToWatch << endl; 
  m_msgs << "Save file prefix: " << file_save_prefix << endl;
  m_msgs << "Save dir prefix: " << dir_save_prefix << endl;
  m_msgs << "Full save dir: " << dir_save_full << endl;
  return(true);
}





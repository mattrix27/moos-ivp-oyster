/************************************************************/
/*    NAME: Michael "Misha" Novitzky                        */
/*    Original NAME: Oliver MacNeely                        */
/*    ORGN: MIT                                             */
/*    FILE: Record.h                                        */
/*    DATE: March 28th, 2018                                */
/*    Original DATE: summer 2017                            */
/*    Attribute to stack overflow question as well          */
/************************************************************/

#ifndef Record_HEADER
#define Record_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "Record.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "portaudio.h"
#include "sndfile.h"

// setup constants needed for audio stream creation

#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (1024)
#define NUM_CHANNELS (1)

typedef short SAMPLE;
#define PA_SAMPLE_TYPE paInt16
#define SAMPLE_SILENCE (0)


//structure for holding recording array, and data needed for writing to a .wav file

struct AudioData {

  int formatType;
  int numberOfChannels;
  int sampleRate;
  size_t size;
  short *recordedSamples;

};


//structure for holding a buffer of audio that is then concatenated to overall recording

extern struct AudioBuffer{

  short *recording;
  size_t size;

} AudioBuffer;


//structure for passing data to threaded function

struct ThreadParams {

    struct AudioData *audiodata;
    struct AudioBuffer *audiobuffer;

    int recording_counter;
    int buffer_counter;

};

//function to initialize AudioData structure

inline struct AudioData init(int sampleRate, int channels, int type) {

  struct AudioData data;
  data.formatType = type;
  data.numberOfChannels = channels;
  data.sampleRate = sampleRate;
  data.size = 0;
  data.recordedSamples = NULL;

  return data;

}

//function to store audio data as a .wav file using the libsndfile library

inline void storeWAV(struct AudioData *audio, const char* filename) {

  SF_INFO sfinfo = {};

    sfinfo.channels = audio->numberOfChannels;
    sfinfo.samplerate = audio->sampleRate;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    SNDFILE *outfile = sf_open(filename, SFM_WRITE, &sfinfo); //open file for writing

  long wr = sf_writef_short(outfile, audio->recordedSamples, audio->size / sizeof(short)); //write audio data to .wav file

  sf_write_sync(outfile);
  sf_close(outfile);

}


//standard MOOS/AppCastingMOOS information

class Record : public AppCastingMOOSApp
{
 public:
   Record();
   ~Record();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload 
   bool buildReport();

 protected:
   void registerVariables();

 private: // Configuration variables
  std::string m_MOOSVarToWatch;
  std::string m_MOOSValueToWatch;

 
 private: // State variables
};

#endif 

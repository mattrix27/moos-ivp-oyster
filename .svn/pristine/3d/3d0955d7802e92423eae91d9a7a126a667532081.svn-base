#--------------------------------------------------------
# The CMakeLists.txt for:                      uSpeechRec
# Author(s):                     Michael "Misha" Novitzky
#--------------------------------------------------------

SET(SRC
  SpeechRec_3_0.cpp
  SpeechRec_Info_3_0.cpp
  main_3_0.cpp
)

#To support compiling on OS X and Ubuntu
#We check if not OS X which means we are on a Linux machine
#and will use those libraries
if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  MESSAGE( STATUS "NOT ON AN APPLE OS! Assuming Linux")
  SET(SPEECH_LIBS pulse pulse-simple asound)
endif (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

ADD_EXECUTABLE(uSpeechRec ${SRC})

#include_directories(/opt/local/include/)

TARGET_LINK_LIBRARIES(uSpeechRec
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread
   julius
   sent
   dl
   portaudio
   z
   sndfile
   ${SPEECH_LIBS})



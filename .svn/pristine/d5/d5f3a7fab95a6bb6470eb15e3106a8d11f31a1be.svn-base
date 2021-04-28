#--------------------------------------------------------
# The CMakeLists.txt for:                       pComms_client
# Author(s):                              Oliver
#--------------------------------------------------------

SET(SRC
  UDPConnect.cpp
  Comms_client.cpp
  Comms_client_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pComms_client ${SRC})

TARGET_LINK_LIBRARIES(pComms_client
   ${MOOS_LIBRARIES}
   mbutil
   m
   pthread
   portaudio
   sndfile)


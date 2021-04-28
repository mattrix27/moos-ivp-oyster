#--------------------------------------------------------
# The CMakeLists.txt for:                       pComms_server
# Author(s):                              Oliver
#--------------------------------------------------------

SET(SRC
  UDPConnect.cpp
  Comms_server.cpp
  Comms_server_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pComms_server ${SRC})

TARGET_LINK_LIBRARIES(pComms_server
   ${MOOS_LIBRARIES}
   mbutil
   m
   pthread)


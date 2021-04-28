#--------------------------------------------------------
# The CMakeLists.txt for:                       pPingResponder
# Author(s):                              Carter Fendley
#--------------------------------------------------------

SET(SRC
  PingResponder.cpp
  PingResponder_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pPingResponder ${SRC})

TARGET_LINK_LIBRARIES(pPingResponder
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread)


#--------------------------------------------------------
# The CMakeLists.txt for:                       pPingDisplay
# Author(s):                              Oliver MacNeely
#--------------------------------------------------------

# FILE(GLOB SRC *.cpp)

SET(SRC
  PingDisplay.cpp
  PingDisplay_Info.cpp
  main.cpp
)



ADD_EXECUTABLE(pPingDisplay ${SRC})

TARGET_LINK_LIBRARIES(pPingDisplay
   ${MOOS_LIBRARIES}
   mbutil
   geometry
   m
   pthread)


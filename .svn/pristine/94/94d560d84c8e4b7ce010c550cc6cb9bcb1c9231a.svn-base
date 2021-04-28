#--------------------------------------------------------
# The CMakeLists.txt for:                       pShorePing
# Author(s):                              Oliver MacNeely
#--------------------------------------------------------

# FILE(GLOB SRC *.cpp)

SET(SRC
  ShorePing.cpp
  ShorePing_Info.cpp
  main.cpp
)



ADD_EXECUTABLE(pShorePing ${SRC})

TARGET_LINK_LIBRARIES(pShorePing
   ${MOOS_LIBRARIES}
   mbutil
   geometry
   m
   pthread)


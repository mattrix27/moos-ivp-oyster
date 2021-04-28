#--------------------------------------------------------
# The CMakeLists.txt for:                       pTimeWatch
# Author(s):                              Carter Fendley
#--------------------------------------------------------

SET(SRC
  TimeWatch.cpp
  TimeWatch_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pTimeWatch ${SRC})

TARGET_LINK_LIBRARIES(pTimeWatch
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread)


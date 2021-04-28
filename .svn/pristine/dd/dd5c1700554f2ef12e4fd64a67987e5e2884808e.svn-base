#--------------------------------------------------------
# The CMakeLists.txt for:                       iLEDInterpreter
# Author(s):                              Caileigh Fitzgerald
#--------------------------------------------------------

SET(SRC
  LEDInterpreter.cpp
  LEDInterpreter_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(iLEDInterpreter ${SRC})

TARGET_LINK_LIBRARIES(iLEDInterpreter
   ${MOOS_LIBRARIES}
   mbutil
   m
   pthread)


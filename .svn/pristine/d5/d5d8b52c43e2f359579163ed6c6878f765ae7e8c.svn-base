#--------------------------------------------------------
# The CMakeLists.txt for:                       iLEDInfoBar
# Author(s):                              Caileigh Fitzgerald
#--------------------------------------------------------

SET(SRC
  LEDInfoBar.cpp
  LEDInfoBar_Info.cpp
  iLEDInfoBar_enums.h
  main.cpp
)

ADD_EXECUTABLE(iLEDInfoBar ${SRC})

TARGET_LINK_LIBRARIES(iLEDInfoBar
   ${MOOS_LIBRARIES}
   SimpleSerial
   mbutil
   m
   pthread)


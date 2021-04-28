#--------------------------------------------------------
# The CMakeLists.txt for:                       iButtonBox
# Author(s):                              Carter Fendley
#--------------------------------------------------------

SET(SRC
  ButtonBox.cpp
  ButtonBox_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(iButtonBox ${SRC})

TARGET_LINK_LIBRARIES(iButtonBox
   ${MOOS_LIBRARIES}
   SimpleSerial
   apputil
   mbutil
   m
   pthread)


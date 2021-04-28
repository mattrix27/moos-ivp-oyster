#--------------------------------------------------------
# The CMakeLists.txt for:                       pRecord2
# Author(s):                              
#--------------------------------------------------------

SET(SRC
  Record2.cpp
  Record2_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pRecord2 ${SRC})

TARGET_LINK_LIBRARIES(pRecord2
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread
   portaudio
   sndfile)



#--------------------------------------------------------
# The CMakeLists.txt for:                       pRecord
# Author(s): Oliver MacNeely
#--------------------------------------------------------

SET(SRC
  Record.cpp
  Record_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pRecord ${SRC})

TARGET_LINK_LIBRARIES(pRecord
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   portaudio
   sndfile
   pthread)


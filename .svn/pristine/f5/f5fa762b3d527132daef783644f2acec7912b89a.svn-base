#--------------------------------------------------------
# The CMakeLists.txt for:                       iMumbleClient
# Author(s):                              
#--------------------------------------------------------
include_directories(../../src_third_parties/)


SET(SRC
  MumbleClient.cpp
  MumbleClient_Info.cpp
  main.cpp
        MumbleCallbackHandler.cpp MumbleCallbackHandler.h SimpleRingBuffer.h)

ADD_EXECUTABLE(iMumbleClient ${SRC})
set_target_properties(iMumbleClient PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Remove this when we figure out all of iMumbleClient's race conditions on Pablos
#target_compile_definitions(iMumbleClient PRIVATE DUMP_CORE)

TARGET_LINK_LIBRARIES(iMumbleClient
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread
   mumlib
   portaudio)


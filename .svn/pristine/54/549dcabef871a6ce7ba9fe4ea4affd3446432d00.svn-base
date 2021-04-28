#--------------------------------------------------------
# The CMakeLists.txt for:                       iZephyrHRM
# Author(s):                              
#--------------------------------------------------------
if( ${APPLE})
message( FATAL_ERROR "iZephryHRM only builds in LINUX (not OSX)" )

else(${APPLE})

SET(SRC
  ZephyrHRM.cpp
  ZephyrHRM_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(iZephyrHRM ${SRC})

TARGET_LINK_LIBRARIES(iZephyrHRM
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   pthread
   bluetooth
   m
   pthread)

endif(${APPLE})

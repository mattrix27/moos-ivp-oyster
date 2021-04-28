#--------------------------------------------------------
# The CMakeLists.txt for:                 iActuationMokai
# Author(s):                                  Alon Yaari
#--------------------------------------------------------

# Set System Specific Libraries
if (${WIN32})
  # Windows Libraries
  SET(SYSTEM_LIBS
     wsock32 )
else (${WIN32})
  # Linux and Apple Libraries
  SET(SYSTEM_LIBS
      m
      pthread )
endif (${WIN32})


FILE(GLOB SRC *.cpp)


ADD_EXECUTABLE(iActuationMokai ${SRC})

TARGET_LINK_LIBRARIES(iActuationMokai
   ${MOOS_LIBRARIES}
   mbutil
   ${SYSTEM_LIBS} )
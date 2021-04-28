#--------------------------------------------------------
# The CMakeLists.txt for:                       iNetNMEAClient
# Author(s):                              
#--------------------------------------------------------
find_package(Boost COMPONENTS thread system REQUIRED)

SET(SRC
  NetNMEAClient.cpp
  NetNMEAClient_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(iNetNMEAClient ${SRC})

TARGET_LINK_LIBRARIES(iNetNMEAClient
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread
   ${Boost_THREAD_LIBRARY}
   ${Boost_SYSTEM_LIBRARY}
   )



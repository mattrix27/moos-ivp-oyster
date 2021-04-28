#--------------------------------------------------------
# The CMakeLists.txt for:                       iNetNMEAServer
# Author(s):                              
#--------------------------------------------------------
find_package(Boost COMPONENTS thread system REQUIRED)

SET(SRC
  NMEASession.cpp
  NMEAServer.cpp
  NetNMEAServer.cpp
  NetNMEAServer_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(iNetNMEAServer ${SRC})

TARGET_LINK_LIBRARIES(iNetNMEAServer
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread
   ${Boost_THREAD_LIBRARY}
   ${Boost_SYSTEM_LIBRARY}
   )


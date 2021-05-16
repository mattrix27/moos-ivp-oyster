#--------------------------------------------------------
# The CMakeLists.txt for:                       pOysterPID
# Author(s):                              Matt Tung
#--------------------------------------------------------

SET(SRC
  OysterPID.cpp
  OysterPID_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pOysterPID ${SRC})

TARGET_LINK_LIBRARIES(pOysterPID
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread)


#--------------------------------------------------------
# The CMakeLists.txt for:                       pOysterROS
# Author(s):                              Matt Tung
#--------------------------------------------------------

SET(SRC
  OysterROS.cpp
  OysterROS_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pOysterROS ${SRC})

TARGET_LINK_LIBRARIES(pOysterROS
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread)


#--------------------------------------------------------
# The CMakeLists.txt for:                       pOysterMUX
# Author(s):                              Matthew Tung
#--------------------------------------------------------

SET(SRC
  OysterMUX.cpp
  OysterMUX_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pOysterMUX ${SRC})

TARGET_LINK_LIBRARIES(pOysterMUX
   ${MOOS_LIBRARIES}
   mbutil
   m
   pthread)


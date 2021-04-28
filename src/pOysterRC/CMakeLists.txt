#--------------------------------------------------------
# The CMakeLists.txt for:                      pOysterRC
# Author(s):                                   Alon Yaari
#--------------------------------------------------------

FILE(GLOB SRC *.cpp)

ADD_EXECUTABLE(pOysterRC ${SRC})

TARGET_LINK_LIBRARIES(pOysterRC
   ${MOOS_LIBRARIES}
   mbutil
   m
   pthread)
   

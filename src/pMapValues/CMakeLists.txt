#--------------------------------------------------------
# The CMakeLists.txt for:                      pMapValues
# Author(s):                                   Alon Yaari
#--------------------------------------------------------

FILE(GLOB SRC *.cpp)

ADD_EXECUTABLE(pMapValues ${SRC})

TARGET_LINK_LIBRARIES(pMapValues
   ${MOOS_LIBRARIES}
   mbutil
   m
   pthread)
   

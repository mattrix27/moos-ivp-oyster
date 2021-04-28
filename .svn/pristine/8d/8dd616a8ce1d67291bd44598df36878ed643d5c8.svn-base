#--------------------------------------------------------
# The CMakeLists.txt for:                         iOS5000
# Author(s):                     Michael "Misha" Novitzky
#--------------------------------------------------------

FILE(GLOB SRC *.cpp)

ADD_EXECUTABLE(iOS5000 ${SRC})
   
TARGET_LINK_LIBRARIES(iOS5000 
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   SimpleSerial
   m
   pthread)

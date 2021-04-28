#--------------------------------------------------------
# The CMakeLists.txt for:                       iJoystick
# Author(s):                                   Alon Yaari
#--------------------------------------------------------

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

message ("library:  ${SDL2_LIBRARY} \n")
message ("includes:  ${SDL2_INCLUDE} \n")

FILE(GLOB SRC *.cpp)

ADD_EXECUTABLE(iJoystick ${SRC})

TARGET_LINK_LIBRARIES(iJoystick 
   ${MOOS_LIBRARIES}
   ${SDL2_LIBRARY}
   geometry
   mbutil
   m
   pthread)
   

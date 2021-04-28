#--------------------------------------------------------
# The CMakeLists.txt for:                       iBlinkstick
# Author(s):                              Hugh Dougherty
#--------------------------------------------------------

# FILE(GLOB SRC *.cpp)

SET(SRC
  Blinkstick.cpp
  Blinkstick_Info.cpp
  main.cpp
)



ADD_EXECUTABLE(iBlinkstick ${SRC})

TARGET_LINK_LIBRARIES(iBlinkstick
   ${MOOS_LIBRARIES}
   mbutil
   m
   pthread)


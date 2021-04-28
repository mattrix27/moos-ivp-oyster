#--------------------------------------------------------
# The CMakeLists.txt for:                       uFleetMon
# Author(s):                              
#--------------------------------------------------------

SET(SRC
  NetMon.cpp
  NetMon_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(uNetMon ${SRC})
set_target_properties(uNetMon PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

TARGET_LINK_LIBRARIES(uNetMon
   ${MOOS_LIBRARIES}
   mbutil
   m
   pthread
   ncurses)


#--------------------------------------------------------
# The CMakeLists.txt for:                       pNodeReportParse
# Author(s):                              Arjun Gupta
#--------------------------------------------------------

SET(SRC
  NodeReportParse.cpp
  NodeReportParse_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pNodeReportParse ${SRC})

TARGET_LINK_LIBRARIES(pNodeReportParse
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread)


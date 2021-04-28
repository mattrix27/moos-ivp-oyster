#--------------------------------------------------------
# The CMakeLists.txt for:                       pCamViewer
# Author(s):                              Simon Andrews
#--------------------------------------------------------

SET(SRC
  CamViewer.cpp
  CamViewer_Info.cpp
  main.cpp
)

find_package(OpenCV REQUIRED)

ADD_EXECUTABLE(pCamViewer ${SRC})

TARGET_LINK_LIBRARIES(pCamViewer
   ${MOOS_LIBRARIES}
   mbutil
   m
   pthread
   ${OpenCV_LIBS}
)


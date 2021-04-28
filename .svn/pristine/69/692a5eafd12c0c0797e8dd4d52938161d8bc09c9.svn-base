#--------------------------------------------------------
# The CMakeLists.txt for:                       iWebCam
# Author(s):                              Michael DeFilippo
#--------------------------------------------------------

SET(SRC
  FPSTracker.cpp
  WebCam.cpp
  WebCam_Info.cpp
  main.cpp
)

# mjd
#find_package( OpenCV)
find_package(OpenCV REQUIRED)

ADD_EXECUTABLE(iWebCam ${SRC})

TARGET_LINK_LIBRARIES(iWebCam
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread
# mjd
   ${MOOS_DEPEND_LIBRARIES}
   ${OpenCV_LIBS})



include_directories( ${MOOS_INCLUDE_DIRS} ${MOOS_DEPEND_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})


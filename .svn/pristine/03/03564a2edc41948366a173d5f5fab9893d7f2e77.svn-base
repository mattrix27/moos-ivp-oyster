#--------------------------------------------------------
# The CMakeLists.txt for:                    app_zaic_hdg
# Author(s):                                Mike Benjamin
#--------------------------------------------------------
if(CMAKE_SYSTEM_NAME STREQUAL Linux)
  SET(SYSTEM_LIBS ${SYSTEM_LIBS} GL)
endif(CMAKE_SYSTEM_NAME STREQUAL Linux)

SET(SRC
  GrepHandler.cpp
  main.cpp
)

ADD_EXECUTABLE(aq_analysis ${SRC})

TARGET_LINK_LIBRARIES(aq_analysis
  mbutil
  logutils
  fltk 
  fltk_gl
  zaicview
  dl
  ${SYSTEM_LIBS}
  m
)

# http://developer.apple.com/qa/qa2007/qa1567.html
IF (${APPLE})
  SET_TARGET_PROPERTIES(aq_analysis PROPERTIES	  
    LINK_FLAGS "-framework OpenGL -framework AGL -framework Cocoa"
    )
ENDIF (${APPLE})


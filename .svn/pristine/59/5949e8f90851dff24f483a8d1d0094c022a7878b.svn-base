#--------------------------------------------------------
# The CMakeLists.txt for:                  uFldTagManager
# Author(s):                                Mike Benjamin
#--------------------------------------------------------

# Set System Specific Libraries
SET(SYSTEM_LIBS m pthread)

SET(SRC
   TagManager.cpp
   TagManager_Info.cpp
   VTag.cpp
   main.cpp
)

ADD_EXECUTABLE(uFldTagManager ${SRC})

TARGET_LINK_LIBRARIES(uFldTagManager
  ${MOOS_LIBRARIES}
  apputil
  geometry 
  mbutil
  contacts
  ${SYSTEM_LIBS}
)


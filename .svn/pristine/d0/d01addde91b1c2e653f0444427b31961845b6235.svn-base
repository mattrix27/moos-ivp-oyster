#--------------------------------------------------------
# The CMakeLists.txt for:                 uFldFlagManager
# Author(s):                                Mike Benjamin
#--------------------------------------------------------

SET(SRC
  FlagManager.cpp
  FlagManager_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(uFldFlagManager ${SRC})

TARGET_LINK_LIBRARIES(uFldFlagManager
   ${MOOS_LIBRARIES}
   apputil
   contacts
   geometry
   mbutil
   m
   pthread)


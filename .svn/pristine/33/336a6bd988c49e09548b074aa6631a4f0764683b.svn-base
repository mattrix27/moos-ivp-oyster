#===========================================================================
# FILE:  CMakeLists.txt for pRangeEvent
# DATE:  2016/03/15
# NAME:  Mohamed Saad Ibn Seddik
#===========================================================================

SET(SRC
  RangeEvent.cpp
  RangeEvent_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pRangeEvent ${SRC})

TARGET_LINK_LIBRARIES(pRangeEvent
  MOOS
  contacts
  geometry
  apputil
  mbutil
  ${SYSTEM_LIBS}
)

#--------------------------------------------------------
# The CMakeLists.txt for:                       uFldZoneEvent
# Author(s):
#--------------------------------------------------------

SET(SRC
  ZoneEvent.cpp
  ZoneEvent_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(uFldZoneEvent ${SRC})

TARGET_LINK_LIBRARIES(uFldZoneEvent
  ${MOOS_LIBRARIES}
  apputil
  geometry
  mbutil
  contacts
  ${SYSTEM_LIBS}
)

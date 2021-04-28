#--------------------------------------------------------
# The CMakeLists.txt for:                       pOysterESC
# Author(s):                              Matt Tung
#--------------------------------------------------------

find_package(Boost COMPONENTS thread system REQUIRED)

SET(SRC
  OysterESC.cpp
  OysterESC_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pOysterESC ${SRC})

include_directories(${Boost_INCLUDE_DIRS})

TARGET_LINK_LIBRARIES(pOysterESC
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread
   ${Boost_THREAD_LIBRARY}
   ${Boost_SYSTEM_LIBRARY}
   )


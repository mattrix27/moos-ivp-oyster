#--------------------------------------------------------
# The CMakeLists.txt for:                     catauthkeys
# Author(s):                                Mike Benjamin
#--------------------------------------------------------

# Set System Specific Libraries
if (${WIN32})
  SET(SYSTEM_LIBS
    wsock32)
else (${WIN32})
  SET(SYSTEM_LIBS
    m)
endif (${WIN32})

SET(SRC main.cpp CatHandler.cpp)

ADD_EXECUTABLE(catauthkeys ${SRC})
   
TARGET_LINK_LIBRARIES(catauthkeys
  mbutil
  ${SYSTEM_LIBS})

# Install Targets
INSTALL(TARGETS catauthkeys
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)


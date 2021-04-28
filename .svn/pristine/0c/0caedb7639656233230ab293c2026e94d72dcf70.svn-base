#--------------------------------------------------------
# The CMakeLists.txt for:                  lib_colregs_aq
#                                      and BHV_AvdColregs
# Author(s):                                Mike Benjamin
#--------------------------------------------------------

# Set System Specific Libraries
if (${WIN32})
  # Windows Libraries
  SET(SYSTEM_LIBS
      )
else (${WIN32})
  # Linux and Apple Libraries
  SET(SYSTEM_LIBS
      m )
endif (${WIN32})

#--------------------------------------------------------
#                                     BHV_OpRegionRecover
#--------------------------------------------------------
ADD_LIBRARY(BHV_OpRegionRecover SHARED 
   BHV_OpRegionRecover.cpp
)
TARGET_LINK_LIBRARIES(BHV_OpRegionRecover
   helmivp 
   behaviors 
   ivpbuild 
   logic 
   ivpcore 
   bhvutil 
   mbutil 
   geometry 
   ${SYSTEM_LIBS} )


#--------------------------------------------------------
#                                        BHV_Defense_Multi
#--------------------------------------------------------
ADD_LIBRARY(BHV_Defense_Multi SHARED
   BHV_Defense_Multi.cpp NodeReport.cpp)
TARGET_LINK_LIBRARIES(BHV_Defense_Multi
   helmivp
   behaviors
   ivpbuild
   logic
   ivpcore
   bhvutil
   mbutil
   geometry
   ${SYSTEM_LIBS} )

#--------------------------------------------------------
#                                       BHV_Defense_Cover
#--------------------------------------------------------
ADD_LIBRARY(BHV_Cover SHARED
   BHV_Cover.cpp NodeReport.cpp)
TARGET_LINK_LIBRARIES(BHV_Cover
   helmivp
   behaviors
   ivpbuild
   logic
   ivpcore
   bhvutil
   mbutil
   geometry
   ${SYSTEM_LIBS} )

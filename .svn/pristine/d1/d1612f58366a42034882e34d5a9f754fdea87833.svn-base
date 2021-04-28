##############################################################################
# FILE:        moos-ivp-extend/src/CMakeLists.txt
# DATE:        2010/09/07
# DESCRIPTION: CMakeLists.txt file for the moos-ivp-extend source directory
##############################################################################


#============================================================================
# Add the libraries in the current directory to the include path
#============================================================================
FILE(GLOB LOCAL_LIBRARY_DIRS ./lib_*)
INCLUDE_DIRECTORIES(${LOCAL_LIBRARY_DIRS})

#============================================================================
# option for minimal and full compilation
#============================================================================
option(BUILD_ALL "Build all apps." ON)


#============================================================================
 # List the subdirectories to build...

ADD_SUBDIRECTORY(lib_behaviors-aq)
ADD_SUBDIRECTORY(pNodeReportParse)
ADD_SUBDIRECTORY(pRangeEvent)
ADD_SUBDIRECTORY(uFldTagManager)
ADD_SUBDIRECTORY(uFldFlagManager)
ADD_SUBDIRECTORY(uFldZoneEvent)

##############################################################################
#                           END of CMakeLists.txt
##############################################################################

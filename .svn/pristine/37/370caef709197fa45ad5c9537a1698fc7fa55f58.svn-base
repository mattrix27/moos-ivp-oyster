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

ADD_SUBDIRECTORY(lib_SimpleSerial)
ADD_SUBDIRECTORY(lib_NMEAParse)
ADD_SUBDIRECTORY(lib_gpsParser)


ADD_SUBDIRECTORY(iGPSDevice)
ADD_SUBDIRECTORY(iOS5000)
ADD_SUBDIRECTORY(iLEDInfoBar)
ADD_SUBDIRECTORY(iButtonBox)
ADD_SUBDIRECTORY(iLEDInterpreter)



ADD_SUBDIRECTORY(iM200)


##############################################################################
#                           END of CMakeLists.txt
##############################################################################

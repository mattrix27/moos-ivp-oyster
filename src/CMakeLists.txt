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

ADD_SUBDIRECTORY(pMapValues)
ADD_SUBDIRECTORY(iJoystick)
ADD_SUBDIRECTORY(pOysterESC)
ADD_SUBDIRECTORY(pOysterMUX)
ADD_SUBDIRECTORY(pOysterRC)
ADD_SUBDIRECTORY(pOysterROS)
ADD_SUBDIRECTORY(iNetNMEAClient)
ADD_SUBDIRECTORY(iNetNMEAServer)

##############################################################################
#                           END of CMakeLists.txt
##############################################################################

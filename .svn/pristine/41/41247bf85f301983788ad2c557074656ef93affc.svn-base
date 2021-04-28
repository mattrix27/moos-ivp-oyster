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

IF(BUILD_VOIP)
  ADD_SUBDIRECTORY(iMumbleClient)
ENDIF()

#  ADD_SUBDIRECTORY(pComms_client)
#  ADD_SUBDIRECTORY(pComms_server)
IF(BUILD_SPEECH)
ADD_SUBDIRECTORY(uSpeechRec)
ADD_SUBDIRECTORY(uDialogManager)

ADD_SUBDIRECTORY(pRecord)
ADD_SUBDIRECTORY(pRecord2)
ENDIF()

ADD_SUBDIRECTORY(pBotDialog)

##############################################################################
#                           END of CMakeLists.txt
##############################################################################

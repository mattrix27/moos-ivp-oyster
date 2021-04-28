##############################################################################
# FILE:        CMakeLists.txt
##############################################################################

#============================================================================
# Add the libraries in the current directory to the include path
#============================================================================
FILE(GLOB LOCAL_LIBRARY_DIRS ./lib_*)
INCLUDE_DIRECTORIES(${LOCAL_LIBRARY_DIRS})

FILE(GLOB LOCAL_LIBRARY_ATTIC_DIRS ../src/lib_*)
INCLUDE_DIRECTORIES(${LOCAL_LIBRARY_ATTIC_DIRS})

#============================================================================
# List the subdirectories to build...
#============================================================================
ADD_SUBDIRECTORY(lib_clearpath)
ADD_SUBDIRECTORY(iClapboard)
ADD_SUBDIRECTORY(iHealth_KF100)
#ADD_SUBDIRECTORY(iActuationKFAC)
ADD_SUBDIRECTORY(pFlagStrategy)
ADD_SUBDIRECTORY(iGPSSim)
ADD_SUBDIRECTORY(iuModemMP)
ADD_SUBDIRECTORY(pEvalLoiter)
ADD_SUBDIRECTORY(pFlagStrategy)
ADD_SUBDIRECTORY(uJSON)

##############################################################################
#                           END of CMakeLists.txt
##############################################################################

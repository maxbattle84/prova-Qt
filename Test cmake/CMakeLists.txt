#==============================================================================
#  Project definition
#==============================================================================

PROJECT (TestSum)

#==============================================================================
#  General stuff
#==============================================================================
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/")
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)

MESSAGE("Cmake is running on an " ${CMAKE_HOST_SYSTEM_PROCESSOR} " processor, under " ${CMAKE_HOST_SYSTEM_NAME} " " ${CMAKE_HOST_SYSTEM_VERSION})

SET(BUILD_INFORMATIONS "using ")


if(MSVC)
   # Determining Visual Studio Version
   SET(BUILD_INFORMATIONS ${BUILD_INFORMATIONS} " Microsoft Visual Studio")

   if(${MSVC_VERSION} EQUAL 1300)
      SET(BUILD_INFORMATIONS ${BUILD_INFORMATIONS} " 6")
   elseif(${MSVC_VERSION} EQUAL 1400)
      SET(BUILD_INFORMATIONS ${BUILD_INFORMATIONS} " 2005")
   elseif(${MSVC_VERSION} EQUAL 1500)
      SET(BUILD_INFORMATIONS ${BUILD_INFORMATIONS} " 2008")
   else(${MSVC_VERSION} EQUAL 1300)
      SET(BUILD_INFORMATIONS ${BUILD_INFORMATIONS} " unknown version(" ${MSVC_VERSION} ")")
   endif(${MSVC_VERSION} EQUAL 1300)
   # Determining if in 32/64 bit mode.
   if(CMAKE_CL_64)
      SET(BUILD_INFORMATIONS ${BUILD_INFORMATIONS} " in 64 bit")
   else(CMAKE_CL_64)
      SET(BUILD_INFORMATIONS ${BUILD_INFORMATIONS} " in 32 bit")
   endif(CMAKE_CL_64)
   
   # set custom VS flags
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251")
   
else(MSVC)
   SET(BUILD_INFORMATIONS ${BUILD_INFORMATIONS} " NOT SET IN THE PROJECT CMAKE...")
endif(MSVC)

MESSAGE("Cmake is compiling for an " ${CMAKE_SYSTEM_PROCESSOR} " processor, for " ${CMAKE_SYSTEM_NAME} " " ${CMAKE_SYSTEM_VERSION} " " ${BUILD_INFORMATIONS})
   
MESSAGE( STATUS "CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR} )
MESSAGE( STATUS "CMAKE_BINARY_DIR:         " ${CMAKE_BINARY_DIR} )
MESSAGE( STATUS "PROJECT_BINARY_DIR:       " ${PROJECT_BINARY_DIR} )

#==============================================================================
#  REMOVE(/CUSTOMIZE) Platform features
#==============================================================================

if(BUILD_FOLDER_HACK)
   SET(OUTPUTPATH ${CMAKE_CURRENT_SOURCE_DIR})
else(BUILD_FOLDER_HACK)
   SET(OUTPUTPATH ${PROJECT_BINARY_DIR})
endif(BUILD_FOLDER_HACK)

# First for the generic no-config case (e.g. with mingw)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUTPATH}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUTPATH}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUTPATH}/lib)
# Second, for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

SET(CMAKE_DEBUG_POSTFIX "d")

MESSAGE( STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY:      " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
MESSAGE( STATUS "CMAKE_LIBRARY_OUTPUT_DIRECTORY:      " ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )
MESSAGE( STATUS "CMAKE_ARCHIVE_OUTPUT_DIRECTORY:      " ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} )

#Use solution folders.
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

#==============================================================================
#  Package(s) import
#==============================================================================

#Run FindQt4.cmake
FIND_PACKAGE(Qt4 REQUIRED)

#==============================================================================
#  Project include(s) folder(s)
#==============================================================================
INCLUDE_DIRECTORIES(
   ${TestSum_SOURCE_DIR}

   #defined in FindQt4.cmake
   ${QT_INCLUDE_DIR}      #QT headers   
)


#==============================================================================
#  Project librarie(s) folder(s)
#==============================================================================
LINK_DIRECTORIES(
   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
   ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}

   #defined in FindQt4.cmake
   ${QT_LIBRARY_DIR}      #QT libraries
)
 
#==============================================================================
#  QT4 Libraries
#==============================================================================
# variables defined in FindQt4.cmake
SET( QT4_LIBS 
   optimized ${QT_QTCORE_LIBRARY_RELEASE}               debug ${QT_QTCORE_LIBRARY_DEBUG}
   optimized ${QT_QTGUI_LIBRARY_RELEASE}               debug ${QT_QTGUI_LIBRARY_DEBUG}
   optimized ${QT_QTOPENGL_LIBRARY_RELEASE}            debug ${QT_QTOPENGL_LIBRARY_DEBUG}
   optimized ${QT_QTWEBKIT_LIBRARY_RELEASE}            debug ${QT_QTWEBKIT_LIBRARY_DEBUG}
   optimized ${QT_QTNETWORK_LIBRARY_RELEASE}            debug ${QT_QTNETWORK_LIBRARY_DEBUG}
)

# platform dependent libraries
IF(WIN32)
   SET(QT4_LIBS
   ${QT4_LIBS}
   optimized ${QT_QTMAIN_LIBRARY_RELEASE}               debug ${QT_QTMAIN_LIBRARY_DEBUG}
#   optimized ${QT_QAXSERVER_LIBRARY_RELEASE}            debug ${QT_QAXSERVER_LIBRARY_DEBUG}
#   optimized ${QT_QAXCONTAINER_LIBRARY_RELEASE}         debug ${QT_QAXCONTAINER_LIBRARY_DEBUG}
   )
ENDIF(WIN32)



#//PROJECT///////////////////////////////////////////////////////////////////////
#==============================================================================
#  TestSum project
#==============================================================================

# ------------------------------------
# - Define application name
# ------------------------------------

SET( TestSum_NAME TestSum)
SET( QT_PROJECT_FILE ${TestSum_NAME}.pro)

# ------------------------------------
# - Define application header path
# ------------------------------------
 
SET(HEADER_PATH ${TestSum_SOURCE_DIR})

# ------------------------------------
# - Enable QT Designer options
# ------------------------------------

SET(QT_USE_QTDESIGNER TRUE)

# ------------------------------------
# - Define application source(s) file(s)
# ------------------------------------

FILE(GLOB TestSum_SRCS "*.cpp")
FILE(GLOB TestSum_VIEWS_SRCS "views/*.cpp")

# ------------------------------------
# - Define application header(s) file(s)
# ------------------------------------
FILE(GLOB TestSum_HDRS "*.h")
FILE(GLOB TestSum_VIEWS_HDRS "views/*.h")

# ------------------------------------
# - Define designer resource file(s) [*.qrc]
# ------------------------------------

SET( TestSum_RCC
   resources/res.qrc
)
QT4_ADD_RESOURCES( TestSum_RCC_SRCS
   ${TestSum_RCC}
)

# ------------------------------------
# - Define designer ui source(s) file(s) [*.ui]
# ------------------------------------

FILE(GLOB TestSum_UI "ui/*.ui")

QT4_WRAP_UI( TestSum_UI_HDRS
   ${TestSum_UI}
)

# ------------------------------------
# - Define QT translation file(s) [*.ts]
# ------------------------------------

FILE(GLOB TestSum_TS "resources/*.ts")

SET_SOURCE_FILES_PROPERTIES(${TestSum_TS} PROPERTIES OUTPUT_LOCATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

QT4_ADD_TRANSLATION( TestSum_TS_SRCS
   ${TestSum_TS}
)

# ------------------------------------
# - Define moc source(s) file(s)
# ------------------------------------

# Tell cmake to create .moc files for all files in the variable qtproject_SRCS that require such a file.
# Note: this assumes that you use #include "header.moc" in your files.

QT4_AUTOMOC(${TestSum_SRCS})
QT4_AUTOMOC(${TestSum_VIEWS_SRCS})

# Don't forget to include output directory, otherwise the UI file won't be wrapped!
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# ------------------------------------
# - Add custom foldering tags for VisualStudio project(s)
# ------------------------------------

IF (MSVC)
   SOURCE_GROUP("Designer Files" FILES ${TestSum_UI} ${TestSum_TS} ${TestSum_RCC} ${TestSum_SOURCE_DIR}/${QT_PROJECT_FILE})
   SOURCE_GROUP("Generated Files" FILES ${TestSum_RCC_SRCS} ${TestSum_TS_SRCS} ${TestSum_UI_HDRS} ${TestSum__MOC_SRCS})
   SOURCE_GROUP("Views" FILES ${TestSum_VIEWS_SRCS})
ENDIF (MSVC)

IF (MSVC)
   SET(ICON_STUFF
      ${TestSum_SOURCE_DIR}/resource.h
      ${TestSum_SOURCE_DIR}/resource.rc
   )
ENDIF (MSVC)

# ------------------------------------
# - Project files to build
# ------------------------------------

ADD_EXECUTABLE( ${TestSum_NAME}
   ${TestSum_SRCS}
   ${TestSum_VIEWS_SRCS}
   ${TestSum_HDRS}
   ${TestSum_VIEWS_HDRS}
   ${TestSum_RCC_SRCS}
   ${TestSum_TS_SRCS}
   ${TestSum_UI_HDRS}
   ${TestSum_MOC_HDRS}
   ${TestSum__MOC_SRCS}
   ${ICON_STUFF}
)

SET_TARGET_PROPERTIES(${TestSum_NAME} PROPERTIES FOLDER "${TARGET_DEFAULT_LABEL_PREFIX}")

SET_TARGET_PROPERTIES(${TestSum_NAME} PROPERTIES DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}")

# ------------------------------------
# - Little hack to get the .exe into /bin
# ------------------------------------

IF (MSVC AND FOLDER_HACK)
  SET_TARGET_PROPERTIES(${TestSum_NAME} PROPERTIES PREFIX "../")
ENDIF (MSVC AND FOLDER_HACK)

# ------------------------------------
# - Define link libraries
# ------------------------------------

SET( TestSum_EXT_LIBS
   ${QT4_LIBS}
   optimized ${QT_QTXML_LIBRARY_RELEASE}          debug ${QT_QTXML_LIBRARY_DEBUG}
   optimized ${QT_QTXMLPATTERNS_LIBRARY_RELEASE}  debug ${QT_QTXMLPATTERNS_LIBRARY_DEBUG}
)

TARGET_LINK_LIBRARIES(${TestSum_NAME} ${TestSum_EXT_LIBS})


#==============================================================================
# Installer
#==============================================================================
# Add stuff that needs to be packaged in the installer

INSTALL(TARGETS ${TestSum_NAME}
   RUNTIME
   DESTINATION bin
   COMPONENT applications
)
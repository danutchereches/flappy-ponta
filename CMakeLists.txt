cmake_minimum_required(VERSION 2.6)

set(APP_NAME flappy-ponta)
project (${APP_NAME})

include(cocos2d/build/BuildHelpers.CMakeLists.txt)

option(USE_CHIPMUNK "Use chipmunk for physics library" ON)
option(USE_BOX2D "Use box2d for physics library" OFF)
option(DEBUG_MODE "Debug or release?" ON)

if(DEBUG_MODE)
  set(CMAKE_BUILD_TYPE DEBUG)
else(DEBUG_MODE)
  set(CMAKE_BUILD_TYPE RELEASE)
endif(DEBUG_MODE)

if (MSVC)
	set(CMAKE_C_FLAGS_DEBUG "-DCOCOS2D_DEBUG=1")
	set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})

	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_CRT_SECURE_NO_WARNINGS")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS")

elseif (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_C_FLAGS_DEBUG "-g -Wall -DCOCOS2D_DEBUG=1")
	set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})

	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

endif()

add_definitions(-DLINUX)

if(USE_CHIPMUNK)
  message("Using chipmunk ...")
  add_definitions(-DCC_ENABLE_CHIPMUNK_INTEGRATION=1)
elseif(USE_BOX2D)
  message("Using box2d ...")
  add_definitions(-DCC_ENABLE_BOX2D_INTEGRATION=1)
endif(USE_CHIPMUNK)

# architecture
if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
set(ARCH_DIR "64-bit")
else()
set(ARCH_DIR "32-bit")
endif()

set(PLATFORM_SRC
  proj.linux/main.cpp
)

set(
GAME_SRC
  Classes/Helpers.cpp
  Classes/Objects.cpp
  Classes/Loader.cpp
  Classes/BackgroundLayer.cpp
  Classes/BirdSprite.cpp
  Classes/GameLayer.cpp
  Classes/GameScene.cpp
  Classes/LoadingScene.cpp
  Classes/MenuScene.cpp
  Classes/Number.cpp
  Classes/OptionLayer.cpp
  Classes/StatusLayer.cpp
  Classes/UserRecord.cpp
  Classes/WelcomeLayer.cpp
  Classes/WelcomeScene.cpp
  Classes/AppDelegate.cpp
  ${PLATFORM_SRC}
)
set(COCOS2D_ROOT ${CMAKE_SOURCE_DIR}/cocos2d)

include_directories(
  /usr/local/include/GLFW
  ${COCOS2D_ROOT}
  ${COCOS2D_ROOT}/cocos
  ${COCOS2D_ROOT}/cocos/audio/include
  ${COCOS2D_ROOT}/cocos/platform
  ${COCOS2D_ROOT}/cocos/platform/desktop
  ${COCOS2D_ROOT}/cocos/platform/linux
  ${COCOS2D_ROOT}/cocos/editor-support
  ${COCOS2D_ROOT}/external
  ${COCOS2D_ROOT}/external/edtaa3func
  ${COCOS2D_ROOT}/external/jpeg/include/linux
  ${COCOS2D_ROOT}/external/tiff/include/linux
  ${COCOS2D_ROOT}/external/webp/include/linux
  ${COCOS2D_ROOT}/external/tinyxml2
  ${COCOS2D_ROOT}/external/unzip
  ${COCOS2D_ROOT}/external/freetype2/include/linux
  ${COCOS2D_ROOT}/external/websockets/include/linux
  ${COCOS2D_ROOT}/external/linux-specific/fmod/include/${ARCH_DIR}
  ${COCOS2D_ROOT}/external/xxhash
  ${COCOS2D_ROOT}/plugin/protocols/include/
)

link_directories(
  /usr/local/lib
  ${COCOS2D_ROOT}/external/jpeg/prebuilt/linux/${ARCH_DIR}
  ${COCOS2D_ROOT}/external/tiff/prebuilt/linux/${ARCH_DIR}
  ${COCOS2D_ROOT}/external/webp/prebuilt/linux/${ARCH_DIR}
  ${COCOS2D_ROOT}/external/freetype2/prebuilt/linux/${ARCH_DIR}
  ${COCOS2D_ROOT}/external/websockets/prebuilt/linux/${ARCH_DIR}
  ${COCOS2D_ROOT}/external/linux-specific/fmod/prebuilt/${ARCH_DIR}
)

if(USE_CHIPMUNK)
	include_directories(${COCOS2D_ROOT}/external/chipmunk/include/chipmunk)
	# chipmunk library
	add_subdirectory(${COCOS2D_ROOT}/external/chipmunk/src)
endif()

if(USE_BOX2D)
	# box2d library
	add_subdirectory(${COCOS2D_ROOT}/external/Box2D)
endif()

# unzip library
add_subdirectory(${COCOS2D_ROOT}/external/unzip)

# tinyxml2 library
add_subdirectory(${COCOS2D_ROOT}/external/tinyxml2)

# audio
add_subdirectory(${COCOS2D_ROOT}/cocos/audio)

# xxhash library
add_subdirectory(${COCOS2D_ROOT}/external/xxhash)

# cocos2d
add_subdirectory(${COCOS2D_ROOT}/cocos)

# plugin proto
add_subdirectory(${COCOS2D_ROOT}/plugin/protocols)

# add the executable
add_executable(${APP_NAME}
  ${GAME_SRC}
)

if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
set(FMOD_LIB "fmodex64")
else()
set(FMOD_LIB "fmodex")
endif()

target_link_libraries(${APP_NAME}
  audio
  cocos2d
  plugin_proto
  )

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin")

set_target_properties(${APP_NAME} PROPERTIES
     RUNTIME_OUTPUT_DIRECTORY  "${APP_BIN_DIR}")

pre_build(${APP_NAME}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
)

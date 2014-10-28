if (UNIX)
  set(PLATFORM_SRC
    platform/linux/ProtocolAnalytics.cpp
    platform/linux/ProtocolGameServices.cpp
    platform/linux/PluginFactory.cpp
    platform/linux/PluginProtocol.cpp
  )
endif()

#include_directories(
#  ..
#)

set(PLUGINPROTO_SRC
  PluginManager.cpp
  PluginParam.cpp
  ${PLATFORM_SRC}
)

add_library(plugin_proto STATIC
  ${PLUGINPROTO_SRC}
)

set_target_properties(plugin_proto
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

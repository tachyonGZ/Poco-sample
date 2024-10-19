add_executable (HelloWorld_websocket "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET HelloWorld_websocket PROPERTY CXX_STANDARD 17)
endif()
# SFML version >= 2.5
cmake_minimum_required(VERSION 3.1)


# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

project(videogame)

# Set version information in a config.h file
set(videogame_VERSION_MAJOR 0)
set(videogame_VERSION_MINOR 1)
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
include_directories("${PROJECT_BINARY_DIR}")

# file(GLOB SRC_FILES CONFIGURE_DEPENDS inc/*.hpp src/*.cpp)
set(SRC_FILES inc/constants.hpp inc/items.hpp inc/player.hpp inc/settings.hpp src/items.cpp src/player.cpp src/settings.cpp)

# Define sources and executable
set(EXECUTABLE_NAME "videogame")
add_executable(${EXECUTABLE_NAME} main.cpp ${SRC_FILES})


# Detect and add SFML

# SFML version >= 2.5
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")
# ex) If you are using debian10, 11, ubuntu20.24, 22.04 and installed with apt package manager, set the values below.
# set(SFML_DIR "/usr/local/vcpkg/ports/sfml/SFML")
# ex) If you are using Windows, manually set the location where you installed SFML.
# set(SFML_DIR "C:/Users/yourname/library/frameworks/SFML-2.5.1/lib/cmake/SFML")
# ex) If you are using MacOS and installed with homebrew, set the values as shown below.
# set(SFML_DIR "/usr/local/Cellar/sfml/2.5.1_1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS network audio graphics window system REQUIRED)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  # SFML version >= 2.5
  #In SFML Version 2.5 or later, ${SFML_LIBRARIES}, ${SFML_DEPENDENCIES}, ${SFML_INCLUDE_DIR} no longer exist. Specify libraries individually.
  target_link_libraries(${PROJECT_NAME} sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
endif()


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)


# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR "${videogame_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${videogame_VERSION_MINOR}")
include(CPack)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



enable_testing()  
set(TEST_FILES test/backendtests.cpp test/playertests.cpp test/settingtests.cpp)
add_executable(
  tester
  ${TEST_FILES}
  ${SRC_FILES}
)
target_link_libraries(tester GTest::gtest_main)
target_link_libraries(tester sfml-network sfml-audio sfml-graphics sfml-window sfml-system)

include(GoogleTest)
gtest_discover_tests(tester)
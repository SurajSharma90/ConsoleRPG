cmake_minimum_required(VERSION 3.12)
project(console_rpg)

# GoogleTest requires threading support
find_package(Threads REQUIRED)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Add the source files to the project
set(SOURCES
  src/Game.cpp
  src/Character.cpp
  src/Boss.cpp
  src/Enemy.cpp
  src/Event.cpp
  src/Inventory.cpp
  src/Item.cpp
  src/Armor.cpp
  src/Weapon.cpp
  src/Puzzle.cpp
  src/gui_functions.cpp
)

# Create the executable
add_executable(console_rpg 
  src/main.cpp
  ${SOURCES})

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# Include the Google Test library
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Add test executable
add_executable(runTests tests/ArmorTest.cpp ${SOURCES})
target_link_libraries(runTests gtest gtest_main Threads::Threads)

# Enables testing via the 'make test' command
enable_testing()
add_test(NAME runTests COMMAND runTests)
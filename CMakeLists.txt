cmake_minimum_required(VERSION 3.13.0)

if (NOT CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_LIST_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
            CACHE FILEPATH "CMake toolchain file")
    message(STATUS "vcpkg toolchain found: ${CMAKE_TOOLCHAIN_FILE}")
endif ()

project(cmake_vcpkg_solidity)
set (CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_BINARY_DIR}/solidity/src/solidity_project)

find_package(Threads)
find_package(jsoncpp CONFIG REQUIRED)
add_library(jsoncpp ALIAS JsonCpp::JsonCpp)
find_package(range-v3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

set(Boost_NO_WARN_NEW_VERSIONS 1)
find_package(Boost 1.81 COMPONENTS system filesystem program_options REQUIRED)

set(USE_SYSTEM_LIBRARIES ON CACHE INTERNAL "")
set(ONLY_BUILD_SOLIDITY_LIBRARIES ON CACHE INTERNAL "")
set(USE_Z3 OFF CACHE INTERNAL "")
set(STRICT_JSONCPP_VERSION OFF CACHE INTERNAL "")
include(FetchContent)
FetchContent_Declare(solidity_project
  GIT_REPOSITORY    git@github.com:ethereum/solidity.git
  GIT_TAG           improve_solidity_embeddability
)
FetchContent_MakeAvailable(solidity_project)

add_executable(cmake_vcpkg_solidity src/main.cpp)
target_link_libraries(cmake_vcpkg_solidity PRIVATE solidity evmasm langutil smtutil solutil jsoncpp yul Boost::boost Boost::program_options)

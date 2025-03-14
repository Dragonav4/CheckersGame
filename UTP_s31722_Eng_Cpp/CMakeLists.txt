cmake_minimum_required(VERSION 3.28)
project(s31722_Checkers_Engine)

set(CMAKE_CXX_STANDARD 20)

set(JAVA_HOME "/Users/dragonav/Library/Java/JavaVirtualMachines/openjdk-22.0.1/Contents/Home")

include_directories(${JAVA_HOME}/include)
include_directories(${JAVA_HOME}/include/darwin)



add_library(s31722_Checkers_Engine_lib SHARED
        GameState.h
        Piece.h
        Piece.cpp
        Board_GameStateJNI.cpp
        GameState.cpp)


find_package(JNI REQUIRED)
target_include_directories(s31722_Checkers_Engine_lib PRIVATE ${JNI_INCLUDE_DIRS})
target_link_libraries(s31722_Checkers_Engine_lib PRIVATE ${JNI_LIBRARIES})

cmake_minimum_required(VERSION 3.15)
project(DungeonRunner)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

set(CMAKE_CXX_STANDARD 11)

set(SFML_STATIC_LIBRARIES FALSE CACHE BOOL "Use static SFML librares")
if (${CMAKE_SYSTEM_NAME} MATCHES "WIN32")
    set(SFML_ROOT "C:/Users/Ilias/Documents/SFML")
endif()

if (SFML_STATIC_LIBRARIES)
    add_definitions(-DSFML_STATIC)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

    if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif()
endif()


# Path to FindSFML.cmake
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/" ${CMAKE_MODULE_PATH})

add_executable(DungeonRunner main.cpp Core/Logic/Entity.cpp Core/Logic/Entity.h Core/Logic/Player.cpp Core/Logic/Player.h Core/Representation/World.cpp Core/Representation/World.h Core/Game.cpp Core/Game.h Core/Representation/PlayerSFML.cpp Core/Representation/PlayerSFML.h Core/Logic/AbstractFactory.cpp Core/Logic/AbstractFactory.h Core/Logic/Transformation.cpp Core/Logic/Transformation.h Core/Logic/Door.cpp Core/Logic/Door.h Core/Representation/DoorSFML.cpp Core/Representation/DoorSFML.h Core/Logic/Random.cpp Core/Logic/Random.h Core/Logic/Collision.cpp Core/Logic/Collision.h Core/Logic/Sword.cpp Core/Logic/Sword.h Core/Representation/SwordSFML.cpp Core/Representation/SwordSFML.h Core/Logic/AIPlayer.cpp Core/Logic/AIPlayer.h Core/Representation/AIPlayerSFML.cpp Core/Representation/AIPlayerSFML.h Core/Representation/Animation.cpp Core/Representation/Animation.h Core/Representation/finishLine.cpp Core/Logic/Subject.cpp Core/Logic/Observer.cpp Core/Logic/Highscores.cpp  )

find_package(SFML 2 COMPONENTS audio graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(DungeonRunner ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
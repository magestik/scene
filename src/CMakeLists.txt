cmake_minimum_required(VERSION 3.9)

add_library(scene Object.cpp Object.h Scene.cpp Scene.h SceneListener.h Light/Light.cpp Light/Light.h Light/Directionnal.cpp Light/Directionnal.h Light/Omni.cpp Light/Omni.h Light/Spot.cpp Light/Spot.h Camera/Camera.cpp Camera/Camera.h)

target_link_libraries(scene PUBLIC containers linear-algebra)
target_include_directories(scene INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

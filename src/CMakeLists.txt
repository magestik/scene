cmake_minimum_required(VERSION 3.9)

set(SCENE_FILES Scene.cpp Scene.h SceneListener.h)
set(OBJECT_FILES Object.cpp Object.h)
set(LIGHT_FILES Light/Light.cpp Light/Light.h Light/Directionnal.cpp Light/Directionnal.h Light/Omni.cpp Light/Omni.h Light/Spot.cpp Light/Spot.h)
set(CAMERA_FILES Camera/Camera.cpp Camera/Camera.h)

set(IMPORTER_FILES Importer/Importer.cpp Importer/Importer.h)

add_library(scene ${SCENE_FILES} ${OBJECT_FILES} ${LIGHT_FILES} ${CAMERA_FILES} ${IMPORTER_FILES})

target_link_libraries(scene PUBLIC containers linear-algebra)
target_include_directories(scene INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Assimp
find_package(assimp REQUIRED)
target_link_libraries(scene PRIVATE ${assimp_LIBRARIES})


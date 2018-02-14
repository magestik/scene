cmake_minimum_required(VERSION 3.9)

set(SCENE_FILES Scene.cpp Scene.h SceneListener.h)
set(RESOURCE_MANAGER_FILES Resources/ResourceManager.cpp Resources/ResourceManager.h Resources/ResourceManagerListener.h Resources/ResourceFormats.h)
set(OBJECT_FILES Objects/Object.cpp Objects/Object.h)
set(LIGHT_FILES Objects/Light/Light.cpp Objects/Light/Light.h Objects/Light/Directionnal.cpp Objects/Light/Directionnal.h Objects/Light/Omni.cpp Objects/Light/Omni.h Objects/Light/Spot.cpp Objects/Light/Spot.h)
set(CAMERA_FILES Objects/Camera/Camera.cpp Objects/Camera/Camera.h)

set(IMPORTER_FILES Importer/Importer.cpp Importer/Importer.h)

add_library(scene ${SCENE_FILES} ${RESOURCE_MANAGER_FILES} ${OBJECT_FILES} ${LIGHT_FILES} ${CAMERA_FILES} ${IMPORTER_FILES})

target_link_libraries(scene PUBLIC containers linear-algebra)
target_include_directories(scene INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Assimp
find_package(assimp REQUIRED)
target_link_libraries(scene PRIVATE ${ASSIMP_LIBRARIES})

# FreeImage
find_package(FreeImage REQUIRED)
target_link_libraries(scene PRIVATE ${FreeImage_LIBRARY})


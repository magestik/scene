cmake_minimum_required(VERSION 3.9)

set(SCENE_FILES Scene.cpp Scene.h SceneListener.h)
set(RESOURCE_MANAGER_FILES Resources/ResourceManager.cpp Resources/ResourceManager.h Resources/ResourceManagerListener.h Resources/ResourceData.h Resources/ResourceFormats.h)
set(VOLUMES_FILES Volumes/BoundingBox.cpp Volumes/BoundingBox.h Volumes/BoundingSphere.cpp Volumes/BoundingSphere.h)

set(OBJECT_FILES Objects/Object.cpp Objects/Object.h)
set(LIGHT_FILES Objects/Light/Light.cpp Objects/Light/Light.h Objects/Light/Directionnal.cpp Objects/Light/Directionnal.h Objects/Light/Omni.cpp Objects/Light/Omni.h Objects/Light/Spot.cpp Objects/Light/Spot.h)
set(CAMERA_FILES Objects/Camera/Camera.cpp Objects/Camera/Camera.h)

set(IMPORTER_FILES Importer/Importer.cpp Importer/Importer.h)

add_library(scene ${SCENE_FILES} ${RESOURCE_MANAGER_FILES} ${VOLUMES_FILES} ${OBJECT_FILES} ${LIGHT_FILES} ${CAMERA_FILES} ${IMPORTER_FILES})

target_link_libraries(scene PUBLIC containers linear-algebra)
target_include_directories(scene INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Assimp
find_package(assimp REQUIRED)
target_link_libraries(scene PRIVATE ${assimp_LIBRARIES})
target_include_directories(scene PRIVATE ${assimp_INCLUDE_DIRS})

# FreeImage
find_package(FreeImage REQUIRED)
target_link_libraries(scene PRIVATE ${FreeImage_LIBRARY})
target_include_directories(scene PRIVATE ${FreeImage_INCLUDE_DIR})

unset(aiLightSource_AMBIENT_EXISTS CACHE)

include(CheckCXXSourceCompiles)

CHECK_CXX_SOURCE_COMPILES("#include <assimp/light.h>
    static_assert(aiLightSource_AMBIENT == 0x4);
    int main() { return(0); }" HAVE_aiLightSource_AMBIENT)

CHECK_CXX_SOURCE_COMPILES("#include <assimp/light.h>
    static_assert(aiLightSource_AREA == 0x5);
    int main() { return(0); }" HAVE_aiLightSource_AREA)

configure_file(config.h.in config.h)

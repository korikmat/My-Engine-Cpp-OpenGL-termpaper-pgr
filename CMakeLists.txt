cmake_minimum_required(VERSION 3.22)
project(project)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE src/main.cpp
        src/window/Window.cpp
        src/window/Window.h
        src/window/Events.cpp
        src/window/Events.h
        src/graphics/Shader.cpp
        src/graphics/Shader.h
        src/graphics/Texture.cpp
        src/graphics/Texture.h
        src/window/Camera.cpp
        src/window/Camera.h
        src/graphics/models/Mesh.cpp
        src/graphics/models/Mesh.h
        src/graphics/models/Model.cpp
        src/graphics/models/Model.h
        src/scene/Scene.cpp
        src/scene/Scene.h
        src/graphics/SkyBox.cpp
        src/graphics/SkyBox.h
        src/loaders/ModelLoader.cpp
        src/loaders/ModelLoader.h
        src/loaders/TextureLoader.cpp
        src/loaders/TextureLoader.h
        src/graphics/AxesCrosshair.cpp
        src/graphics/AxesCrosshair.h
        src/graphics/gBuffer.cpp
        src/graphics/gBuffer.h
        src/graphics/TextureCubeArray.cpp
        src/graphics/TextureCubeArray.h
        src/graphics/lighting/Lighting.cpp
        src/graphics/lighting/Lighting.h
        src/graphics/lighting/Light.cpp
        src/graphics/lighting/Light.h
        src/graphics/hud/Batch2D.cpp
        src/graphics/hud/Batch2D.h
        src/graphics/hud/Font.cpp
        src/graphics/hud/Font.h
        src/graphics/hud/UVRegion.cpp
        src/graphics/hud/UVRegion.h
        src/renderers/HudRenderer.cpp
        src/renderers/HudRenderer.h
        src/graphics/models/TVScreen.cpp
        src/graphics/models/TVScreen.h
        src/class_factory/ClassFactory.cpp
        src/class_factory/ClassFactory.h
        src/graphics/models/Terrain.cpp
        src/graphics/models/Terrain.h
        src/graphics/models/TVModel.cpp
        src/graphics/models/TVModel.h
        src/graphics/lighting/Fog.cpp
        src/graphics/lighting/Fog.h
        src/loaders/FileSaver.cpp
        src/loaders/FileSaver.h
        src/renderers/Renderer.cpp
        src/renderers/Renderer.h
        src/animation/AnimationPoint.cpp
        src/animation/AnimationPoint.h
        src/animation/Animator.cpp
        src/animation/Animator.h
        src/hardcode/tv.cpp
        src/hardcode/tv.h)

if(WIN32)
    add_compile_options("-Wall" "-g3" "-O0")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

    set(GLFW_DIR external/glfw-3.3.9)
    set(GLEW_DIR external/glew-2.2.0)
    set(DEVIL_DIR external/devil)
    set(GLM_DIR external)
    set(ASSIMP_DIR external/assimp-5.3.1)

    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIRS} ${GLFW_DIR}/include ${GLEW_DIR}/include ${DEVIL_DIR}/include ${GLM_DIR} ${ASSIMP_DIR}/include)

    configure_file(${CMAKE_SOURCE_DIR}/${DEVIL_DIR}/lib/x64/Release/DevIL.dll ${CMAKE_BINARY_DIR} COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/${GLEW_DIR}/bin/Release/x64/glew32.dll ${CMAKE_BINARY_DIR} COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/${ASSIMP_DIR}/bin/libassimp-5.dll ${CMAKE_BINARY_DIR} COPYONLY)

    link_directories(${GLEW_DIR}/lib/Release/x64)
    link_directories(${GLFW_DIR}/lib-mingw-w64)
    link_directories(${DEVIL_DIR}/lib/x64/Release)
    link_directories(${ASSIMP_DIR}/lib)
    link_directories(${ASSIMP_DIR}/contrib/zlib)

    add_executable(project ${SOURCE})
    target_link_libraries(project ${OPENGL_LIBRARIES} glew32 glfw3 devil assimp zlibstatic)

#elseif(UNIX)
#    add_compile_options("-Wall" "-g3" "-O0")
#
#    set(GLM_DIR external)
#
#    find_package(OpenGL REQUIRED)
#    find_package(glfw3 REQUIRED)
#    find_package(GLEW REQUIRED)
#    find_package(DevIL REQUIRED)
#    find_package(assimp REQUIRED)
#
#    include_directories(${GLM_DIR})
#
#
#    add_executable(project ${SOURCE})
#    target_link_libraries(project ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${ASSIMP_LIBRARIES} glfw IL ILU ILUT)
endif()

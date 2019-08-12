cmake_minimum_required(VERSION 3.13)
project(rayTracerProject)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(rayTracerProject
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/Makefile
        cmake-build-debug/rayTracerProject.cbp
        include/aabb.h
        include/boxCanHit.h
        include/bvhNode.h
        include/camera.h
        include/canHitGeneric.h
        include/canHitGenericList.h
        include/checkerBoardTexture.h
        include/constantMedium.h
        include/constantTexture.h
        include/dielectricMaterial.h
        include/diffuseLightMaterial.h
        include/diffuseMaterial_Lambertian.h
        include/flipNormals.h
        include/imageTexture.h
        include/isotrophic.h
        include/material.h
        include/metalMaterial.h
        include/OBJ.h
        include/ray.h
        include/rectangleCanHit.h
        include/rotateY.h
        include/sphereCanHit.h
        include/texture.h
        include/translate.h
        include/triangleCanHit.h
        include/vec3.h
        include/xzRectangleCanHit.h
        include/yzRectangleCanHit.h
        src/main.cpp
        src/obj.cpp
        build.py
        bunny_centered.obj
        c.obj
        cap.ppm
        CMakeLists.txt
        cornell.ppm
        lab.exe
        out.ppm
        outVec.ppm
        outVecHQ.ppm
        README.md
        SDL2.dll
        w.ppm include/ppmLoader.h include/generateWorld.h)

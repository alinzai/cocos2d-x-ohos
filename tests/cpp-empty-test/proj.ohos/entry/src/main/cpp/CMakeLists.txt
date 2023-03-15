cmake_minimum_required(VERSION 3.4.1)
project(nativerender)

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../..)

set(CLASSES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../Classes)

set(platform_name "ohos")

find_library( # Sets the name of the path variable.
              EGL-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              EGL )

find_library( # Sets the name of the path variable.
              GLES-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              GLESv3 )

message("***************  GLES-lib: ${GLES-lib} ****************")

find_library( # Sets the name of the path variable.
              hilog-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              hilog_ndk.z )

find_library( # Sets the name of the path variable.
              libace-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              ace_ndk.z )

find_library( # Sets the name of the path variable.
              libnapi-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              ace_napi.z )

find_library( # Sets the name of the path variable.
              libuv-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              uv )
find_library( # Sets the name of the path variable.
              rawfile-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              rawfile.z )

if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
    file(GLOB ALL_RESOURCES_FILES "${CMAKE_CURRENT_LIST_DIR}/../../../../../tests/cpp-empty-tests/Resources/*")
    file(COPY ${ALL_RESOURCES_FILES}
        DESTINATION ${CMAKE_CURRENT_LIST_DIR}/../resources/rawfile)
endif()

include_directories(${COCOS2DX_ROOT_PATH}/external/opengles/api)

add_library(${PROJECT_NAME} SHARED  main.cpp
                                    napi_init.cpp
                                    ${CLASSES_PATH}/AppDelegate.cpp
                                    ${CLASSES_PATH}/HelloWorldScene.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CLASSES_PATH})
target_include_directories(${PROJECT_NAME}  PUBLIC  ${COCOS2DX_ROOT_PATH}
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/editor-support
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/extensions
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos/napi/common
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos/napi/modules
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos/napi
                                            PUBLIC  ${COCOS2DX_ROOT_PATH}/cocos/platform/ohos
                                                    )
#TBD need fixed
target_include_directories(${PROJECT_NAME} PUBLIC ${COCOS2DX_ROOT_PATH}/external/chipmunk/include
    )

add_subdirectory(${COCOS2DX_ROOT_PATH}/tests/cpp-empty-test cpp_empty_test)
message("***************  entry link gles  ****************")
target_link_libraries(${PROJECT_NAME} PUBLIC cocos2d cpp_empty_test ${libnapi-lib} ${GLES-lib})
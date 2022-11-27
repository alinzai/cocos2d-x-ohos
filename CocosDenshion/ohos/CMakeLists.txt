cmake_minimum_required(VERSION 3.4.1)

project(cocosdenshion)

set(COCOSDENSHION_SRC "SimpleAudioEngine.cpp")

set(COCOSDENSHION_HEADER
    ../include
    ../../cocos2dx
    ../../cocos2dx/include
    ../../cocos2dx/kazmath/include
    ../../cocos2dx/platform/ohos
)

add_library(${PROJECT_NAME} STATIC ${COCOSDENSHION_SRC})

include_directories(${COCOSDENSHION_HEADER}
    ../include
    ../../cocos2dx
    ../../cocos2dx/include
    ../../cocos2dx/kazmath/include
    ../../cocos2dx/platform/ohos
)

#set(CMAKE_C_FLAGS -Wno-psabi -Wno-absolute-value -Wno-extra)
#set(CMAKE_CXX_FLAGS -Wno-overloaded-virtual -Wno-unused-function -Wno-unused-private-field -Wno-reorder-ctor -Wno-unsequenced -Wno-extra)
target_compile_definitions(${PROJECT_NAME} PUBLIC -DOpenHarmony=1)
target_compile_options(${PROJECT_NAME} PUBLIC -Wno-psabi -Wno-absolute-value -Wno-extra -Wno-overloaded-virtual -Wno-unused-function -Wno-unused-private-field -Wno-reorder-ctor -Wno-unsequenced -Wno-extra -Wno-unused-command-line-argument -Wno-ignored-qualifiers)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
                                                  ${CMAKE_CURRENT_SOURCE_DIR}/../../cocos2dx
                                                  ${CMAKE_CURRENT_SOURCE_DIR}/../../cocos2dx/include
                                                  ${CMAKE_CURRENT_SOURCE_DIR}/../../cocos2dx/kazmath/include
                                                  ${CMAKE_CURRENT_SOURCE_DIR}/../../cocos2dx/platform/ohos
                                                  ${CMAKE_CURRENT_SOURCE_DIR}/../../external/opengles/api
                                                  )
target_link_libraries(${PROJECT_NAME} PUBLIC cocos2dx_static)
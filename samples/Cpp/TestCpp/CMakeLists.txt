# the minimum version of CMake.
cmake_minimum_required(VERSION 3.4.1)
project(testcpp_common)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include
                    ../../../external
                    ../../../external/lib
                    ../../../external/Box2D
                    ../../../../curl
                    ../../../CocosDenshion/include
                    ../../../external/chipmunk/include/chipmunk
                    Classes
                    Classes/ExtensionsTest
                    ../../../external/tiff_4_0_3
                    ../../../external/tiff_4_0_3/libtiff
                    #../../Cpp/TestCpp
                    )

set(TEST_COMMON_HEADER
    include
    kazmath/include
    platform/ohos
    ../external/opengles/api
    platform/ohos/napi/modules
    Classes/ExtensionsTest
    ../../../external/tiff_4_0_3
    ../../../external/tiff_4_0_3/libtiff
)

set(TEST_COMMON_SRC
    Classes/AccelerometerTest/AccelerometerTest.cpp
    Classes/ActionManagerTest/ActionManagerTest.cpp
    Classes/ActionsTest/ActionsTest.cpp
    Classes/ActionsEaseTest/ActionsEaseTest.cpp
    Classes/ActionsProgressTest/ActionsProgressTest.cpp
    Classes/Box2DTest/Box2dTest.cpp
    Classes/Box2DTestBed/Box2dView.cpp
    Classes/Box2DTestBed/GLES-Render.cpp
    Classes/Box2DTestBed/Test.cpp
    Classes/Box2DTestBed/TestEntries.cpp
    Classes/BugsTest/Bug-1159.cpp
    Classes/BugsTest/Bug-1174.cpp
    Classes/BugsTest/Bug-350.cpp
    Classes/BugsTest/Bug-422.cpp
    Classes/BugsTest/Bug-624.cpp
    Classes/BugsTest/Bug-886.cpp
    Classes/BugsTest/Bug-899.cpp
    Classes/BugsTest/Bug-914.cpp
    Classes/BugsTest/BugsTest.cpp
    Classes/BugsTest/Bug-458/Bug-458.cpp
    Classes/BugsTest/Bug-458/QuestionContainerSprite.cpp
    Classes/ChipmunkTest/ChipmunkTest.cpp
    Classes/ClickAndMoveTest/ClickAndMoveTest.cpp
    Classes/ClippingNodeTest/ClippingNodeTest.cpp
    Classes/CocosDenshionTest/CocosDenshionTest.cpp
    # Classes/CurlTest/CurlTest.cpp
    Classes/CurrentLanguageTest/CurrentLanguageTest.cpp
    Classes/DrawPrimitivesTest/DrawPrimitivesTest.cpp
    Classes/EffectsAdvancedTest/EffectsAdvancedTest.cpp
    Classes/EffectsTest/EffectsTest.cpp
    Classes/ExtensionsTest/ExtensionsTest.cpp
    Classes/ExtensionsTest/NotificationCenterTest/NotificationCenterTest.cpp
    Classes/ExtensionsTest/ControlExtensionTest/CCControlScene.cpp
    Classes/ExtensionsTest/ControlExtensionTest/CCControlSceneManager.cpp
    Classes/ExtensionsTest/ControlExtensionTest/CCControlButtonTest/CCControlButtonTest.cpp
    Classes/ExtensionsTest/ControlExtensionTest/CCControlColourPicker/CCControlColourPickerTest.cpp
    Classes/ExtensionsTest/ControlExtensionTest/CCControlPotentiometerTest/CCControlPotentiometerTest.cpp
    Classes/ExtensionsTest/ControlExtensionTest/CCControlSliderTest/CCControlSliderTest.cpp
    Classes/ExtensionsTest/ControlExtensionTest/CCControlStepperTest/CCControlStepperTest.cpp
    Classes/ExtensionsTest/ControlExtensionTest/CCControlSwitchTest/CCControlSwitchTest.cpp
    Classes/ExtensionsTest/CocosBuilderTest/CocosBuilderTest.cpp
    Classes/ExtensionsTest/CocosBuilderTest/HelloCocosBuilder/HelloCocosBuilderLayer.cpp
    Classes/ExtensionsTest/CocosBuilderTest/TestHeader/TestHeaderLayer.cpp
    Classes/ExtensionsTest/CocosBuilderTest/ButtonTest/ButtonTestLayer.cpp
    Classes/ExtensionsTest/CocosBuilderTest/MenuTest/MenuTestLayer.cpp
    Classes/ExtensionsTest/CocosBuilderTest/AnimationsTest/AnimationsTestLayer.cpp
    Classes/ExtensionsTest/CocosBuilderTest/TimelineCallbackTest/TimelineCallbackTestLayer.cpp
    # Classes/ExtensionsTest/NetworkTest/HttpClientTest.cpp
    # Classes/ExtensionsTest/NetworkTest/WebSocketTest.cpp
    Classes/ExtensionsTest/EditBoxTest/EditBoxTest.cpp
    Classes/ExtensionsTest/TableViewTest/TableViewTestScene.cpp
    Classes/ExtensionsTest/TableViewTest/CustomTableViewCell.cpp
    Classes/ExtensionsTest/CocoStudioArmatureTest/ArmatureScene.cpp
    Classes/ExtensionsTest/CocoStudioActionTimelineTest/ActionTimelineTestScene.cpp
    Classes/ExtensionsTest/CocoStudioComponentsTest/ComponentsTestScene.cpp
    Classes/ExtensionsTest/CocoStudioComponentsTest/EnemyController.cpp
    Classes/ExtensionsTest/CocoStudioComponentsTest/GameOverScene.cpp
    Classes/ExtensionsTest/CocoStudioComponentsTest/PlayerController.cpp
    Classes/ExtensionsTest/CocoStudioComponentsTest/ProjectileController.cpp
    Classes/ExtensionsTest/CocoStudioComponentsTest/SceneController.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/CocoStudioGUITest.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/CocosGUIScene.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/GUIEditorTest.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/CustomGUIScene.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UIScene.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UISceneManager.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UIButtonTest/UIButtonTest.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UICheckBoxTest/UICheckBoxTest.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UIImageViewTest/UIImageViewTest.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UILabelAtlasTest/UILabelAtlasTest.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UILabelBMFontTest/UILabelBMFontTest.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UILabelTest/UILabelTest.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UIListViewTest/UIListViewTest.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UILoadingBarTest/UILoadingBarTest.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UIPageViewTest/UIPageViewTest.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UILayoutTest/UILayoutTest.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UIScrollViewTest/UIScrollViewTest.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UISliderTest/UISliderTest.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UITextFieldTest/UITextFieldTest.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UIWidgetAddNodeTest/UIWidgetAddNodeTest.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UIRichTextTest/UIRichTextTest.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UIScene_Editor.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UISceneManager_Editor.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UIButtonTest/UIButtonTest_Editor.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UICheckBoxTest/UICheckBoxTest_Editor.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UIImageViewTest/UIImageViewTest_Editor.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UILabelAtlasTest/UILabelAtlasTest_Editor.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UILabelBMFontTest/UILabelBMFontTest_Editor.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UILabelTest/UILabelTest_Editor.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UIListViewTest/UIListViewTest_Editor.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UILoadingBarTest/UILoadingBarTest_Editor.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UIPageViewTest/UIPageViewTest_Editor.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UILayoutTest/UILayoutTest_Editor.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UIScrollViewTest/UIScrollViewTest_Editor.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UISliderTest/UISliderTest_Editor.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UITextFieldTest/UITextFieldTest_Editor.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/UIWidgetAddNodeTest/UIWidgetAddNodeTest_Editor.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/CustomWidget/CustomImageView.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/CustomWidget/CustomImageViewReader.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/CustomWidget/CustomReader.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/CustomTest/CustomImageTest/CustomImageTest.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/CustomWidget/CustomParticleWidget.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/CustomWidget/CustomParticleWidgetReader.cpp
    Classes/ExtensionsTest/CocoStudioGUITest/CustomTest/CustomParticleWidgetTest/CustomParticleWidgetTest.cpp
    Classes/ExtensionsTest/CocoStudioSceneTest/SceneEditorTest.cpp
    Classes/ExtensionsTest/CocoStudioSceneTest/TriggerCode/acts.cpp
    Classes/ExtensionsTest/CocoStudioSceneTest/TriggerCode/cons.cpp
    Classes/FontTest/FontTest.cpp
    Classes/IntervalTest/IntervalTest.cpp
    Classes/KeypadTest/KeypadTest.cpp
    Classes/LabelTest/LabelTest.cpp
    Classes/LayerTest/LayerTest.cpp
    Classes/NodeTest/NodeTest.cpp
    Classes/TextInputTest/TextInputTest.cpp
    Classes/MenuTest/MenuTest.cpp
    Classes/MotionStreakTest/MotionStreakTest.cpp
    Classes/MutiTouchTest/MutiTouchTest.cpp
    Classes/ParallaxTest/ParallaxTest.cpp
    Classes/ParticleTest/ParticleTest.cpp
    Classes/PerformanceTest/PerformanceAllocTest.cpp
    Classes/PerformanceTest/PerformanceNodeChildrenTest.cpp
    Classes/PerformanceTest/PerformanceParticleTest.cpp
    Classes/PerformanceTest/PerformanceSpriteTest.cpp
    Classes/PerformanceTest/PerformanceTest.cpp
    Classes/PerformanceTest/PerformanceTextureTest.cpp
    Classes/PerformanceTest/PerformanceTouchesTest.cpp
    Classes/RenderTextureTest/RenderTextureTest.cpp
    Classes/RotateWorldTest/RotateWorldTest.cpp
    Classes/SceneTest/SceneTest.cpp
    Classes/SchedulerTest/SchedulerTest.cpp
    Classes/ShaderTest/ShaderTest.cpp
    Classes/SpineTest/SpineTest.cpp
    Classes/SpriteTest/SpriteTest.cpp
    Classes/TextureCacheTest/TextureCacheTest.cpp
    Classes/Texture2dTest/Texture2dTest.cpp
    Classes/TexturePackerEncryptionTest/TextureAtlasEncryptionTest.cpp
    Classes/TileMapTest/TileMapTest.cpp
    Classes/TouchesTest/Ball.cpp
    Classes/TouchesTest/Paddle.cpp
    Classes/TouchesTest/TouchesTest.cpp
    Classes/TransitionsTest/TransitionsTest.cpp
    Classes/UserDefaultTest/UserDefaultTest.cpp
    Classes/ZwoptexTest/ZwoptexTest.cpp
    Classes/FileUtilsTest/FileUtilsTest.cpp
    Classes/DataVisitorTest/DataVisitorTest.cpp
    Classes/ConfigurationTest/ConfigurationTest.cpp
    Classes/controller.cpp
    Classes/testBasic.cpp
    Classes/AppDelegate.cpp
    Classes/VisibleRect.cpp

)
add_definitions("-DOpenHarmony")
add_definitions("-DCOCOS2D_DEBUG=3")

include_directories(${COCOS2DX_HEADER}
    ../../../cocos2dx
    ../../../CocosDenshion/proj.ohos
    ../../../external/Box2D
    ../../../external/chipmunk
    ../../../extensions/proj.ohos
    ../../../extensions
    ../../Cpp/TestCpp/Classes
    Classes/ExtensionsTest
)

add_compile_options(-DUSE_FILE32API
    -Wno-overloaded-virtual
    -Wno-unused-function
    -Wno-unused-private-field
    -Wno-unused-variable
    -Wno-header-hygiene
    -Wno-reorder-ctor
    -Wno-unsequenced
    -Wno-extra
    -Wno-c++11-narrowing
    -Wno-format
    -Wno-return-stack-address
    -Wno-macro-redefined
    -Wno-implicit-const-int-float-conversion
    -Wno-missing-field-initializers
    -Wno-misleading-indentation
    -Wno-sign-compare
    -Wno-void-pointer-to-int-cast
    -Wno-unused-command-line-argument
    -Wno-unknown-warning-option
    )

add_library(${PROJECT_NAME} SHARED ${TEST_COMMON_SRC})

target_link_directories(${PROJECT_NAME} PUBLIC ../external/lib)
target_link_libraries(${PROJECT_NAME} PUBLIC png_static z turbojpeg_static)

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

# target_link_directories(nativerender PUBLIC ${NATIVERENDER_ROOT_PATH}/lib/arm64-v8a)
target_link_libraries(${PROJECT_NAME} PUBLIC ${EGL-lib} ${GLES-lib} ${hilog-lib}
    ${libace-lib} ${libnapi-lib} ${libuv-lib} libace_napi.z.so libc++.a extensions)

target_link_libraries(${PROJECT_NAME} PUBLIC libace_napi.z.so extensions)
add_subdirectory(../../../extensions extensionsOut.bin)
add_subdirectory(../../../cocos2dx cocosOut.bin)


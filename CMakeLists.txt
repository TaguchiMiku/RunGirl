#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

cmake_minimum_required(VERSION 3.6)

set(APP_NAME TestProject)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(${APP_NAME})
include_directories(${CMAKE_SOURCE_DIR}/Classes/cricket-1.6.7/inc)
link_directories(${CMAKE_SOURCE_DIR}/Classes/cricket-1.6.7/lib/android/ndk/${ANDROID_ABI}/debug)
link_libraries(${CMAKE_SOURCE_DIR}/Classes/cricket-1.6.7/lib/android/ndk/${ANDROID_ABI}/debug/libck.a)
#include(AndroidNdkModules)
#android_ndk_import_module_cpufeatures()

#include_directories(
#        D:/TaguchiMiku/cricket-1.6.7/inc
#)

#link_directories(
#        D:/TaguchiMiku/cricket-1.6.7/lib/android/ndk/${ANDROID_ABI}/debug
#)

#link_libraries(
#        D:/TaguchiMiku/cricket-1.6.7/lib/android/ndk/${ANDROID_ABI}/debug/libck.a
#)

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

include(CocosBuildSet)
add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
if(APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

# add cross-platforms source files and header files 
list(APPEND GAME_SOURCE
     Classes/AppDelegate.cpp
     Classes/GameScene.cpp
        Classes/input/OPRT_State.cpp
        Classes/input/OPRT_Touch.cpp
        Classes/input/OPRT_Enemy.cpp
        Classes/Animation/AnimCtl.cpp
        Classes/obj/Player.cpp
        Classes/obj/Enemy.cpp
        Classes/obj/Unit.cpp
        Classes/obj/DashFx.cpp
        Classes/move/FallMove.cpp
        Classes/move/Falling.cpp
        Classes/move/JumpMove.cpp
        Classes/move/Jumping.cpp
        Classes/move/MoveLR.cpp
        Classes/move/AttackMove.cpp
        Classes/move/EnemyLR.cpp
        Classes/ActionCtl.cpp
        Classes/actModule.cpp
        Classes/CheckCollision.cpp
        Classes/CheckKey.cpp
        Classes/CheckList.cpp
        Classes/effect/EffectMng.cpp
        Classes/effect/Effekseer.cpp
        Classes/effect/EffekseerNative.cpp
        Classes/effect/EffekseerRendererNative.cpp
        Classes/TitleScene.cpp
        Classes/ResultScene.cpp
        Classes/item/HpItem.cpp
        Classes/item/NormalItem.cpp
        Classes/item/FxGlow.cpp
        Classes/CameraCtl.cpp
        Classes/Score.cpp
        Classes/ui/clickUI.cpp
        Classes/ui/TitleNameMove.cpp
        Classes/ui/BackScroll.cpp
        Classes/ui/Attack.cpp
        Classes/ui/TimerMng.cpp
        Classes/ui/CountDown.cpp
        Classes/MapCreate.cpp
        Classes/EnemyCreate.cpp
        Classes/ItemCreate.cpp
        Classes/sound/SoundMng.cpp
        #Classes/sound/SoundMng.cpp
     )
list(APPEND GAME_HEADER
     Classes/AppDelegate.h
     Classes/GameScene.h
        Classes/input/OPRT_State.h
        Classes/input/OPRT_Touch.h
        Classes/input/OPRT_Enemy.h
        Classes/Animation/AnimCtl.h
        Classes/obj/Player.h
        Classes/obj/Enemy.h
        Classes/obj/Unit.h
        Classes/obj/DashFx.h
        Classes/move/FallMove.h
        Classes/move/Falling.h
        Classes/move/JumpMove.h
        Classes/move/Jumping.h
        Classes/move/MoveLR.h
        Classes/move/AttackMove.h
        Classes/move/EnemyLR.h
        Classes/ActionCtl.h
        Classes/actModule.h
        Classes/CheckCollision.h
        Classes/CheckKey.h
        Classes/CheckList.h
        Classes/effect/EffectMng.h
        Classes/effect/Effekseer.h
        Classes/effect/EffekseerNative.h
        Classes/effect/EffekseerRendererNative.h
        Classes/TitleScene.h
        Classes/ResultScene.h
        Classes/item/HpItem.h
        Classes/item/NormalItem.h
        Classes/item/FxGlow.cpp
        Classes/CameraCtl.h
        Classes/Score.h
        Classes/ui/clickUI.h
        Classes/ui/TitleNameMove.h
        Classes/ui/BackScroll.h
        Classes/ui/Attack.h
        Classes/ui/TimerMng.h
        Classes/ui/CountDown.h
        Classes/MapCreate.h
        Classes/EnemyCreate.h
        Classes/ItemCreate.h
        Classes/sound/SoundMng.h
        #Classes/sound/SoundMng.h
     )

if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME MyGame)
    list(APPEND GAME_SOURCE
         proj.android/app/jni/hellocpp/main.cpp
         )
elseif(LINUX)
    list(APPEND GAME_SOURCE
         proj.linux/main.cpp
         )
elseif(WINDOWS)
    list(APPEND GAME_HEADER
         proj.win32/main.h
         proj.win32/resource.h
         )
    list(APPEND GAME_SOURCE
         proj.win32/main.cpp
         proj.win32/game.rc
         ${common_res_files}
         )
elseif(APPLE)
    if(IOS)
        list(APPEND GAME_HEADER
             proj.ios_mac/ios/AppController.h
             proj.ios_mac/ios/RootViewController.h
             )
        set(APP_UI_RES
            proj.ios_mac/ios/LaunchScreen.storyboard
            proj.ios_mac/ios/LaunchScreenBackground.png
            proj.ios_mac/ios/Images.xcassets
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/ios/main.m
             proj.ios_mac/ios/AppController.mm
             proj.ios_mac/ios/RootViewController.mm
             proj.ios_mac/ios/Prefix.pch
             ${APP_UI_RES}
             )
    elseif(MACOSX)
        set(APP_UI_RES
            proj.ios_mac/mac/Icon.icns
            proj.ios_mac/mac/Info.plist
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/mac/main.cpp
             proj.ios_mac/mac/Prefix.pch
             ${APP_UI_RES}
             )
    endif()
    list(APPEND GAME_SOURCE ${common_res_files})
endif()

# mark app complie info and libs info
set(all_code_files
    ${GAME_HEADER}
    ${GAME_SOURCE}
    )
if(NOT ANDROID)
    add_executable(${APP_NAME} ${all_code_files})
else()
    add_library(${APP_NAME} SHARED ${all_code_files})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
endif()

target_link_libraries(${APP_NAME} cocos2d)
target_include_directories(${APP_NAME}
        PRIVATE Classes
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
)

# mark app resources
setup_cocos_app_config(${APP_NAME})
if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")
    if(MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES
                              MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist"
                              )
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
        set_xcode_property(${APP_NAME} DEVELOPMENT_TEAM "")
        set_xcode_property(${APP_NAME} CODE_SIGN_IDENTITY "iPhone Developer")
    endif()
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME})
endif()

if(LINUX OR WINDOWS)
    set(APP_RES_DIR "$<TARGET_FILE_DIR:${APP_NAME}>/Resources")
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif()

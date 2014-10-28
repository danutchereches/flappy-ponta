LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/plugin/publish)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := main.cpp \
					../../Classes/Helpers.cpp \
					../../Classes/Objects.cpp \
					../../Classes/Loader.cpp \
					../../Classes/AtlasLoader.cpp \
					../../Classes/BackgroundLayer.cpp \
					../../Classes/BirdSprite.cpp \
					../../Classes/GameLayer.cpp \
					../../Classes/GameScene.cpp \
					../../Classes/LoadingScene.cpp \
					../../Classes/MenuScene.cpp \
					../../Classes/Number.cpp \
					../../Classes/OptionLayer.cpp \
					../../Classes/StatusLayer.cpp \
					../../Classes/UserRecord.cpp \
					../../Classes/WelcomeLayer.cpp \
					../../Classes/WelcomeScene.cpp \
					../../Classes/AppDelegate.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += PluginProtocolStatic

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)
$(call import-module,protocols/android)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
# $(call import-module,editor-support/cocostudio)
# $(call import-module,network)
# $(call import-module,extensions)

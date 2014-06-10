LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

OPENCV_LIB_TYPE:=STATIC
OPENCV_INSTALL_MODULES:=on

include /home/livingstore/workspace/andriod/OpenCV-2.4.8-android-sdk/sdk/native/jni/OpenCV.mk

LOCAL_MODULE    := ImageProcessing
LOCAL_SRC_FILES := ImageProcessing.cpp
LOCAL_LDLIBS += -llog -ldl

include $(BUILD_SHARED_LIBRARY)
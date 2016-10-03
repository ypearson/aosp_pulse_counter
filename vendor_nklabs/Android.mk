LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES       := receive_counts.c
LOCAL_SHARED_LIBRARIES:= libcutils
LOCAL_MODULE          := receive_counts
include $(BUILD_EXECUTABLE)

# HAL module implemenation, not prelinked and stored in
# hw/<GPS_HARDWARE_MODULE_ID>.<ro.hardware>.so
include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE   := false
LOCAL_MODULE_PATH      := $(TARGET_OUT_SHARED_LIBRARIES)/hw
LOCAL_SHARED_LIBRARIES := liblog libcutils libhardware
LOCAL_SRC_FILES        := librcounts.c
LOCAL_MODULE           := rcnt.qcom
LOCAL_MODULE_TAGS      := debug
LOCAL_MULTILIB         := 64
include $(BUILD_SHARED_LIBRARY)

include $(call all-makefiles-under,$(LOCAL_PATH))


#Makefile
GPP := g++
GCC := gcc
OBJECT := OpenGLExample
LOCAL_PATH := $(shell pwd)
#$(info $(LOCAL_PATH))

LOCAL_C_INCLUDE := $(LOCAL_PATH)/include

CPPFLAGS := -O0 -g3 -Wall -c -fmessage-length=0 -shared

SHARED_LIBRARIES := GL GLU glut

LOCAL_SRC_DIR := src

LOCAL_OUT_DIR := out

LOCAL_OBJ_DIR := obj

LOCAL_BIN_DIR := bin

LOCAL_SRC_FILES :=

LOCAL_CPP_OBJ_FILES :=

LOCAL_CPP_DEP_FILES :=

LOCAL_OUT_FILE  :=

# Find all cpp file
define under-all-cpp-files
	$(patsubst ./%, %, \
		$(shell cd $(LOCAL_PATH); \
			find -L $(1) $(2) $(3) -name "*.cpp" -and -readable))
endef

# Find all c file
define under-all-c-files
	$(patsubst ./%, %, \
		$(shell cd $(LOCAL_PATH); \
			find -L $(1) $(2) $(3) -name "*.c" -and -readable))
endef

#generate executable file
define translate-host-o-to-executable
	@mkdir -p $(dir $@)
	@$(GPP) -o $@ $(LOCAL_CPP_OBJ_FILES) $(LOCAL_C_OBJ_FILES) $(SHARED_LIBRARIES)
	$(info Target Executable Object : $@)
	@ln -sf $@
endef

#generate shared lib file
define translate-host-o-to-shared-lib
	@mkdir -p $(dir $@)
	@$(GPP) -o $@ $(LOCAL_CPP_OBJ_FILES) $(LOCAL_C_OBJ_FILES) $(SHARED_LIBRARIES) -shared -fPIC
	$(info Target Shared Object : $@)
endef

LOCAL_SRC_FILES := $(call under-all-cpp-files, .) $(call under-all-c-files, .)

LOCAL_CPP_OBJ_FILES := $(foreach item, $(filter %.cpp, $(LOCAL_SRC_FILES)), $(patsubst $(LOCAL_SRC_DIR)/%.cpp, $(LOCAL_OUT_DIR)/$(LOCAL_OBJ_DIR)/%.o, $(item)))
LOCAL_C_OBJ_FILES := $(foreach item, $(filter %.c, $(LOCAL_SRC_FILES)), $(patsubst $(LOCAL_SRC_DIR)/%.c, $(LOCAL_OUT_DIR)/$(LOCAL_OBJ_DIR)/%.o, $(item)))

LOCAL_CPP_DEP_FILES := $(foreach item, $(filter %.cpp, $(LOCAL_SRC_FILES)), $(patsubst $(LOCAL_SRC_DIR)/%.cpp, $(LOCAL_OUT_DIR)/$(LOCAL_OBJ_DIR)/%.d, $(item)))
LOCAL_C_DEP_FILES := $(foreach item, $(filter %.c, $(LOCAL_SRC_FILES)), $(patsubst $(LOCAL_SRC_DIR)/%.c, $(LOCAL_OUT_DIR)/$(LOCAL_OBJ_DIR)/%.d, $(item)))

LOCAL_OUT_FILE  := $(LOCAL_OUT_DIR)/$(LOCAL_BIN_DIR)/$(OBJECT)

#$(foreach item, $(LOCAL_C_OBJ_FILES), $(info 67 : $(item)))

	
.PHONY : all

all : $(LOCAL_OUT_FILE)

SHARED_LIBRARIES := $(foreach item, $(SHARED_LIBRARIES), $(addprefix -l, $(item)))

LOCAL_C_INCLUDE := $(foreach item, $(LOCAL_C_INCLUDE), $(addprefix -I, $(item)))

$(LOCAL_OUT_FILE) : $(LOCAL_CPP_OBJ_FILES) $(LOCAL_C_OBJ_FILES) $(SHARED_LIBRARIES)
ifneq ($(strip $(SHARED_LIB)), true)
	$(translate-host-o-to-executable)
else
	$(translate-host-o-to-shared-lib)
endif
#	./$(OBJECT)

$(LOCAL_CPP_OBJ_FILES) : $(LOCAL_OUT_DIR)/$(LOCAL_OBJ_DIR)/%.o : $(LOCAL_SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(GPP) $(LOCAL_C_INCLUDE) $(CPPFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o $@ $<
	$(info $(OBJECT) <===== $<)

$(LOCAL_C_OBJ_FILES) : $(LOCAL_OUT_DIR)/$(LOCAL_OBJ_DIR)/%.o : $(LOCAL_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(GCC) $(LOCAL_C_INCLUDE) $(CPPFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o $@ $<
	$(info $(OBJECT) <===== $<)

ifneq ($(strip $(LOCAL_CPP_DEP_FILES)),)
-include $(LOCAL_CPP_DEP_FILES)
endif

ifneq ($(strip $(LOCAL_C_DEP_FILES)),)
-include $(LOCAL_C_DEP_FILES)
endif

.PHONY : clean 
clean : 
	@-rm -rvf out/ $(OBJECT)
	@echo "Clean over"

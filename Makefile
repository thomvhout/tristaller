#
# Cross Platform Makefile
# Compatible with MSYS2/MINGW, Ubuntu 14.04.1 and Mac OS X
#
# You will need GLFW (http://www.glfw.org):
# Linux:
#   apt-get install libglfw-dev
# Mac OS X:
#   brew install glfw
# MSYS2:
#   pacman -S --noconfirm --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-glfw
#

# Based on imgui/examples/example_glfw_opengl3/Makefile

.PHONY: all clean debug
.DEFAULT_GOAL := all

EXE = tristaller
IMGUI_DIR = lib/imgui
SOURCE_DIR = src
SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_vulkan.cpp
BUILD_DIR = build
OBJS = $(addprefix $(BUILD_DIR)/,$(addsuffix .o, $(basename $(notdir $(SOURCES)))))
UNAME_S := $(shell uname -s)
LINUX_GL_LIBS = -lGL

VULKAN_SDK_PATH=/home/$(LOGNAME)/hdd/project/vulkan/sdk/1.3.224.0/x86_64
LIBZIP_BUILD_PATH=./lib/libzip/build/lib/

CXXFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
CXXFLAGS += -g -Wall -Wformat
CXXFLAGS += -std=c++17 -I$(VULKAN_SDK_PATH)/include
LDFLAGS = -L$(VULKAN_SDK_PATH)/lib -lvulkan
LIBS = $(LIBZIP_BUILD_PATH)/libzip.so

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

# TODO Use local GLFW instead of system
# TODO Obtain local vulkan-sdk
ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	LIBS += $(LINUX_GL_LIBS) `pkg-config --static --libs glfw3`

	CXXFLAGS += `pkg-config --cflags glfw3`
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	ECHO_MESSAGE = "Mac OS X"
	LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
	LIBS += -L/usr/local/lib -L/opt/local/lib -L/opt/homebrew/lib
	#LIBS += -lglfw3
	LIBS += -lglfw

	CXXFLAGS += -I/usr/local/include -I/opt/local/include -I/opt/homebrew/include
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(OS), Windows_NT)
	ECHO_MESSAGE = "MinGW"
	# TODO replace opengl with vulkan
	LIBS += -lglfw3 -lgdi32 -lopengl32 -limm32

	CXXFLAGS += `pkg-config --cflags glfw3`
	CFLAGS = $(CXXFLAGS)
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

#%.o:%.cpp
$(BUILD_DIR)/%.o:$(SOURCE_DIR)/%.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

$(BUILD_DIR)/%.o:$(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o:$(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# TODO Don't build libzip examples
$(LIBZIP_BUILD_PATH)/libzip.so: $(LIBZIP_BUILD_PATH)/../../src/ziptool.c 
	cd lib/libzip/ && \
	mkdir -p build && cd build && \
	cmake ../ && \
	make

# vulkan_sdk
# 	cd $(VULKAN_SDK_PATH) && ./vulkan_sdk

all: $(EXE) $(BUILD_DIR)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS) $(LIBZIP_BUILD_PATH)/libzip.so
	$(CXX) -o $(BUILD_DIR)/$@ $^ $(CXXFLAGS) $(LIBS) $(LDFLAGS) 

debug: $(OBJS) $(LIBZIP_BUILD_PATH)/libzip.so
	$(CXX) -o $(BUILD_DIR)/$(EXE) $^ $(CXXFLAGS) $(LIBS) $(LDFLAGS) -g

clean:
	rm -rf $(EXE) $(BUILD_DIR) 

clean-all:
	rm -f imgui.ini
	cd $(LIBZIP_BUILD_PATH)/.. && make clean

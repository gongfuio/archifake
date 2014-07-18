# Includes
INCLUDES := $(realpath src/)
# INCLUDES += /usr/include/freetype2

# Sources
SOURCES := $(realpath $(shell find src/ -type f -iname "*.c"))
SOURCES += $(realpath $(shell find src/ -type f -iname "*.cpp"))

# Objects
OBJECTS := $(addsuffix .o, $(basename $(SOURCES)))

# Compilation flags
RELEASEFLAGS := -g -O0
#RELEASEFLAGS := -O3
CPPFLAGS += -pipe $(foreach dir, $(INCLUDES), -I$(dir))
CFLAGS += -std=gnu99 -Wall -mmmx -msse -msse2 -msse3 $(RELEASEFLAGS)
CXXFLAGS += -std=gnu++11 -Wall -mmmx -msse -msse2 -msse3 $(RELEASEFLAGS)
LDFLAGS += -pipe #-L/usr/lib/mesa
LIBRARIES := -lstdc++ -lm -lGL -lfontconfig -lXft -lX11 -ljpeg -lpng -lpthread -lrt -lm -lstdc++ -lGL -lGLU -lGLEW

# System detection
BASE_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))/


all: archifake

clean:
	@rm -f archifake
	@rm -f $(OBJECTS)


archifake: $(OBJECTS)
	@echo "linking $(subst $(BASE_DIR),,$@)..."
	@$(LINK.o) -o $@ $^ $(LIBRARIES)


%.o: %.c
	@echo "compiling $(subst $(BASE_DIR),,$<)..."
	@$(COMPILE.c) -o $@ $<

%.o: %.cpp
	@echo "compiling $(subst $(BASE_DIR),,$<)..."
	@$(COMPILE.cpp) -o $@ $<


.PHONY: all clean

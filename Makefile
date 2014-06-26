# Includes
INCLUDES := $(realpath include/)
INCLUDES += /usr/include/freetype2

# Sources
SOURCES := $(realpath $(wildcard src/*.c src/*.cpp))

# Objects
OBJECTS := $(addsuffix .o, $(basename $(SOURCES)))

# Compilation flags
RELEASEFLAGS := -g -O0
#RELEASEFLAGS := -O3
CPPFLAGS += -c -pipe $(foreach dir, $(INCLUDES), -I$(dir))
CFLAGS += -std=gnu99 -Wall -funsigned-char -mmmx -msse -msse2 -msse3
CXXFLAGS += -std=gnu++11 -Wall -funsigned-char -mmmx -msse -msse2 -msse3
LDFLAGS += -pipe -L/usr/lib/mesa -lstdc++ -lm -lGL -lfontconfig -lXft -lX11 -ljpeg -lpng -lpthread -lrt -lm -lstdc++ -lGL -lGLU -lGLEW

# System detection
BASE_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))/


all: archifake

clean:
	@rm -f archifake
	@rm -f $(OBJECTS)


archifake: $(OBJECTS)
	@echo "linking $(subst $(BASE_DIR),,$@)..."
	@$(LINK.o) $(RELEASEFLAGS) -o $@ $^


%.o: %.c
	@echo "compiling $(subst $(BASE_DIR),,$<)..."
	@$(COMPILE.c) $(RELEASEFLAGS) -o $@ $<

%.o: %.cpp
	@echo "compiling $(subst $(BASE_DIR),,$<)..."
	@$(COMPILE.cpp) $(RELEASEFLAGS) -o $@ $<


.PHONY:	all clean

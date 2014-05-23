CXX ?= g++-4.8
MKDIR := mkdir -p
CXXFLAGS += `pkg-config --cflags sdl2 SDL2_image`
CXXFLAGS += -Wall -Werror -Wextra -Weffc++ -pedantic -std=c++0x
LDFLAGS += `pkg-config --libs sdl2 SDL2_image`
PROG := bin/cave
OBJS := $(patsubst src/%.cpp,obj/%.o, $(wildcard src/*.cpp))
DEPS := $(OBJS:.o=.d)

.PHONY: all clean

all: build

build: $(PROG)

-include $(DEPS)

clean:
	rm -rf $(PROG) $(OBJS)

$(PROG): $(OBJS)
	@$(MKDIR) $(dir $@)
	$(CXX) $^ $(CXXFLAGS) $(LDFLAGS) -o $@

obj/%.o : src/%.cpp
	@$(MKDIR) $(dir $@)
	$(CXX) $< $(CXXFLAGS) -c -MD -o $@


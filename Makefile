CXX ?= g++-4.8
MKDIR := mkdir -p
CXXFLAGS += `pkg-config --cflags sdl2 SDL2_image`
CXXFLAGS += -Wall -Werror -Wextra -Weffc++ -pedantic -std=c++0x
LDFLAGS += `pkg-config --libs sdl2 SDL2_image`
PROGS := bin/cave
OBJS := $(patsubst src/%.cpp,obj/%.o, $(wildcard src/*.cpp))

.PHONY: all clean

all: build

build: $(PROGS)

clean:
	rm -rf $(PROGS) $(OBJS)

bin/cave: obj/animated_sprite.o \
	obj/backdrop.o \
	obj/damage_text.o \
	obj/first_cave_bat.o \
	obj/game.o \
	obj/graphics.o \
	obj/input.o \
	obj/main.o \
	obj/map.o \
	obj/number_sprite.o \
	obj/player.o \
	obj/player_health.o \
	obj/player_walking_animation.o \
	obj/polar_star.o \
	obj/sprite.o \
	obj/timer.o \
	obj/varying_width_sprite.o

$(PROGS):
	@$(MKDIR) $(dir $@)
	$(CXX) $^ $(CXXFLAGS) $(LDFLAGS) -o $@

obj/%.o : src/%.cpp
	@$(MKDIR) $(dir $@)
	$(CXX) $< $(CXXFLAGS) -c -MD -o $@


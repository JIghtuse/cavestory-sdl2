CXX := g++
MKDIR := mkdir -p
CXXFLAGS := -Wall -Werror -Wextra -pedantic
LDFLAGS := 
PROGS := bin/cave
OBJS := $(patsubst src/%.c,obj/%.o, $(wildcard src/*.c))

.PHONY: all clean

all: build

build: $(PROGS)

clean:
	rm -rf $(PROGS) $(OBJS)

bin/cave: obj/game.o obj/main.o

$(PROGS):
	@$(MKDIR) $(dir $@)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

obj/%.o : src/%.cpp
	@$(MKDIR) $(dir $@)
	$(CXX) $(CXXFLAGS) -c -MD -o $@ $<


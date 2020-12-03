CXX = g++
DEPS = ./*.hpp

CXXFLAGS = -std=c++17 -fopenmp

target  := ./pathtracer
obj_dir := ../build/obj/
sources := $(shell find ./ -name \*.cpp)
objects := $(addprefix $(obj_dir), $(notdir $(sources:.cpp=.o)))
dirs    := $(dir $(sources))
VPATH   := $(dirs)

all: CXXFLAGS += -O3
all: pathtracer

.PHONY: debug
debug: CXXFLAGS += -g
debug: pathtracer

.PHONY: sanitize
sanitize: CXXFLAGS += -g -fsanitize=address
sanitize: pathtracer

pathtracer: $(objects)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean: 
	rm -f $(obj_dir)*.o ./pathtracer

$(objects): $(obj_dir)%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<


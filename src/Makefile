CXX = g++
DEPS = ./*.hpp

CXXFLAGS = -std=c++17 -fopenmp

target  := ./pathtracer
obj_dir := ../build/obj/
sources := $(shell find ./ -name \*.cpp)
objects := $(addprefix $(obj_dir), $(notdir $(sources:.cpp=.o)))
dirs    := $(dir $(sources))
VPATH   := $(dirs)

# Compile optimized version
pathtracer: $(objects)
	$(CXX) $(CXXFLAGS) -O3 -o $@ $^

# Compile debug version
debug: $(objects)
	$(CXX) $(CXXFLAGS) -g -o $@ $^

# Compile debug version with AddressSanitizer
sanitize: $(objects)
	$(CXX) $(CXXFLAGS) -g -fsanitize=address -o $@ $^

# Delete executable and object files
.PHONY: clean
clean: 
	rm -f $(obj_dir)*.o pathtracer

# Rule to compile object files
$(objects): $(obj_dir)%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<


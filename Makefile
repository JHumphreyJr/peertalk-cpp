#Directories
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj
HDR_DIR = include

#Compiler settings
CXXFLAGS = -Wall -g
LIBINC = -Lbin
HDRINC = -I$(HDR_DIR)

#Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
#Example source files
SRCS_EX = $(wildcard $(SRC_DIR)/example/*.cpp)

#Object files
OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))
OBJS_EX = $(patsubst %.cpp,$(OBJ_DIR)/example/%.o,$(notdir $(SRCS_EX)))

#Public header files
HDR_PUB = src/peertalk.h src/Peertalk.hpp src/Protocol.hpp src/Channel.hpp

.PHONY: all
all: peertalk

.PHONY: example
example: peertalk $(OBJS_EX)
	$(CXX) $(CXXFLAGS) -o bin/$@ $(OBJS_EX) $(LIBINC) -lpeertalk -lusbmuxd

.PHONY: peertalk
peertalk: $(OBJS)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(HDR_DIR)
#create static library
	ar rcs $(BIN_DIR)/libpeertalk.a $(OBJS)
#create shared library
	$(CXX) -shared -Wl,-soname,lib$@.so.0.1 -o $(BIN_DIR)/lib$@.so.0.1 $(OBJS)
	ln -sf $(BIN_DIR)/lib$@.so.0.1 $(BIN_DIR)/lib$@.so
#copy headers
	cp $(HDR_PUB) $(HDR_DIR)

$(OBJ_DIR)/example/%.o: $(SRC_DIR)/example/%.cpp
	mkdir -p $(OBJ_DIR)/example
	$(CXX) $(CXXFLAGS) $(HDRINC) -o $@ -c $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -fPIC -o $@  -c $<

.PHONY: clean
clean:
	rm -r $(OBJ_DIR) 2> /dev/null || true
	rm -r $(HDR_DIR) 2> /dev/null || true
	rm -r $(BIN_DIR) 2> /dev/null || true
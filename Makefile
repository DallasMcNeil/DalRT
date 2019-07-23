SRC_DIR := src
OBJ_DIR := build
INCLUDE_DIR := include
HEADER_FILES := $(wildcard $(INCLUDE_DIR)/*.hpp)
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

EXAMPLE_DIR := examples
EXAMPLE_BUILD_DIR := examples/build
EXAMPLE_SRC_FILES := $(wildcard $(EXAMPLE_DIR)/*.cpp)
EXAMPLE_OBJ_FILES := $(patsubst $(EXAMPLE_DIR)/%.cpp,$(EXAMPLE_BUILD_DIR)/%,$(EXAMPLE_SRC_FILES))
ARFLAGS := -rs $(OBJ_DIR)/libDalRT.a
CPPFLAGS := -std=c++17 -I include -I lib
EXAMPLE_FLAGS := -Lbuild -lDalRT


all: build examples

examples: $(EXAMPLE_OBJ_FILES)

build: $(OBJ_FILES)
	ar $(ARFLAGS) $^

$(EXAMPLE_BUILD_DIR)/%: $(EXAMPLE_DIR)/%.cpp build
	g++ $(CPPFLAGS) $(EXAMPLE_FLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADER_FILES)
	g++ $(CPPFLAGS) -g -c -o $@ $<

clean:
	rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/libDalRT.a & rm -f $(EXAMPLE_BUILD_DIR)/*
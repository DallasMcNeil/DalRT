SRC_DIR := src
OBJ_DIR := build
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
ARFLAGS := -rsv $(OBJ_DIR)/DalRT.a
CPPFLAGS := -std=c++17 -g -I include -I lib
CXXFLAGS :=

link: $(OBJ_FILES)
	ar $(ARFLAGS) $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f build/*.o DalRT.a
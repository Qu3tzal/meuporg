SRC_DIR := meuporg-server/source/
SRC_FILES := $(wildcard $(SRC_DIR)/**/*.cpp)
OBJ_FILES := $(SRC_FILES:.cpp=.o)
CXXFLAGS := -std=c++11 -Wall
LDFLAGS := -lsfml-system-d -lsfml-graphics-d -lsfml-window-d -lsfml-audio-d -lsfml-network-d

all: $(OBJ_FILES)
	$(CXX) $(CXX_FLAGS) $(LDFLAGS) $^ -o meuporg-server/meuporg-server.debug
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
   $(CXX) $(CXXFLAGS) $(LDFLAGS) -c -o $@ $<
   
clean:
	rm meuporg-server/meuporg-server
	rm meuporg-server/*.obj

test:
	echo "Tests:"

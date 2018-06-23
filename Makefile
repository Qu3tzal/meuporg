SRC_DIR := meuporg-server/source/
SRC_FILES := $(wildcard $(SRC_DIR)/**/*.cpp)
OBJ_FILES := $(SRC_FILES:.cpp=.o)

all: $(OBJ_FILES)
	$(CXX) $^ -std=c++11 -Wall -o meuporg-server/meuporg-server.debug
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
   $(CXX) -lsfml-system-d -lsfml-graphics-d -lsfml-window-d -lsfml-audio-d -lsfml-network-d -std=c++11 -Wall -c -o $@ $<
   
clean:
	rm meuporg-server/meuporg-server
	rm meuporg-server/*.obj

test:
	echo "Tests:"

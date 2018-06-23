SRC_DIR := meuporg-server/source/
OBJ_DIR := meuporg-server/
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: $(OBJ_FILES)
	$(CXX) -std=c++14 -Wall -o meuporg-server
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
   $(CXX) -std=c++14 -Wall -c -o $@ $<
   
clean:
	rm meuporg-server/meuporg-server
	rm meuporg-server/*.obj

test:
	echo "Tests:"

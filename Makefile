APP_NAME = lfgOpenGL
BUILD_DIR = ./bin

APP_DEFINES :=
APP_INCLUDES := -I./include -framework Cocoa -framework OpenGL -framework IOKit
APP_LINKERS := -L./lib -lglfw3

build:
	g++ -o $(BUILD_DIR)/$(APP_NAME) *.cpp -Wall $(APP_INCLUDES) $(APP_LINKERS) -std=c++17

run:
	$(BUILD_DIR)/$(APP_NAME)

brun:
	make build
	make run
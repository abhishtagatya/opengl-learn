APP_NAME = lfgOpenGL
BUILD_DIR = ./bin

APP_DEFINES :=
APP_INCLUDES := -I./include -framework Cocoa -framework OpenGL -framework IOKit
APP_LINKERS := -L./lib -lglfw3

build:
	g++ -o $(BUILD_DIR)/$(APP_NAME) *.cpp $(APP_INCLUDES) $(APP_LINKERS) -std=c++17
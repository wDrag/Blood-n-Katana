#OBJS specifies which files to compile as part of the project
OBJS = main.cpp src/Core/engine.cpp src/Graphics/TextureManager.cpp 
OBJS += src/Animation/AnimationHandler.cpp src/Inputs/Input.cpp src/Timer/Timer.cpp
OBJS += src/Map/TileLayer.cpp src/TinyXML/tinystr.cpp src/TinyXML/tinyxml.cpp 
OBJS += src/TinyXML/tinyxmlparser.cpp src/TinyXML/tinyxmlerror.cpp
OBJS += src/Map/MapParser.cpp src/Camera/Camera.cpp src/Collision/CollisionHandler.cpp
OBJS += 
#Characters lib
CHARACTERS = src/Characters/Samurai.cpp
#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I src/include -I src

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L src/lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -std=c++17 -static-libgcc -static-libstdc++

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = BND

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(CHARACTERS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)	
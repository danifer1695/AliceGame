# Name of the output executable
TARGET = Assignment4.exe

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -static -static-libgcc -static-libstdc++

# All your source files
SRC = Assignment4.cpp \
      source/Events.cpp source/Door.cpp source/Action.cpp source/Buffer.cpp \
      source/Game.cpp source/Player.cpp source/Room.cpp source/Character.cpp \
      source/CharacterDatabase.cpp source/Screen.cpp source/Item.cpp \
      source/ItemDatabase.cpp utilities/Input_Parser.cpp utilities/Logger.cpp \
      utilities/Input_Manager.cpp utilities/Utilities.cpp source/Map.cpp

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Clean rule
clean:
	del /Q $(TARGET)
# Compilateur et options
CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -std=c++17

# Répertoires
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
BIBLIO_DIR = Biblio

# Fichiers sources et objets
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Nom de l'exécutable
TARGET = $(BIN_DIR)/mon_programme

# Règle par défaut
all: $(TARGET)

# Construction de l'exécutable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ -L$(BIBLIO_DIR)

# Compilation des fichiers objets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Nettoyage des fichiers générés
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Phonies
.PHONY: all clean

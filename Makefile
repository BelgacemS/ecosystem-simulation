# Compilateur et options
CC := gcc
CFLAGS := -g -Wall -Wextra -pedantic
INCLUDES := -Iinclude

# Répertoires
SRC_DIR := src
INC_DIR := include
TEST_DIR := tests
BUILD_DIR := build
BIN_DIR := bin
DATA_DIR := data

# Fichiers source
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
TEST_FILES := $(wildcard $(TEST_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))
TEST_OBJ := $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%.o,$(TEST_FILES))

# Exécutables
MAIN_EXEC := $(BIN_DIR)/ecosys
TEST_EXEC := $(BIN_DIR)/tests_ecosys

# Règle par défaut
all: directories $(MAIN_EXEC) $(TEST_EXEC)

# Création des répertoires nécessaires
directories:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

# Programme principal
$(MAIN_EXEC): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

# Programme de test
$(TEST_EXEC): $(filter-out $(BUILD_DIR)/main_ecosys.o, $(OBJ_FILES)) $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Compilation des fichiers source
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation des fichiers de test
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Nettoyer les fichiers générés
clean:
	rm -rf $(BUILD_DIR)/* $(BIN_DIR)/* $(DATA_DIR)/population_stats.txt $(DATA_DIR)/evolution_populations.png

# Nettoyer tous les fichiers générés
distclean: clean

# Lancer les tests
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Lancer le programme principal avec visualisation
run: $(MAIN_EXEC)
	./$(BIN_DIR)/ecosys
	python3 $(DATA_DIR)/plot_populations.py

# Lancer le programme principal sans visualisation
run-sim: $(MAIN_EXEC)
	./$(BIN_DIR)/ecosys

.PHONY: all directories clean test run run-sim

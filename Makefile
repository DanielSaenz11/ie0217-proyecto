# Compilador y banderas para la compilación
CXX = g++
CXXFLAGS = -std=c++20 -Wall

# Directorios de SQLite
SQLITE_INCLUDE = -I<path_to_sqlite_include>
SQLITE_LIB = -L<path_to_sqlite_lib>

# Directorios de los archivos fuente, de cabecera y de compilación
SRC_DIR = src
INCLUDE_DIR = include
UTILS_DIR = utils
BUILD_DIR = build

# Archivos fuente y archivos objeto
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) utils/auxiliares.cpp
OBJ_FILES = $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_FILES:.cpp=.o)))

# Verificar el sistema operativo
ifeq ($(OS), Windows_NT)
    RM = del /Q
    MKDIR = if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    EXT = .exe
else
    RM = rm -rf
    MKDIR = mkdir -p $(BUILD_DIR)
    EXT =
endif

# Ejecutables
EXEC_MAIN = $(BUILD_DIR)/sistemaGestionBancaria
EXEC_DB_INIT = $(BUILD_DIR)/inicio_db

# Reglas para construir los ejecutables
all: $(BUILD_DIR) $(EXEC_MAIN)$(EXT) $(EXEC_DB_INIT)$(EXT)

# Crear el directorio build
$(BUILD_DIR):
	$(MKDIR)

$(EXEC_MAIN)$(EXT): $(BUILD_DIR)/main.o $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $(SQLITE_INCLUDE) $(SQLITE_LIB) -o $@ $(OBJ_FILES) -lsqlite3

$(EXEC_DB_INIT)$(EXT): $(BUILD_DIR)/inicio_db.o $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(SQLITE_INCLUDE) $(SQLITE_LIB) -o $@ -lsqlite3 utils/inicio_db.cpp

# Compilación de los archivos objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $(SQLITE_INCLUDE) -c $< -o $@

$(BUILD_DIR)/%.o: $(UTILS_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $(SQLITE_INCLUDE) -c $< -o $@

# Limpiar archivos generados
clean:
	$(RM) $(BUILD_DIR)/*$(EXT) $(OBJ_FILES)

# Regla para ejecutar el programa completo
run: all
	./$(EXEC_DB_INIT) && ./$(EXEC_MAIN)

# PHONY targets
.PHONY: all clean

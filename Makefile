# Compilador y banderas para la compilación
CXX = g++
CXXFLAGS = -std=c++20 -Wall
SQLITE_INCLUDE = -I<path_include_directory_sqlite> 
SQLITE_LIB = -L<path_library_directory_sqlite> 

# Archivos fuente y archivos objeto
SRC_FILES = $(wildcard src/*.cpp) utils/auxiliares.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)
BUILD_DIR = build

# Ejecutables
EXEC_MAIN = $(BUILD_DIR)/sistemaGestionBancaria
EXEC_DB_INIT = $(BUILD_DIR)/iniciar_db

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

# Reglas para construir los ejecutables
all: $(EXEC_MAIN)$(EXT) $(EXEC_DB_INIT)$(EXT)

$(EXEC_MAIN)$(EXT): src/main.cpp $(OBJ_FILES)
	$(MKDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ src/main.cpp $(OBJ_FILES)

$(EXEC_DB_INIT)$(EXT): utils/inicio_db.cpp $(OBJ_FILES)
	$(MKDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ utils/inicio_db.cpp $(OBJ_FILES)

# Compilación de los archivos objeto
$(OBJ_FILES): %.o : %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -c $< -o $@

# Limpiar archivos generados
clean:
	$(RM) $(BUILD_DIR)/*$(EXT) $(OBJ_FILES)

# PHONY targets	
.PHONY: all clean
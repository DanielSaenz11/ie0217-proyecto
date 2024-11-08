# Compilador y banderas para la compilación
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Iinclide

# Directorios
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
UTILS_DIR = utils

# Archivos fuente y ejecutables
MAIN_SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/CDP.cpp $(SRC_DIR)/Cliente.cpp $(SRC_DIR)/Cuenta.cpp \
           $(SRC_DIR)/Database.cpp $(SRC_DIR)/Transaccion.cpp $(SRC_DIR)/verificarExistencia.cpp \
           $(UTILS_DIR)/auxiliares.cpp
INIT_DB_SRC = $(UTILS_DIR)/inicio_db.cpp $(UTILS_DIR)/auxiliares.cpp
MAIN_EXEC = $(BUILD_DIR)/sistemaGestionBancaria
INIT_DB_EXEC = $(BUILD_DIR)/iniciar_db

# Comandos
all: $(MAIN_EXEC) $(INIT_DB_EXEC)

# Instrucciones para la compilación del ejecutable principal
$(MAIN_EXEC): $(MAIN_SRC)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Instrucciones para la compilación del ejecutable para la inicialización de la base de datos
$(INIT_DB_EXEC): $(INIT_DB_SRC)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para limpiar los archivos utilizados en la compilación
clean:
	rm -rf $(BUILD_DIR)

# PHONY targets
.PHONY: all clean
# Nome do executável
TARGET = stock_simulation

# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Arquivos de cabeçalho e código fonte
HEADERS = include/stock.hpp include/user.hpp include/market.hpp include/transaction.hpp include/simulation.hpp
SOURCES = src/main.cpp src/stock.cpp src/user.cpp src/market.cpp src/transaction.cpp src/simulation.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Regra padrão
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para compilar os arquivos .cpp em .o
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza dos arquivos compilados
clean:
	rm -f $(OBJECTS) $(TARGET)

# Limpeza completa, incluindo backups
distclean: clean
	rm -f *~ *.bak

# Regra para executar o programa
run: $(TARGET)
	./$(TARGET)

# Regra para debug
debug: CXXFLAGS += -g
debug: clean $(TARGET)

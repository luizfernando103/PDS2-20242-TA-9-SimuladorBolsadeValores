# Nome do executável
TARGET = stock_simulation

# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Arquivos de cabeçalho e código fonte
HEADERS = stock.hpp user.hpp market.hpp transaction.hpp simulation.hpp
SOURCES = main.cpp stock.cpp user.cpp market.cpp transaction.cpp simulation.cpp
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

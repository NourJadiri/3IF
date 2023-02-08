# makefile plus ou moins générique
# outils
ECHO = @echo
RM = @rm

CXX = g++
LD = g++

# options
CXXFLAGS = -g -Wall -ansi -pedantic -std=c++14
LDFLAGS = -g -Wall -pedantic -std=c++14
RMFLAGS = -rf

# repertoires
BIN_DIR = ./../bin/

# definition des cibles
INTERFACE := $(wildcard *.h)
REALISATION := $(INTERFACE:.h=.cpp)
OBJETS = $(REALISATION:.cpp=.o)
EXE = analog
BIN = $(BIN_DIR)$(EXE)
EFFACE = clean
.PHONY : $(EFFACE)

# edition des liens
$(BIN) : $(OBJETS)
	$(ECHO) ">>>Edition des liens de <$(EXE)>"
	$(LD) $(LDFLAGS) $^ -o $@

# compilation des fichiers
%.o: %.cpp
	@$(ECHO) ">>>Compilation de" $<
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(EFFACE) :
	@$(ECHO) ">>>Suppression des fichiers compilés" $<
	$(RM) $(RMFLAGS) $(BIN) $(OBJETS)

# dependances complementaires
Analog.o : Graph.h
Graph.o : Log_Utils.h Node.h
Log.o : Log_Utils.h
LogFile_Manager.o : Log.h
Main.o : Analog.h
Node.o : Connections.h
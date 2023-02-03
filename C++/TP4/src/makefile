# makefile plus ou moins générique
# outils
ECHO = @echo
RM = @rm

CXX = g++
LD = g++

# options
CXXFLAGS = -g -DMAP -Wall -ansi -pedantic -std=c++11
LDFLAGS = -g -Wall -pedantic -std=c++11
RMFLAGS = rm -f

# definition des cibles
INTERFACE := Main.h LogFile_Manager.h Log_Utils.h Log.h Analog.h
REALISATION := $(INTERFACE:.h=.cpp)
OBJETS = $(REALISATION:.cpp=.o)
EXE = analog
EFFACE = clean
.PHONY : $(EFFACE)

# edition des liens
$(EXE) : $(OBJETS)
	$(ECHO) ">>>Edition des liens de <$(EXE)>"
	$(LD) $(LDFLAGS) -o $(EXE) $(OBJETS)

# compilation des fichiers
%.o: %.cpp
	@$(ECHO) ">>>Compilation de" $<
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(EFFACE) :
	@$(ECHO) ">>>Suppression des fichiers compilés" $<
	$(RM) $(RMFLAGS) $(EXE) $(OBJETS)
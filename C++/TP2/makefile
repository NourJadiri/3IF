# makefile plus ou moins générique
ECHO = @echo
RM = @rm
RMFLAGS = rm -f

CXX = g++
LD = g++
CXXFLAGS = -g -DMAP -Wall -ansi -pedantic -std=c++11
LDFLAGS = -g -Wall -pedantic -std=c++11

INTERFACE = Main.h Catalogue.h ComposedTrip.h List.h Node.h SimpleTrip.h Trip.h
REALISATION = $(INTERFACE:.h=.cpp)
OBJETS = $(INTERFACE:.h=.o)
EXE = trajets
EFFACE = clean

# edition des liens
$(EXE) : $(OBJETS)
	$(ECHO) ">>>Edition des liens de <$(EXE)>"
	$(LD) $(LDFLAGS) -o $(EXE) $(OBJETS)

# compilation des fichiers
%.o: %.cpp
	@$(ECHO) ">>>Compilation de" $<
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(EFFACE) :
	$(RM) $(RMFLAGS) $(EXE) $(OBJETS)
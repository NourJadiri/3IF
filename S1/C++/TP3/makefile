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
INTERFACE := Main.h Catalogue.h ComposedTrip.h List.h Node.h SimpleTrip.h Trip.h CatalogueUtils.h
REALISATION := $(INTERFACE:.h=.cpp)
REALISATION := $(REALISATION) Catalogue_InputManager.cpp Catalogue_OutputManager.cpp
OBJETS = $(REALISATION:.cpp=.o)
EXE = trajets
FICHIERSTXT = $(wildcard *.csv)
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

# commentaire ci-dessous a enlever si vous souhaitez egalement supprimer les fichiers .csv avec la commande make clean
$(EFFACE) :
	$(RM) $(RMFLAGS) $(EXE) $(OBJETS) 
	#$(RM) $(RMFLAGS) $(FICHIERSTXT)

# dependance des fichiers
Main.o : Main.h Catalogue.h
Catalogue.o : Catalogue.h SimpleTrip.h ComposedTrip.h CatalogueUtils.h List.h
Catalogue_InputManager.o : Catalogue.h ComposedTrip.h SimpleTrip.h CatalogueUtils.h
Catalogue_OutputManager.o : List.h Catalogue.h CatalogueUtils.h
CatalogueUtils.o : CatalogueUtils.h Catalogue.h
ComposedTrip.o : ComposedTrip.h List.h Trip.h
List.o : List.h Node.h
Node.o : Node.h Trip.h SimpleTrip.h
SimpleTrip.o : SimpleTrip.h Trip.h
Trip.o : Trip.h
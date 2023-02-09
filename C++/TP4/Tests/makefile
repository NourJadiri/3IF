# makefile du Framework de Tests
# outils
MAKE = @make
BASH = @bash
RM = @rm

# cibles
BIN = analog
TEST = test
CLEAN = clean
.PHONY: $(CLEAN) $(TEST) $(BIN)

# mise a jour de l'executable analog
$(BIN):
	$(MAKE) -s -C ../src ./../bin/analog

# lancement du framework de tests
$(TEST):
	$(BASH) ./mktest.sh

# suppression de l'executable, des -o et des resultats des tests
$(CLEAN):
	$(MAKE) -s -C ../src/ clean
#RM -rf results.csv


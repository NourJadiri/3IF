Ce dossier contient l'ensemble des livrables du TP4 pour le binôme B3406 composé de Nour ElJadiri et de Marie Roulier.

La page de manuel est disponible à la racine et s'ouvre avec la commande suivante :
$ man ./analog.man
Si besoin, le fichier readme2.txt contient l'ensemble des informations de ce manuel.

Dans le dossier src se trouvent toutes les classes (interface et réalisation), ainsi qu'une librairie, le module Main et le makefile de l'exécutable analog.
La commande make permet de générer l'exécutable analog, et la commande make clean d'effacer tous les fichiers compilés ainsi que l'exécutable analog.

Dans le dossier Tests se trouve le framework de Tests, ainsi qu'un autre fichier makefile, deux scripts shell pour exécuter ce framework, et un fichier csv pour stocker les résultats des tests.

Dans le dossier bin se trouvera l'exécutable analog, après avoir fait appel à la commande make, que ce soit depuis le dossier Tests ou le dossier src.

Dans le dossier Logs, il est possible de déposer tous les fichiers log dont l'utilisateur aura besoin, cela permet d'organiser un peu mieux ce dossier.

Les commandes suivantes permettent de répondre aux besoins spécifiés dans le TP :
- créer l'exécutable analog - depuis les dossiers src ou Tests - : $ make
- lancer le framework de Tests - depuis le dossier Tests uniquement - : $ make test 
- effacer tous les fichiers compilés ainsi que l'exécutable - depuis les dossiers src ou Tests - : $ make clean

---------------
Pour les tests, pour chaque colonne, il y a trois différents résultats d'exécution possibles :
- 0 : le test ne s'est pas exécuté correctement (FAILED)
- 1 : le test s'est bien passé (PASSED)
- 2 : le test de comparaison de cette colonne n'a pas été effectué car non nécessaire

Un petit exemple pour mieux comprendre :

Test ID;Return code validation;Out result;StdErr result;File creation result;Global result
Test1;2;1;2;2;1

Le test n°1 n'a pas comparé de code de retour, ni de message d'erreur ou de création de fichiers (résultats valent 2).
Il a uniquement comparé une sortie sur console, qui a été correctement exécutée (résultat vaut 1).
Ainsi, le résultat global est égal à 1 -> le test est validé (PASSED).

-----------------
NOTE IMPORTANTE :
Nous supposons que l'utilisateur exécutera correctement le framework de Tests, c'est-à-dire qu'il fera appel aux scripts shell, soit en utilisant directement les commandes make, puis make test, soit en utilisant ./mktest.sh. En effet, dans ce script se trouve des commandes de réinitialisation nécessaire pour certains tests. S'il ne fait pas cela, les résultats des tests pourraient être altérés.
En exécutant un à un les tests à la main sans prêter attention aux fichiers d'origine et aux fichiers créés, l'utilisateur risque d'altérer le bon déroulement complet du framework de Tests par la suite.
Par précaution (ceci est rappelé dans les commentaires du mktest.sh), une ligne de commande a été rajoutée dans les fichiers run des Tests qui pourraient attendre une entrée de l'utilisateur non prévue initialement dans le test.

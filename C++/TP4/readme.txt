Ce dossier contient l'ensemble des livrables du TP4 pour le binôme B3406 composé de Nour ElJadiri et de Marie Roulier.

La page de manuel est disponible à la racine et s'ouvre avec la commande suivante : man ./analog.man
Si besoin, le fichier readme2.txt contient l'ensemble des informations de ce manuel.

Dans le dossier src se trouvent toutes les classes (interface et réalisation), ainsi qu'une librairie, le module Main et le makefile de l'exécutable analog.
La commande make permet de générer l'exécutable analog, et la commande make clean d'effacer tous les fichiers compilés ainsi que l'exécutable analog.

Dans le dossier Tests se trouve le framework de Tests, ainsi qu'un autre fichier makefile, deux scripts shell pour exécuter ce framework, et un fichier csv pour stocker les résultats des tests.
Ce deuxième makefile permet de créer l'exécutable analog avec la simple commande make, et de lancer le framework de Tests avec la commande make test.
La commande make clean permet d'effacer tous les fichiers compilés ainsi que l'exécutable analog.

Dans le dossier bin se trouvera l'exécutable analog, après avoir fait appel à la commande make, que ce soit depuis le dossier Tests ou le dossier src.

Dans le dossier Logs, il est possible de déposer tous les fichiers log dont vous aurez besoin, cela permet d'organiser un peu mieux ce dossier.

NOTE IMPORTANTE :
Nous supposons que vous exécuterez correctement le framework de Tests, c'est-à-dire que vous ferez appel aux scripts shell, soit en utilisant directement les commandes make puis make test, soit en utilisant ./mktest.sh. En effet, dans ce script se trouve des commandes de réinitialisation nécessaire pour certains tests. Si vous ne faites pas cela, les résultats des tests pourraient être altérés.
En exécutant un à un les tests à la main sans prêter attention aux fichiers d'origine et aux fichiers créés, vous risquez d'altérer le bon déroulement complet du framework de Tests par la suite.
Par précaution (ceci est rappelé dans les commentaires du mktest.sh), une ligne de commande a été rajoutée dans les fichiers run des Tests qui pourraient attendre une entrée de l'utilisateur non prévue initialement dans le test.

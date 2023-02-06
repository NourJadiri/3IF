


La page de manuel de l'application peut être exécutée grâce à la commande suivante : man ./analog.man

Sinon, en voici le texte :



analog(1)                                                     Manuel de Commandes Générales                                                    analog(1)

NOM
       analog - Analyse d’un fichier de log Apache

SYNOPSIS
       analog [-g fichierDot.dot] [-e] [-t heure] [-u fichierTxt.txt] fichierLog.log

DESCRIPTION
       analog est un outil en ligne de commande qui permet d’analyser des requêtes HTTP enregistrées dans un fichier de log fichierLog.log de serveur
       web Apache. analog permet d’afficher les statistiques de logs sur la sortie standard. analog dispose également de quelques options de filtrage,
       ce qui permet d’effectuer différentes analyses. analog peut éventuellement générer un document synthétique de ces statistiques, sous forme de
       graphique au format GraphViz, dans un fichier fichierDot.dot. Il est possible de combiner plusieurs options de filtrage.
       Dans tous les cas (sans et avec options), analog affiche sur la console la liste des 10 documents les plus consultés, dans l’ordre décroissant de
       popularité, avec le nombre de consultations.

OPTIONS
       -g fichierDot.dot
              Spécifie le fichier dans lequel il faut générer le graphique des statistiques au format GraphViz. Chaque page consultée apparaît sous
              forme de nœud, et chaque arc indique le nombre de traversées associées entre deux pages. Un message indiquera qu’un graphe a été généré
              dans le fichier fichierDot.dot. Affiche également la liste des 10 documents les plus consultés.

       -e     Exclut tous les documents ayant des extensions de type image, css ou javascript. Un avertissement indiquera que cette option a été
              utilisée. Affiche également la liste des 10 documents les plus consultés.

       -g heure
              Spécifie la plage horaire [heure, heure + 1[ sur laquelle il faut prendre en compte les logs. Exclut les hits qui ne font pas partie de
              cette fenêtre. Un avertissement indiquera que cette option a été utilisée. Affiche également la liste des 10 documents les plus consultés.

       -g fichierTxt.txt
              Spécifie le fichier de configuration à utiliser contenant la base URL à supprimer des logs. Si ce fichier est vide, l’application analog
              sera exécutée par défaut et déterminera elle-même la base de l’URL afin de la supprimer. Affiche également la liste des 10 documents les
              plus consultés.

CODE DE RETOUR
       analog sort 0 en cas de succès, et >0 si une erreur survient.

NOTES
       Le fichier de log fichierLog.log doit exister et ne doit pas être vide.
       L’option -g ne fonctionne que si le fichier fichierDot.dot est donné et existe. Sinon, analog se terminera.
       L’option -e supprime toute la ligne de log si au moins une des deux pages (cible ou referer) est de type image, css ou javascript. Par exemple,
       si un referer de type .jpg accède à une page .ics, alors ni le referer ni la cible ne seront pris en compte dans l’analyse.
       L’option -u ne fonctionne que si le fichier fichierTxt.txt est donné et existe. Il peut être vide au besoin.
       Si la même commande est entrée plusieurs fois, elle ne sera exécutée qu’une seule fois.
       Un avertissement sera affiché si les statistiques de logs ont été réalisées sur moins de 10 ou même sur aucun log.

EXEMPLES
       $ ./analog fichierLog.log
              Comportement de l’application par défaut. Analyse du fichier fichierLog.log et affichage sur la console des 10 (ou moins) pages les plus
              visitées par ordre croissant de popularité, ainsi que leur nombre de consultations.

       $ ./analog -g fichierDot.dot fichierLog.log
              Analyse du fichier fichierLog.log et affichage sur la console des 10 (ou moins) pages les plus visitées par ordre croissant de popularité,
              ainsi que leur nombre de consultations. Génération du fichier fichierDot.dot au format GraphViz qui représente graphiquement le parcours
              des ressources visitées.

       $ ./analog -e fichierLog.log
              Analyse du fichier fichierLog.log et affichage sur la console des 10 (ou moins) pages les plus visitées qui ne sont pas de type image, css
              ou javascript, par ordre croissant de popularité, ainsi que leur nombre de consultations.

       $ ./analog -t 12 fichierLog.log
              Analyse du fichier fichierLog.log et affichage sur la console des 10 (ou moins) pages les plus visitées entre 12h et 13h, par ordre
              croissant de popularité, ainsi que leur nombre de consultations.

       $ ./analog -u fichierTxt.txt fichierLog.log
              Prise en compte de la base de l’URL qui se trouve dans le fichier fichierTxt.txt, s’il est non vide. Sinon, exécution par défaut de
              l’application analog. Analyse du fichier fichierLog.log et affichage sur la console des 10 (ou moins) pages les plus visitées par ordre
              croissant de popularité, ainsi que leur nombre de consultations.

       $ ./analog -e -g fichierDot.dot fichierLog.log
              Possibilité de combiner plusieurs filtres. Analyse du fichier fichierLog.log et affichage sur la console des 10 (ou moins) pages les plus
              visitées qui ne sont pas de type image, css ou javascript, par ordre croissant de popularité, ainsi que leur nombre de consultations.
              Génération du fichier fichierDot.dot au format GraphViz qui représente graphiquement le parcours des ressources visitées.

AUTEURS
       Nour ElJadiri (mohamed-nour.eljadiri@insa-lyon.fr)
       Marie Roulier (marie.roulier@insa-lyon.fr)

 version 1.0                                                         05 février 2023                                                           analog(1)
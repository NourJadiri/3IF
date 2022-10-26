#include <stdlib.h>

int main(){





    return 0;
}







/*DS Algorithmique - 3IF - lundi 27 mai 2019
--------------------------------------------------------
Deux bateaux de pirates découvrent un trésor sur une ile déserte. Le trésor
est composé d’objets en or et en argent, chaque objet ayant un certain poids.
Chaque bateau peut transporter un certain poids maximal, en plus de la charge actuelle.
Une contrainte supplémentaire : les restrictions de circulation des bateaux de
        pirates dans l’océan où se situe l’ile imposent un chargement d’un seul type d’article
        dans un bateau (dans notre cas : un bateau peut transporter un seul type de métal précieux).
Question : quelle est la quantité totale de métal du trésor (or et argent)
transportable par les deux bateaux en une seule fois ?
Format en entrée
----------------

L'entrée standard sera composée d'une série de nombres entiers positifs séparés
        par des retours à la ligne :
- la capacité vacante du bateau 1 (entier n, 1 <= n <= 10000) ;
- la capacité vacante du bateau 2 (entier m, 1 <= m <= 10000) ;
- le nombre d’objets en argent du trésor (entier pa, 1 <= pa <= 100) ;
- le nombre d’objets en or du trésor (entier po, 1 <= po <= 100) ;
- pa+po nombres entiers positifs, représentants les poids des objets
        (les premiers pa en argent, les suivantes po en or)

Le format en entrée est respecté, vous n'avez pas à faire de test pour le vérifier.

Format en sortie
----------------
La sortie : un nombre entier désignant la quantité totale en or et argent
        qui peut être transportée par les deux bateaux en une seule fois.
La ligne de sortie sera finalisée par un retour à la ligne de type "\r\n".

Exemple 1
-----------
Entrée :
10    // capA
12    // capB
3     // pa
3     // po
5     // weight a1
2
4
8     // weight o1
7
5

Sortie :
21

Explication :
- Bateau 1 : les objets en argent de poids 5 et 4 ;
- Bateau 2 : les objets en or de poids 7 et 5
*/
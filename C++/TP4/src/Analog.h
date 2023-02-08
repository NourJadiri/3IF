/*************************************************************************
                           Analog - interface utilisateur & appels fonctions
                             -------------------
    début                : 17/01/2023
    copyright            : (C) 2023 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Analog> (fichier Analog.h) ----------------
#if ! defined ( ANALOG_H )
#define ANALOG_H

//--------------------------------------------------- Interfaces utilisées
#include "Graph.h"

//------------------------------------------------------------------ Types
typedef std::string url;

//------------------------------------------------------------------------
// Rôle de la classe <Analog>
// La classe Analog permet de verifier que toutes les commandes entrees
// sur la ligne de commande sont correctement utilisees.
// C'est-a-dire qu'il faut entrer un argument en plus si necessaire
// et surtout, pour une utilisation par defaut, il faut donner un fichier
// de log qui existe et qui ne soit pas vide.
// Cette classe se charge egalement de generer le vecteur logs, qui
// stock tous les logs apres filtrage si besoin ; ainsi que le Graph graph
// qui stock tous les logs apres filtrage sous forme de noeuds et d'arcs, à
// partir duquel la classe genere le graph (contenu du fichier .dot lors
// de l'utilisation de la commande -g).
// Enfin, la classe permet d'afficher les messages/avertissements
// ainsi que le top 10
//------------------------------------------------------------------------

class Analog
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    int Launch ( int & argcMain, char * * & argvMain );
    // Mode d'emploi :
    // Transmission des arguments de la ligne de commande lors de son appel
    // argcMain correspond au nombre d'arguments, et argvMain est un tableau
    // qui stock ces arguments.
    // C'est cette methode qui se charge d'appeler les methodes qui permettent
    // de verifier les conditions
    // C'est egalement elle qui se charge de l'affichage sur la console
    // des 10 pages les plus consultees.
    // Contrat :
    // Les parametres doivent etre valides
    // donc toutes les conditions des commandes doivent etre valides
    // sinon, retourne la valeur 1

    const bool * GetCommandes ( ) const;
    // Mode d'emploi :
    // Renvoie le tableau des commandes entree par l'utilisateur

    const int & GetHeure ( ) const;
    // Mode d'emploi :
    // Renvoie l'heure entree par l'utilisateur lors de l'utilisation
    // de la commande -t

    const url & GetUrlUser ( ) const;
    // Mode d'emploi :
    // Renvoie l'URL entree par l'utilisateur lors de l'utilisation
    // de la commande -u

    const std::shared_ptr < Connections > & GetLogs ( ) const;
    // Mode d'emploi :
    // Renvoie le vector des logs apres filtrage

    const std::unique_ptr < Graph > & GetGraph ( ) const;
    // Mode d'emploi :
    // Renvoie le Graph des logs apres filtrage sous forme de noeuds et arcs


//-------------------------------------------- Constructeurs - destructeur
    Analog ( );
    // Mode d'emploi :
    // Constructeur d'un Analog

    ~Analog ( );
    // Mode d'emploi :
    // Destructeur d'un Analog

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    int checkG ( );
    // Mode d'emploi :
    // verification des conditions relatives a la commande -g
    // c'est-a-dire verification du fichier dot
    // le parametre dotFile correspond au suppose nom de fichier dot
    // ecrit par l'utilisateur sur la ligne de commande, apres utilisation
    // de la commande -g.
    // retourne 1 si les conditions ne sont pas verifiees, 0 sinon
    // Contrat :
    // l'attribut dotFile doit etre un string valide (non vide)

    int checkT ( const std::string & hour ) ;
    // Mode d'emploi :
    // verification des conditions relatives a la commande -t
    // c'est-a-dire verification de l'heure entree sur la ligne de commande
    // le parametre hour correspond a la supposee heure ecrite par l'utilisateur
    // sur la ligne de commande, apres utilisation de la commande -t.
    // retourne 1 si les conditions ne sont pas verifiees, 0 sinon
    // Contrat :
    // hour doit etre un string valide (non vide)

    int checkU ( const std::string & fichierConfig );
    // Mode d'emploi :
    // verification des conditions relatives a la commande -u
    // c'est-a-dire verification du fichier entre sur la ligne de commande
    // le parametre fichierConfig correspond au suppose nom de fichier txt
    // ecrit par l'utilisateur sur la ligne de commande, apres utilisation de
    // la commande -u.
    // retourne 1 si les conditions ne sont pas verifiees, 0 sinon
    // Contrat :
    // fichierConfig doit etre un string valide (non vide)

    static int verifFichierLog ( const std::string & logFile, const std::string & mainArg ) ;
    // Mode d'emploi :
    // verification des conditions relatives a l'utilisation par defaut
    // c'est-a-dire verification de la presence du fichier log ainsi que
    // verification qu'il n'est pas vide.
    // retourne 1 si les conditions ne sont pas verifiees, 0 sinon
    // Contrat :
    // logFile et mainArg doivent etre des strings valides (non vides)

    void executeG ( );
    // Mode d'emploi :
    // permet de generer le graph correspondant aux logs apres filtrage
    // Contrat :
    // l'attribut dotFile doit etre un string valide (non vide)

    void displayHeading ( ) const;
    // Mode d'emploi :
    // affichage sur la console des messages/avertissements en fonction
    // des options sur la ligne de commande
    // Contrat :
    // le tableau commandes doit avoir ete correctement modifie en fonction
    // des commandes choisies par l'utilisateur

    std::ofstream generateDotFile ( );
    // Mode d'emploi :
    // path correspond au fichier dans lequel il faut generer le graph
    // Contrat :
    // l'attribut dotFile doit etre un string valide (non vide)


//----------------------------------------------------- Attributs protégés
    // stock des commandes utilisees sur la ligne de commande
    bool commandes[5] = { true, false, false, false, false };
    // si usage de la commande -g
    std::string dotFile;
    // si usage de la commande -t
    int heure;
    // si usage de la commande -u
    url urlUser;
    // tous les logs apres filtrage
    std::shared_ptr < Connections > logs;
    // tous les logs apres filtrage sous forme de noeuds et arcs
    std::unique_ptr < Graph > graph;
};

#endif // ANALOG_H
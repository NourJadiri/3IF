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
// La classe Analog permet de vérifier que toutes les commandes entrées
// sur la ligne de commande sont correctement utilisées.
// C'est-à-dire qu'il faut entrer un argument en plus si nécessaire
// et surtout, pour quelconque utilisation, il faut donner un fichier
// de log qui existe et qui ne soit pas vide.
// Cette classe se charge également de générer le vecteur logs, qui
// stock tous les logs apres filtrage si besoin ; et génère le graph
// (contenu du fichier .dot lors de l'utilisation de la commande -g).
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
    // Transmission des arguments de la ligne de commande lors de son appel.
    // argcMain correspond au nombre d'arguments, et argvMain est un tableau
    // qui stock ces arguments.
    // C'est cette méthode qui se charge d'appeler les méthodes qui permettent
    // de vérifier les conditions de chaque commande
    // C'est également elle qui se charge de l'affichage sur la console
    // des 10 pages les plus consultées.
    // Contrat :
    // Les paramètres doivent être valides
    // donc toutes les conditions des commandes doivent etre valides
    // sinon, retourne la valeur 1

    const bool * GetCommandes ( ) const;
    // Mode d'emploi :
    // Renvoie le tableau des commandes entrées par l'utilisateur

    const std::string & GetHeure ( ) const;
    // Mode d'emploi :
    // Renvoie l'heure entrée par l'utilisateur lors de l'utilisation
    // de la commande -t

    const url & GetUrlUser ( ) const;
    // Mode d'emploi :
    // Renvoie l'URL entrée par l'utilisateur lors de l'utilisation
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
    // vérification des conditions relatives à la commande -g
    // c'est-à-dire vérification du fichier dot
    // retourne 1 si les conditions ne sont pas verifiées, 0 sinon
    // Contrat :
    // l'attribut dotFile doit être un string valide (non vide)

    int checkT ( ) ;
    // Mode d'emploi :
    // vérification des conditions relatives à la commande -t
    // c'est-à-dire vérification de l'heure entrée sur la ligne de commande
    // retourne 1 si les conditions ne sont pas verifiées, 0 sinon
    // Contrat :
    // heure doit être un string valide (non vide)

    int checkU ( const std::string & fichierConfig );
    // Mode d'emploi :
    // vérification des conditions relatives à la commande -u
    // c'est-à-dire vérification du fichier entré sur la ligne de commande
    // le paramètre fichierConfig correspond au supposé nom de fichier txt
    // écrit par l'utilisateur sur la ligne de commande, après utilisation de
    // la commande -u.
    // retourne 1 si les conditions ne sont pas verifiées, 0 sinon
    // Contrat :
    // fichierConfig doit être un string valide (non vide)

    static int verifFichierLog ( const std::string & logFile, const std::string & mainArg ) ;
    // Mode d'emploi :
    // vérification des conditions relatives à l'utilisation par défaut
    // c'est-à-dire vérification de la présence du fichier log ainsi que
    // vérification qu'il n'est pas vide.
    // retourne 1 si les conditions ne sont pas verifiées, 0 sinon
    // Contrat :
    // logFile et mainArg doivent être des strings valides (non vides)

    void executeG ( );
    // Mode d'emploi :
    // permet de générer le graph correspondant aux logs après filtrage
    // Contrat :
    // l'attribut dotFile doit être un string valide (non vide)

    void displayHeading ( ) const;
    // Mode d'emploi :
    // affichage sur la console des messages/avertissements en fonction
    // des options sur la ligne de commande
    // Contrat :
    // le tableau commandes doit avoir été correctement modifié en fonction
    // des commandes choisies par l'utilisateur
    // les attributs heure et urlUser doivent être des string valides (non vides)

    void generateDotFile ( );
    // Mode d'emploi :
    // écriture dans le fichier dot du graph
    // Contrat :
    // l'attribut dotFile doit être un string valide (non vide)


//----------------------------------------------------- Attributs protégés
    // enregistre les différentes commandes entrées par l'utilisateur
    bool commandes[5] = { true, false, false, false, false };
    // si usage de la commande -g
    std::string dotFile;
    // si usage de la commande -t
    std::string heure = "0";
    // url par défaut si non usage de la commande -u / fichier de config vide
    url urlUser = DEFAULT_URL_BASE;
    // tous les logs après filtrage
    std::shared_ptr < Connections > logs;
    // tous les logs après filtrage sous forme de noeuds et arcs
    std::unique_ptr < Graph > graph;
};

#endif // ANALOG_H
/*************************************************************************
                           Connections  -  description
                             -------------------
    début                : 17/01/2023
    copyright            : (C) 2023 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Connections> (fichier Connections.h) ----------------
#if ! defined ( LOGFILE_MANAGER_H )
#define LOGFILE_MANAGER_H

//--------------------------------------------------- Interfaces utilisées
#include <fstream>
#include "Log.h"
#include <unordered_map>

//------------------------------------------------------------------------
// Rôle de la classe <Connections>
//
//
//------------------------------------------------------------------------

class Connections
{
//----------------------------------------------------------------- PUBLIC

public:
    friend class Graph;

//----------------------------------------------------- Méthodes publiques
    void Init ( const bool * commandes, int heure = 0, const std::string & url = DEFAULT_URL_BASE );
    // Mode d'emploi :
    // Renvoie le vector logs

    const std::vector < std::unique_ptr < Log > > & GetLogs ( ) const;
    // Mode d'emploi :
    // Renvoie le vector logs

    list < std::pair < Cible, int > > Top10Logs ( );
    // Mode d'emploi :
    // determination des 1O noeuds ayant le plus de hits
    // Contrat :
    // les noeuds doivent avoir ete prealablement filtres selon les
    // commandes utilisees par l'utilisateur


//------------------------------------------------- Surcharge d'opérateurs
    friend std::ostream & operator << ( std::ostream & os, Connections & l );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Connections ( );
    // Mode d'emploi (constructeur par defaut) :
    //
    // Contrat :
    //

    explicit Connections ( const std::string & pathToFile );
    // Mode d'emploi (constructeur parametre) :
    // Le constructeur s'occupe d'ouvrir le fichier caratérisé par le chemin pathToFile
    // On ne vérifie pas ici si le fichier existe vraiment car cela est déja effectué
    // au niveau de l'application ( classe Analog )
    // Contrat :
    // Le fichier existe et a la bonne extension

    ~Connections();
    // Mode d'emploi :
    // Destructeur par défaut de Connections



//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    // fichier de log a partir duquel l'import se fait
    std::ifstream logFile;
    // Tableau de logs qui servira a la creation d'un graph si l'utilisateur le demande
    std::vector < std::unique_ptr < Log > > logs;
    // Map qui stock toutes les cibles avec le nombre de hits
    std::unordered_map < Cible, int > hitTable;
    // Liste qui stock le top 10 des pages les plus visitees
    std::list < std::pair < Cible, int > > top10Logs;
};


//-------------------------------- Autres définitions dépendantes de <Connections>
void insertSorted ( std::list < std::pair < Cible, int > > & list, const std::pair < Cible, int > & value );
// Mode d'emploi :
// Fonction qui permet l'insertion d'éléments dans la liste top10 en implémentant
// notre propre relation d'ordre ( d'abord selon les hits puis par ordre alphabétique )
// Contrat :
// la liste et les valeurs à insérer sont bien formés, et correspondent au type précisé


#endif // LOGFILE_MANAGER_H
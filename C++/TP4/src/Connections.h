/*************************************************************************
                           Connections  -  historique des demandes
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
#include <unordered_map>
#include "Log.h"

//------------------------------------------------------------------------
// Rôle de la classe <Connections>
//
//------------------------------------------------------------------------

class Connections
{
//----------------------------------------------------------------- PUBLIC

public:
    friend class Graph;

//----------------------------------------------------- Méthodes publiques
    void Init ( const bool * commandes, int heure, const std::string & url );
    // Mode d'emploi :
    // Renvoie le vector logs

    const std::vector < std::unique_ptr < Log > > & GetLogs ( ) const;
    // Mode d'emploi :
    // Renvoie le vector logs

    std::list < std::pair < Cible, int > > Top10Logs ( );
    // Mode d'emploi :
    // détermination des 1O noeuds ayant le plus de hits
    // Contrat :
    // les noeuds doivent avoir été préalablement filtrés selon les
    // commandes utilisées par l'utilisateur


//------------------------------------------------- Surcharge d'opérateurs
    friend std::ostream & operator << ( std::ostream & os, Connections & l );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Connections ( );
    // Mode d'emploi (constructeur par defaut) :
    // Constructeur par défaut de Connections

    explicit Connections ( const std::string & pathToFile );
    // Mode d'emploi (constructeur parametre) :
    // Le constructeur s'occupe d'ouvrir le fichier de nom pathToFile
    // Pas de vérification de l'existence du fichier car dejà fait précedemment dans
    // la classe Analog
    // Contrat :
    // Le fichier existe et a la bonne extension

    ~Connections();
    // Mode d'emploi :
    // Destructeur par défaut de Connections


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    // fichier de log à partir duquel l'import se fait
    std::ifstream logFile;
    // Tableau de logs qui servira à la création d'un Graph si l'utilisateur le demande
    std::vector < std::unique_ptr < Log > > logs;
    // Map qui stock toutes les cibles avec le nombre de hits
    std::unordered_map < Cible, int > hitTable;
    // Liste qui stock le top 10 des pages les plus visitées
    std::list < std::pair < Cible, int > > top10Logs;
};


//-------------------------------- Autres définitions dépendantes de <Connections>
void insertSorted ( std::list < std::pair < Cible, int > > & list, const std::pair < Cible, int > & value );
// Mode d'emploi :
// Fonction qui permet l'insertion d'éléments dans la list top10 en implémentant
// notre propre relation d'ordre (d'abord selon les hits, puis par ordre alphabétique)
// Contrat :
// la list et les valeurs à insérer sont bien formés, et correspondent au type precisé


#endif // LOGFILE_MANAGER_H
/*************************************************************************
                           LogFile_Manager  -  description
                             -------------------
    début                : 17/01/2023
    copyright            : (C) 2023 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <LogFile_Manager> (fichier LogFile_Manager.h) ----------------
#if ! defined ( LOGFILE_MANAGER_H )
#define LOGFILE_MANAGER_H

//--------------------------------------------------- Interfaces utilisées
#include <fstream>
#include "Log.h"
#include <unordered_map>

//------------------------------------------------------------------------
// Rôle de la classe <LogFile_Manager>
//
//
//------------------------------------------------------------------------

class LogFile_Manager
{
//----------------------------------------------------------------- PUBLIC

public:
    friend class Graph;

//----------------------------------------------------- Méthodes publiques
    void Init ( const bool * commandes, int temps = 0, const string & url = "" );
    // Mode d'emploi :
    // Renvoie le vector logs

    const std::vector < std::shared_ptr < Log > > & GetLogs ( ) const;
    // Mode d'emploi :
    // Renvoie le vector logs

    list < std::pair < Cible , int > > Top10Logs ( );
    // Mode d'emploi :
    // determination des 1O noeuds ayant le plus de hits
    // Contrat :
    // les noeuds doivent avoir ete prealablement filtres selon les
    // commandes utilisees par l'utilisateur


//------------------------------------------------- Surcharge d'opérateurs
    friend std::ostream & operator << ( std::ostream & os, LogFile_Manager & l );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    LogFile_Manager ( );
    // Mode d'emploi (constructeur par defaut) :
    //
    // Contrat :
    //

    explicit LogFile_Manager ( const std :: string & pathToFile );
    // Mode d'emploi (constructeur parametre) :
    //
    // Contrat :
    // Le fichier existe et a la bonne extension

    ~LogFile_Manager();
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------------------------ PRIVE

protected:

    //----------------------------------------------------- Attributs protégés
    std::ifstream logFile; // Fichier de log à partir duquel l'import se fait
    std::vector < std::shared_ptr <Log> > logs; // Tableau de logs qui servira à la création d'un graph si l'utilisateur le demande
    std::unordered_map < Cible , int > hitTable; // Map qui stock toutes les cibles avec le nombre de hits
    std::list < std::pair < Cible , int > >top10Logs; // Liste qui stock le top 10 des pages les plus visitées

};

void insertSorted ( std::list < std::pair < Cible , int > > & list, const std::pair < Cible , int > & value );


#endif // LOGFILE_MANAGER_H
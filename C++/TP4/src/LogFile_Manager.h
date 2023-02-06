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

//------------------------------------------------------------------ Types
typedef std::string path;

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
    // Mode d'emploi :
    //
    // Contrat :
    //


//----------------------------------------------------- Méthodes publiques
    void commandeDefaut ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void commandeE ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    const std::vector < std::shared_ptr < Log > > & GetLogs ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //


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

    explicit LogFile_Manager ( const std :: string & pathToFile, int command = DEFAULT );
    // Mode d'emploi (constructeur parametre) :
    //
    // Contrat :
    //

    ~LogFile_Manager();
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    std :: ifstream logFile;
    std::vector< std::shared_ptr<Log> > logs;
};

#endif // LOGFILE_MANAGER_H
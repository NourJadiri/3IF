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


//----------------------------------------------------- Méthodes publiques

    const std::vector < std::shared_ptr < Log > > & GetLogs ( ) const;
    // Mode d'emploi :
    // Getter qui retourne le vector logs
    // Contrat :
    //

    void Init ( const bool commandes[ ] , int temps = 0 , const string & url = "" );



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
    //----------------------------------------------------- Méthodes protégées


    //----------------------------------------------------- Attributs protégés
    std::ifstream logFile;
    std::vector < std::shared_ptr<Log> > logs;
};

#endif // LOGFILE_MANAGER_H
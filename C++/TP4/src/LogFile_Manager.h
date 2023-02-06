#ifndef INC_3IF_LOGFILE_MANAGER_H
#define INC_3IF_LOGFILE_MANAGER_H
#include <fstream>
#include "Log.h"


//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes


//------------------------------------------------------------------ Types

typedef std::string path;

//------------------------------------------------------------------------

// Rôle de la classe <LogFile_Manager>

//------------------------------------------------------------------------



class LogFile_Manager
{
//----------------------------------------------------------------- PUBLIC
friend class Graph;

public:
//----------------------------------------------------- Méthodes publiques

    friend std::ostream & operator<<( std::ostream & os , LogFile_Manager & l );

    void commandeDefaut ( const std::string & pathToFile );

//-------------------------------------------- Constructeurs - destructeur
    LogFile_Manager() = default;

    explicit LogFile_Manager( const std :: string & pathToFile , const int command = DEFAULT );



    ~LogFile_Manager();

//------------------------------------------------- Surcharge d'opérateurs


//------------------------------------------------------------------ PRIVE

protected:

//----------------------------------------------------- Attributs protégés
    std :: ifstream logFile;

    std::vector< std::shared_ptr<Log> > logs;
public:

    const std::vector<std::shared_ptr<Log>> &GetLogs() const;

//----------------------------------------------------- Méthodes protégées


};

//-------------------------------- Autres définitions dépendantes de <Ensemble>


#endif //INC_3IF_LOGFILE_MANAGER_H

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

public:
//----------------------------------------------------- Méthodes publiques

    friend std::ostream & operator<<( std::ostream & os , LogFile_Manager & l );

//-------------------------------------------- Constructeurs - destructeur
    LogFile_Manager() = default;

    explicit LogFile_Manager( const std :: string & pathToFile );


    ~LogFile_Manager();

//------------------------------------------------- Surcharge d'opérateurs


//------------------------------------------------------------------ PRIVE

protected:

//----------------------------------------------------- Attributs protégés
    std :: ifstream logFile;

    std::vector< std::shared_ptr<Log> > logs;
public:
    const std::vector<std::shared_ptr<Log>> &getLogs() const;

//----------------------------------------------------- Méthodes protégées


};

//-------------------------------- Autres définitions dépendantes de <Ensemble>


#endif //INC_3IF_LOGFILE_MANAGER_H

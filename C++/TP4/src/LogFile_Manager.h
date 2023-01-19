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

//-------------------------------------------- Constructeurs - destructeur
    LogFile_Manager();

    ~LogFile_Manager();

//------------------------------------------------- Surcharge d'opérateurs


//------------------------------------------------------------------ PRIVE

protected:
    path pathToFile;

//----------------------------------------------------- Attributs protégés

//----------------------------------------------------- Méthodes protégées


};

//-------------------------------- Autres définitions dépendantes de <Ensemble>


#endif //INC_3IF_LOGFILE_MANAGER_H

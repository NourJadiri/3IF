#ifndef INC_3IF_LOGMANAGER_H
#define INC_3IF_LOGMANAGER_H
#include <fstream>
#include "Log.h"
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

typedef std::string path;

//------------------------------------------------------------------------

// Rôle de la classe <LogManager>

//------------------------------------------------------------------------



class LogManager
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    LogManager();
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur


//------------------------------------------------------------------ PRIVE

protected:
    path pathToFile;

//----------------------------------------------------- Attributs protégés

//----------------------------------------------------- Méthodes protégées


};

//-------------------------------- Autres définitions dépendantes de <Ensemble>


#endif //INC_3IF_LOGMANAGER_H

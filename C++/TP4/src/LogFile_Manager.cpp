/*************************************************************************
                           Ensemble  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <LogFile_Manager> (fichier LogFile_Manager.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <memory>
#include "LogFile_Manager.h"

using namespace std;

//------------------------------------------------------ Include personnel

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

const vector<std::shared_ptr<Log>> &LogFile_Manager::getLogs() const
{
    return logs;
}

void LogFile_Manager::commandeDefaut(const string &path)
{


}

//------------------------------------------------- Surcharge d'opérateurs

std::ostream &operator<<( ostream &os, LogFile_Manager & l ) {
    for( auto & i : l.logs )
    {
        os << i-> getShortReferer() << " -> " << i->getCible() << endl;
    }

    return os;
}


//-------------------------------------------- Constructeurs - destructeur

LogFile_Manager::LogFile_Manager( const string & pathToFile )
// Algorithme :
//
{
    logFile.open(pathToFile);
    string log;

    while( getline( logFile, log ) )
    {
        logs.push_back( std::make_shared<Log>( log ) );
    }

}

LogFile_Manager::LogFile_Manager( const string &pathTofile, int & command )
{

}


LogFile_Manager :: ~LogFile_Manager() = default;
//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

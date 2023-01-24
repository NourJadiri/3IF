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



//------------------------------------------------- Surcharge d'opérateurs



//-------------------------------------------- Constructeurs - destructeur

LogFile_Manager::LogFile_Manager( const string & pathToFile )
// Algorithme :
//
{
    logFile.open( pathToFile );
    string log;

    while( getline( logFile, log ) )
    {
        logs.push_back( std::make_shared<Log>( log ) );
    }
}

void LogFile_Manager::Display()
{
    for ( auto & i : logs )
    {
        cout << i->getShortReferer() << " -> " << i->getDocumentRequested() << endl;
    }
}

LogFile_Manager :: ~LogFile_Manager() = default;
//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

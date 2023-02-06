/*************************************************************************
                           LogFile_Manager  -  description
                             -------------------
    début                : 17/01/2023
    copyright            : (C) 2023 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <LogFile_Manager> (fichier LogFile_Manager.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <memory>
using namespace std;

//------------------------------------------------------ Include personnel
#include "LogFile_Manager.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
const vector < shared_ptr < Log > > & LogFile_Manager::GetLogs ( ) const
{
    return logs;
} //----- Fin de GetLogs


//------------------------------------------------- Surcharge d'opérateurs
ostream & operator << ( ostream & os, LogFile_Manager & l )
// Algorithme :
//
{
    for ( auto & i : l.logs )
    {
        os << i->GetShortReferer() << " -> " << i->GetCible() << endl;
    }
    return os;
} //----- Fin de operator <<


//-------------------------------------------- Constructeurs - destructeur
LogFile_Manager::LogFile_Manager ( )
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <LogFile_Manager>" << endl;
#endif
} //----- Fin de LogFile_Manager (constructeur par defaut)

LogFile_Manager::LogFile_Manager ( const string & pathToFile, const int command )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur paramétré de <LogFile_Manager>" << endl;
#endif

    logFile.open( pathToFile );
    string log;

    // TODO : il manque le default
    switch( command )
    {
        case DEFAULT:
            commandeDefaut();
            break;
        case E:
            commandeE();
            break;
        case G:
            break;

        default:
            break;
    }
} //----- Fin de LogFile_Manager (constructeur parametre)

LogFile_Manager :: ~LogFile_Manager ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <LogFile_Manager>" << endl;
#endif
} //----- Fin de ~LogFile_Manager

void LogFile_Manager::commandeDefaut ( )
{
    string log;
    while ( getline( logFile, log ) )
    {
        logs.push_back(std::make_shared<Log>(log));
    }
}

void LogFile_Manager::commandeE ( )
{
    string log;
    while( getline ( logFile , log ) )
    {
        auto temp = Log ( log );
        const auto & ext = temp.GetExtension();

        // TODO : chercher les autres extension a exclure
        if ( ext == ".png" || ext == ".jpg" || ext == ".css" || ext == ".js" )
        {
            continue;
        }

        logs.push_back( std::make_shared<Log>(log) );
    }
}
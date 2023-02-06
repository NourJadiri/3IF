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


void LogFile_Manager::Init( const bool *commandes, int temps , const string & url )
{
    string line;

    // On parcourt le fichier de logs
    while ( getline ( logFile , line ) )
    {
        // On extrait les informations de chaque ligne
        auto temp = Log ( line );

        // Si -e et que temp a une extension invalide
        if ( commandes[E] && isExcluded( temp.GetExtension() ) )
        {
            // On ne considère pas temp
            continue;
        }
        // Si -t et que temp a un temps de consultation invalide
        if ( commandes[T] && ( temp.GetHeureConsultation() < temps || temp.GetHeureConsultation() > temps + 1 ) )
        {
            // On ne considère pas temp
            continue;
        }

        // Si -u et que le referer n'a pas l'url de base qui est demandée dans le fichierd e config
        if ( commandes[U] && getBaseFromUrl( temp.GetLongReferer() ) != url )
        {
            continue;
        }

        // Sinon on importe le log
        logs.push_back( make_shared<Log>(temp) );
    }
}

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

LogFile_Manager::LogFile_Manager ( const string & pathToFile )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur paramétré de <LogFile_Manager>" << endl;
#endif

    logFile.open( pathToFile );

} //----- Fin de LogFile_Manager (constructeur parametre)

LogFile_Manager :: ~LogFile_Manager ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <LogFile_Manager>" << endl;
#endif
}//----- Fin de ~LogFile_Manager


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

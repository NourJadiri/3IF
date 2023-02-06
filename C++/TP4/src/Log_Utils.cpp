/*************************************************************************
                           Log_Utils  -  description
                             -------------------
    début                : 17/01/2023
    copyright            : (C) 2023 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Librairie <Log_Utils> (fichier Log_Utils.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <fstream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Log_Utils.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool isValidUrl ( const string & url )
// Algorithme :
// retourne True si l'url suit le bon format
{
    std::regex pattern( "(https?|ftp|file)://[-a-zA-Z0-9+&@#/%?=~_|!:,.;]*[-a-zA-Z0-9+&@#/%=~_|]" );
    return std::regex_match( url, pattern );
} //----- Fin de isValidUrl

string getPathFromUrl ( const string & url )
// Algorithme :
// Parcourt l'url et
{
    std::regex path_regex( "(ftp|https?)://[^/]+/(.*)" );
    std::smatch match;

    if ( std::regex_search( url, match, path_regex ) )
    {
        return match[2];
    }

    return url;
} //----- Fin de getPathFromUrl

string getExtensionFromFile ( const std::string & file )
{
    size_t last_dot_pos = file.find_last_of('.');
    if (last_dot_pos == std::string::npos)
    {
        return "";
    }

    return file.substr(last_dot_pos + 1);
}

string getBaseFromUrl ( const string & url )
// Algorithme :
// Parcourt l'url et
{
    std::regex path_regex( "(ftp|https?)://([^/]+)/(.*)" );
    std::smatch match;

    if ( std::regex_search( url, match, path_regex ) )
    {
        return match[2];
    }

    return url;
} //----- Fin de getBaseFromUrl

bool validExtension( const string & file, const string & ext )
// Algorithme :
//
{
    // verification de l'extension du fichier
    if ( !(file.find("." + ext ) != string::npos ) )
    {
        cerr << endl << "Il faut insérer le fichier " << ext << " ainsi que son extension." << endl;
        return false;
    }
    return true;
} //----- Fin de validExtension

bool fileNotFound ( const string & logFile )
// Algorithme :
//
{
    // fichier bien existant
    ifstream configUrlStream ( logFile );
    if ( !configUrlStream.good() )
    {
        cerr << endl << "Le fichier de log n'existe pas. Merci de rentrer un fichier existant." << endl;
        return true;
    }
    return false;
} //----- Fin de fileNotFound

bool fileIsEmpty ( const string & logFile )
// Algorithme :
//
{
    ifstream configUrlStream ( logFile );

    // vérifier si le fichier est vide
    configUrlStream.seekg( 0, ios_base::end );
    // va a la fin du fichier
    long size;
    size = configUrlStream.tellg(); // get position actuelle = taille du fichier

    if ( size == 0 ) // fichier est vide
    {
        cerr << endl << "Le fichier de log est vide. Merci de rentrer un fichier non vide." << endl;
        return true;
    }
    configUrlStream.clear();
    configUrlStream.seekg( 0 );

    return false;
} //----- Fin de fileIsEmpty

bool connectionSuccess ( int returnCode )
{
    return returnCode == OK || returnCode == PREMANENT_REDIRECT || returnCode == TEMPORARY_REDIRECT;
}


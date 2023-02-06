#include "Log_Utils.h"
#include <fstream>

using namespace std;

bool isValidUrl ( const string & url )
// Algorithme :
// retourne True si l'url suit le bon format
{
    std::regex pattern( "(https?|ftp|file)://[-a-zA-Z0-9+&@#/%?=~_|!:,.;]*[-a-zA-Z0-9+&@#/%=~_|]" );
    return std::regex_match( url, pattern );
}

string getPathFromUrl ( const string &url )
// Algorithme :
// Parcours l'url et
{
    std::regex path_regex("(ftp|https?)://[^/]+/(.*)");
    std::smatch match;

    if ( std::regex_search(url, match, path_regex) )
    {
        return match[2];
    }

    return url;
}

string getBaseFromUrl ( const string & url )
// Algorithme :
// Parcours l'url et
{
    std::regex path_regex("(ftp|https?)://([^/]+)/(.*)");
    std::smatch match;

    if ( std::regex_search(url, match, path_regex) )
    {
        return match[2];
    }

    return url;
}


bool validExtension( const string & file , const string & ext )
{
    // verification de l'extension du fichier
    if ( !(file.find("." + ext ) != string::npos ) )
    {
        cerr << endl << "Il faut insérer le fichier " << ext << " ainsi que son extension." << endl;
        return false;
    }
    else
    {
        return true;
    }
}

bool fileNotFound ( const string & logFile )
{
    // fichier bien existant
    ifstream configUrlStream ( logFile );
    if ( !configUrlStream.good() )
    {
        cerr << endl << "Le fichier de log n'existe pas. Merci de rentrer un fichier existant." << endl;
        return true;
    }
    return false;
}

bool fileIsEmpty ( const string & logFile )
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
    else
    {
        configUrlStream.clear();
        configUrlStream.seekg(0);

        return false;
    }
}


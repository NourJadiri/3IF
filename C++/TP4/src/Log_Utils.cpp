/*************************************************************************
                           Log_Utils  -  gestion de fonctions basiques
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

//---------------------------------------------------- Fonctions publiques
bool isValidUrl ( const string & url )
// Algorithme :
// retourne TRUE si l'url suit le format type d'une adresse URL
{
    std::regex pattern( "(https?|ftp|file)://[-a-zA-Z0-9+&@#/%?=~_|!:,.;]*[-a-zA-Z0-9+&@#/%=~_|]" );
    return std::regex_match( url, pattern );
} //----- Fin de isValidUrl

string getPathFromUrl ( const string & url )
// Algorithme :
// parcours de l'URL pour retrouver le chemin de l'adresse
{
    std::regex path_regex( "(ftp|https?)://[^/]+/(.*)" );
    std::smatch match;

    if ( std::regex_search( url, match, path_regex ) )
    {
        return match[2];
    }

    return url;
} //----- Fin de getPathFromUrl

string getBaseFromUrl ( const string & url )
// Algorithme :
// parcours de l'URL pour retrouver la base de l'adresse (nom de domaine)
{
    std::regex path_regex( "(ftp|https?)://([^/]+)/(.*)" );
    std::smatch match;

    if ( std::regex_search( url, match, path_regex ) )
    {
        return match[2];
    }

    return url;
} //----- Fin de getBaseFromUrl

string getExtensionFromFile ( const std::string & file )
// Algorithme :
// recherche des caracteres apres le point -> extension du fichier
{
    size_t last_dot_pos = file.find_last_of('.');
    if (last_dot_pos == std::string::npos)
    {
        return "";
    }

    return file.substr(last_dot_pos + 1);
} //----- getExtensionFromFile

bool validExtension( const string & file, const string & ext )
// Algorithme :
// compare l'extension en parametre avec celle du fichier
// et retourne TRUE si ce sont les memes
// sinon retourne une erreur
{
    if ( !(file.find("." + ext ) != string::npos ) )
    {
        cerr << endl << "Il faut insérer le fichier " << ext << " ainsi que son extension." << endl;
        return false;
    }
    return true;
} //----- Fin de validExtension

bool fileNotFound ( const string & logFile )
// Algorithme :
// verifie si le fichier en parametre existe, sinon retourne une erreur
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
// verifie si le fichier en parametre est vide, sinon retourne une erreur
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
// Algorithme :
// verifie si le code de retour du log fait partie de ceux pour laquelle la connexion
// a correctement ete etablie
{
    return returnCode == OK || returnCode == PREMANENT_REDIRECT || returnCode == TEMPORARY_REDIRECT
                            || returnCode == PARTIAL_CONTENT || returnCode == NOT_MODIFIED;
} //----- Fin de connectionSuccess

bool isExcluded ( const string & ext )
// Algorithme :
// Recherche par dichotomie de l'extension a exclure dans le tableau extensionsToExclude
// donc raisonnement par ordre alphabetique des extensions
// Retourne TRUE si l'extension est trouvee (donc a exclure)
{
    array < string, 9 > extensionsToExclude = { "bmp", "css", "gif", "ico", "jpeg", "jpg", "js", "png", "tiff" };
    return binary_search( extensionsToExclude.begin(), extensionsToExclude.end(), ext );
} //----- Fin de isExcluded
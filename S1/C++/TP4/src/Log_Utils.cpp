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
    std::regex path_regex( "(ftp://|https?://)?(?:www\\\\.)?([^/]+)(\\/.*)" );
    std::smatch match;

    if ( std::regex_search( url, match, path_regex ) )
    {
        return match[3];
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

string removeParamsFromUrl ( const string & url )
// Algorithme :
// La fonction trouve la première occurence de "?" qui correspond à un paramètre mis en url
// Elle supprime ensuite tout élément présent à partir de ce "?" afin de ne conserver que
// le chemin de l'url
{
    std::string result = url;

    // trouve la position du "?" qui indique le début d'un paramètre
    size_t paramStart = result.find( '?' );

    // si un "?" est trouvé
    if ( paramStart != string::npos )
    {
        // suppression de la suite
        result.erase( paramStart );
    }

    return result;
} //----- Fin de removeParamsFromUrl

string getExtensionFromFile ( const std::string & file )
// Algorithme :
// recherche des caractères après le point -> extension du fichier
{
    size_t last_dot_pos = file.find_last_of( '.') ;
    if ( last_dot_pos == std::string::npos )
    {
        return "";
    }

    return file.substr( last_dot_pos + 1 );
} //----- getExtensionFromFile

bool validExtension( const string & file, const string & ext )
// Algorithme :
// compare l'extension en paramètre avec celle du fichier
// et retourne TRUE si ce sont les mêmes
// sinon retourne une erreur
{
    if ( file.find( "." + ext ) == string::npos )
    {
        cerr << endl << "A " << ext << " file and its extension must be entered." << endl;
        return false;
    }
    return true;
} //----- Fin de validExtension

bool fileNotFound ( const string & logFile )
// Algorithme :
// vérifie si le fichier en paramètre existe, sinon retourne une erreur
{
    // fichier bien existant
    ifstream configUrlStream ( logFile );
    if ( !configUrlStream.good() )
    {
        cerr << endl << "The log file does not exist. Please enter an existing file." << endl;
        return true;
    }
    return false;
} //----- Fin de fileNotFound

bool fileIsEmpty ( const string & logFile )
// Algorithme :
// vérifie si le fichier en paramètre est vide, sinon retourne une erreur
{
    ifstream configUrlStream ( logFile );

    // vérifier si le fichier est vide
    configUrlStream.seekg( 0, ios_base::end );
    // va à la fin du fichier
    long size;
    size = configUrlStream.tellg(); // trouve la position actuelle = taille du fichier

    if ( size == 0 ) // fichier vide
    {
        cerr << endl << "The log file is empty. Please enter a non-empty file." << endl;
        return true;
    }
    configUrlStream.clear();
    configUrlStream.seekg( 0 );

    return false;
} //----- Fin de fileIsEmpty

bool connectionSuccess ( int returnCode )
// Algorithme :
// vérifie si le code de retour du log fait partie de ceux pour laquelle la connexion
// a correctement été établie
{
    return returnCode == OK || returnCode == PREMANENT_REDIRECT || returnCode == TEMPORARY_REDIRECT
                            || returnCode == PARTIAL_CONTENT || returnCode == NOT_MODIFIED;
} //----- Fin de connectionSuccess

bool isExcluded ( const string & ext )
// Algorithme :
// Recherche par dichotomie de l'extension à exclure dans le tableau extensionsToExclude
// donc raisonnement par ordre alphabétique des extensions
// Retourne TRUE si l'extension est trouvée (donc à exclure)
{
    array < string, 9 > extensionsToExclude = { "bmp", "css", "gif", "ico", "jpeg", "jpg", "js", "png", "tiff" };
    return binary_search( extensionsToExclude.begin(), extensionsToExclude.end(), ext );
} //----- Fin de isExcluded
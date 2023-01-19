#include "Log_Utils.h"


using namespace std;

bool isValidUrl ( const string & url )
// Algorithme :
// retourne True si l'url suit le bon format
{
    std::regex pattern( "(https?|ftp|file)://[-a-zA-Z0-9+&@#/%?=~_|!:,.;]*[-a-zA-Z0-9+&@#/%=~_|]" );
    return std::regex_match( url, pattern );
}

string get_path_from_url ( const string & url )
// Algorithme :
// Parcours l'url et
{
    std::regex path_regex("(ftp|https?)://[^/]+/(.*)");
    std::smatch match;

    if ( std::regex_search(url, match, path_regex) )
    {
        return match[2];
    }

    return "";
}

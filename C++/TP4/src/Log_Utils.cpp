#include "Log_Utils.h"


using namespace std;

bool isValidUrl( const std::string &url )
// Algorithme :
// retourne True si l'url suit le bon format
{
    std::regex pattern( "(https?|ftp|file)://[-a-zA-Z0-9+&@#/%?=~_|!:,.;]*[-a-zA-Z0-9+&@#/%=~_|]" );
    return std::regex_match( url, pattern );
}

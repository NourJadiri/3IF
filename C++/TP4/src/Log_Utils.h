//
// Created by Nour on 17/01/2023.
//

#ifndef INC_3IF_LOG_UTILS_H
#define INC_3IF_LOG_UTILS_H

#include <iostream>
#include <algorithm>
#include <regex>
#include <list>

bool isValidUrl ( const std :: string & url );

std::string getPathFromUrl (const std :: string & url );

std::string getBaseFromUrl ( const std :: string & url );

bool validExtension( const std::string & file , const std::string & ext );

bool fileNotFound ( const std::string & logFile );

bool fileIsEmpty ( const std::string & logFile );


#endif //INC_3IF_LOG_UTILS_H

//
// Created by Nour on 17/01/2023.
//

#ifndef INC_3IF_LOG_UTILS_H
#define INC_3IF_LOG_UTILS_H

#include <iostream>
#include <regex>

bool isValidUrl ( const std :: string & url );

std::string getPathFromUrl (const std :: string & url );

std::string getBaseFromUrl ( const std :: string & url );

#endif //INC_3IF_LOG_UTILS_H

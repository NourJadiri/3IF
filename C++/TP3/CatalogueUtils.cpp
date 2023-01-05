/*************************************************************************
                           CatalogueUtils  -  gestion des separateurs
                             -------------------
    début                : 04/01/2023
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Fichier source <CatalogueUtils> (fichier CatalogueUtils.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;

//------------------------------------------------------ Include personnel
#include "CatalogueUtils.h"

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
int countSeparators ( string & s, char separator )
// Algorithme :
//
{
    int count = 0;

    for (char i: s)
    {
        if (i == separator) {
            count++;
        }
    }

    return count;
} //----- Fin de countSeparators

string * split ( string & str, char seperator )
// Algorithme :
//
{
    // Creating the string array that will hold our strings after splitting
    // hard coded 5 as a value because our format gives exactly 5 splitted strings (optimization)
    // the possibility to use a more generic separation can be considered by using :
    // string * strings = new string[countSparators(str,',') + 1]
    string * strings = new string [ 5 ];

    int currIndex = 0, i = 0;
    int startIndex = 0, endIndex;

    while ( i <= str.size() )
    {
        // if reaches the separator or the end of the string to split
        if ( str[i] == seperator || i == str.size() )
        {
            // New string ends at the separator
            endIndex = i;
            string subStr;

            subStr.append( str, startIndex, endIndex - startIndex );

            strings[ currIndex ] = subStr;
            currIndex += 1;

            // Update the starting index
            startIndex = endIndex + 1;
        }
        i++;
    }
    return strings;
} //----- Fin de split
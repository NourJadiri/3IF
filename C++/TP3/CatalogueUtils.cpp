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
#include <iostream>
#include <fstream>
using namespace std;
//-------------------------------------------------------- Include système

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

            // Update the starting lastIndex
            startIndex = endIndex + 1;
        }
        i++;
    }
    return strings;
} //----- Fin de split

int findNextTripIndex ( ifstream & tripStream )
{
    int lastIndex = 1; // by default, the lastIndex of the first trip to be saved is 1

    // if user decided to append to a file, need to get the lastIndex of the last trip in file
    tripStream.seekg( 0, ios::end ); // move to end of file
    if ( tripStream.tellg() == 0 ) // if file is empty
    {
        tripStream.close();
        return lastIndex; // lastIndex will stay 1
    }

    long pos;
    pos = tripStream.tellg();
    pos--;

    for ( ; ; ) // useful if composed trip as the last trip, to move up in the file until the last number ≠ 0
    {
        // 1st iteration: go to end of last line
        tripStream.seekg( pos-- );

        // 1st iteration: move position back to char just before last line
        char c;
        do
        {
            tripStream.seekg( pos-- );
            c = tripStream.peek();
        }
        while ( pos > 0 && c != '\n' );

        // 1st iteration: go back +1 char to get to beginning of last line (digit)
        tripStream.seekg( 1, ios_base::cur );

        string trip, * data;

        // get the line to extract the number of the trip
        getline( tripStream, trip );
        data = split( trip, ',' );
        if ( !trip.empty() && data[0] != "0" ) // if it's not a composed trip -> digit 0
        {
            lastIndex = stoi( data[0] );
            delete [ ] data;
            tripStream.close();

            return lastIndex + 1; // index of next trip to be saved (index of last trip in file +1)
        }
    }
}  //----- Fin de findNextTripIndex
/*************************************************************************
                           CatalogueUtils  -  gestion des separateurs
                             -------------------
    début                : 04/01/2023
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Librairie <CatalogueUtils> (fichier CatalogueUtils.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//------------------------------------------------------ Include personnel
#include "CatalogueUtils.h"

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
int countSeparators ( string & s, char separator )
// Algorithme :
// compte le nombre de separateurs recherchés dans un string s
{
    int count = 0;

    for (char i : s)
    {
        if ( i == separator )
        {
            count++;
        }
    }
    return count;
} //----- Fin de countSeparators

string * split ( string & str, char seperator )
// Algorithme :
// creation d'un tableau de string qui separe et stock les parties d'un trajet apres splitting
// la valeur de 5 a été forcée car notre format aura toujours exactement 5 separateurs ','
// la possibilite d'utiliser cette methode de facon plus generique peut se faire en utilisant
// la methode countSeparators : string * strings = new string[ countSparators( str, ',' ) + 1 ]
{
    string * strings = new string [ 5 ];

    int currIndex = 0, i = 0;
    int startIndex = 0, endIndex;

    while ( i <= str.size() )
    {
        // if reaches the separator or the end of the string to split
        if ( str[ i ] == seperator || i == str.size() )
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
// Algorithme :
// Parcours du fichier donné en partant de la fin, et remonte progressivement jusqu'à
// trouver un indice de trajet qui soit different de 0
// Retourne cet indice augmenté de 1
{
    int lastIndex = 1; // by default, the lastIndex of the first trip to be saved is 1

    // if user decided to append to a file, need to get the lastIndex of the last trip in file
    tripStream.seekg( 0, ios::end ); // move to end of file
    if ( tripStream.tellg() == 0 ) // if file is empty
    {
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
        if ( pos > 0 )
        {
            tripStream.seekg( 1, ios_base::cur );
        }
            // else the position is the beginning of the file hence the digit is the first character
        else
        {
            tripStream.seekg( 0, ios_base::beg );
        }

        string trip, * data;

        // get the line to extract the number of the trip
        getline( tripStream, trip );
        data = split( trip, ',' );

        if ( !trip.empty() && data[0] != "0" ) // if it's not a composed trip -> digit 0
        {
            lastIndex = stoi( data[0] );

            delete [ ] data;

            return lastIndex + 1; // index of next trip to be saved (index of last trip in file +1)
        }

        delete [ ] data;
    }
}  //----- Fin de findNextTripIndex

string inputValidString ( const string & label )
// Algorithme :
// Utilisation de la fonction string.find() qui permet de
// repérer si l'entrée utilisateur comporte des caractères spéciaux qui pourraient
// compromettre le fichier de sauvegarde des trajets.
// Note :
// Pour l'instant seule la virgule ',' représente une réelle menace pour la sauvegarde,
// mais on pourrait facilement imaginer l'élimination de plus de caractères histoire de
// rendre l'application plus robuste :)
{
    string input;

    cout << "----- Enter the " << label << ": ";

    bool validString;
    do
    {
        cin >> input;
        // The string is valid if it does not contain any ',' character
        validString = !( input.find( ',' ) != string::npos );

        if ( !validString )
        {
            cout << "Please enter a valid " << label;
        }
    }
    while ( !validString );

    return input;
} //----- Fin de inputValidString


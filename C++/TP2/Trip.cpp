/*************************************************************************
                           Trip  -  SOMETHINGXXXXXXXXXX
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER,
                                        Vincent VOIGTLÄNDER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
                           vincent.voigtlander@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Trip> (fichier Trip.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Trip.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
char *Trip::GetStart ( ) const
// Algorithme :
// returns attribute char* start
{
    return start;
} //----- Fin de GetStart

char *Trip::GetEnd ( ) const
// Algorithme :
// returns attribute char* end
{
    return end;
} //----- Fin de GetEnd

int Trip::GetType ( ) const
// Algorithme :
//
{
    return type;
} //----- Fin de GetType


//------------------------------------------------- Surcharge d'opérateurs
bool Trip::operator == ( const Trip &aTrip ) const
// Algorithme :
// Two trips are equal if their start and their ends are the same
{
    return (!strcmp(start, aTrip.GetStart()) && !strcmp(end, aTrip.GetEnd()));
} //----- Fin de operator ==

//-------------------------------------------- Constructeurs - destructeur
Trip::Trip ( )
// Default constructor
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <Trip>" << endl;
#endif
    start = nullptr;
    end = nullptr;
    type = VIRTUAL;
} //----- Fin de Trip (constructeur par défaut)

Trip::Trip ( const char* startCity, const char* endCity )
// Algorithme :
// generic constructor that takes start, and end as a parameter
{
#ifdef MAP
    cout << "Appel au constructeur paramétré de <Trip>" << endl;
#endif
    start = new char[64];
    end = new char[64];
    strcpy(this->start, startCity);
    strcpy(this->end, endCity);
    type = VIRTUAL;
} //----- Fin de Trip (constructeur paramétré)


Trip::~Trip ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Trip>" << endl;
#endif
    delete [] start;
    delete [] end;
} //----- Fin de ~Trip



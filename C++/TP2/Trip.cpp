/*************************************************************************
                           Trip  -  description
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

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Trip::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

char* Trip::GetStart ( )
// Algorithme :
//
{
    return start;
} //----- Fin de GetStart

char* Trip::GetEnd ( )
// Algorithme :
//
{
    return end;
} //----- Fin de GetEnd

void Trip::Display ( )
// Algorithme :
//
{
    cout << "Trip from " << start << " to " << end << endl;
} //----- Fin de Display


//------------------------------------------------- Surcharge d'opérateurs
Trip & Trip::operator = ( const Trip & unTrip )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Trip::Trip ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Trip>" << endl;
#endif
} //----- Fin de Trip


Trip::~Trip ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Trip>" << endl;
#endif
} //----- Fin de ~Trip


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

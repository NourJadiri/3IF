/*************************************************************************
                           Trip  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
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
} //----- Fin de Méthode

char* Trip::GetEnd ( )
// Algorithme :
//
{
    return end;
} //----- Fin de Méthode


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

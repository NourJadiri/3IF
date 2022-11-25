/*************************************************************************
                           Trip  -  Objet trajet
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

char* Trip::GetStart ( ) const
// Algorithme :
//
{
    return start;
} //----- Fin de GetStart

char* Trip::GetEnd ( ) const
// Algorithme :
//
{
    return end;
} //----- Fin de GetEnd


//------------------------------------------------- Surcharge d'opérateurs
ostream& operator<< ( ostream& os, const Trip & aTrip ) {
// Algorithme :
//
    aTrip.Display(os);
    return os;
} //----- Fin de operator<<


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

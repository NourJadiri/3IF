/*************************************************************************
                           SimpleTrip  -  Objet d'un trajet simple
                             -------------------
    début                : 03/01/2023
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <SimpleTrip> (fichier SimpleTrip.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

//------------------------------------------------------ Include personnel
#include "SimpleTrip.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void SimpleTrip::Display ( ) const
{
    cout << "trip from " << start << " to " << end << " by " << transportation;
} //----- Fin de Display

char * SimpleTrip::GetTransport ( ) const
{
    return transportation;
} //----- Fin de GetTransport

void SimpleTrip::SaveTripToFile ( ofstream & tripStream )
// Algorithme :
// permet d'écrire le mode de transport d'un trajet simple
{
    Trip::SaveTripToFile( tripStream );
    tripStream << "," << transportation << endl;
} //----- Fin de SaveTripToFile

//-------------------------------------------- Constructeurs - destructeur
SimpleTrip::SimpleTrip ( const char * aStart, const char * aEnd,
                         const char * aTransportation )
                         : Trip( aStart, aEnd )
{
#ifdef MAP
    cout << "Appel au constructeur de <SimpleTrip>" << endl;
#endif
    type = SIMPLE_TRIP;
    if ( aTransportation == nullptr )
    // otherwise seg fault
    {
        transportation = new char [ 64 ];
        return;
    }
    transportation = new char [ strlen( aTransportation ) + 1 ];
    strcpy( transportation, aTransportation );
} //----- Fin de SimpleTrip

SimpleTrip::~SimpleTrip ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <SimpleTrip>" << endl;
#endif
    delete [ ] transportation;
} //----- Fin de ~SimpleTrip
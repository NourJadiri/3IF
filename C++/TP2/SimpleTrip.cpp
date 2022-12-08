/*************************************************************************
                           SimpleTrip  -  Objet d'un trajet simple
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER,
                                        Vincent VOIGTLÄNDER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
                           vincent.voigtlander@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <SimpleTrip> (fichier SimpleTrip.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "SimpleTrip.h"

//----------------------------------------------------------------- PUBLIC

//-------------------------------------------- Constructeurs - destructeur
SimpleTrip::SimpleTrip ( const char* aStart, const char* aEnd, const char* aTransportation ) : Trip(aStart, aEnd)
// Calls generic Trip constructor
// Copies the transportation
{
#ifdef MAP
    cout << "Appel au constructeur de <SimpleTrip>" << endl;
#endif
    transportation = new char[64];
    type = SIMPLE_TRIP;
    strcpy(transportation , aTransportation);
} //----- Fin de SimpleTrip


SimpleTrip::~SimpleTrip ( )
// Destructor
// Frees the space allocated to transportation
{
#ifdef MAP
    cout << "Appel au destructeur de <SimpleTrip>" << endl;
#endif
    delete [] transportation;
} //----- Fin de ~SimpleTrip

//----------------------------------------------------- Méthodes publiques
void SimpleTrip::Display ( ) const
// Algorithme :
//
{
    cout << "Trip from " << start << " to " << end << " by " << transportation;
}

char* SimpleTrip::GetTransport ( ) const {
    return transportation;
}
//----- Fin de GetTransport


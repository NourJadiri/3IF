/*************************************************************************
                           ComposedTrip  -  Objet d'un trajet compose
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER,
                                        Vincent VOIGTLÄNDER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
                           vincent.voigtlander@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <ComposedTrip> (fichier ComposedTrip.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "ComposedTrip.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//-------------------------------------------- Constructeurs - destructeur

ComposedTrip::ComposedTrip ( const char* aStart, const char* aEnd, const char* aTransportation ) : Trip(aStart, aEnd)

{

    transportation = new char[64];
    strcpy(this->transportation , aTransportation);
} //----- Fin de SimpleTrip

//----------------------------------------------------- Méthodes publiques
void ComposedTrip::Display ( ostream& os ) const
// Algorithme :
//
{
    os << "not yet implemented!"; 
} //----- Fin de Display

void AddSimpleTrip (SimpleTrip* newSTrip)
// Algorithme :
//
{
    ; // not implemented 
} //----- Fin de AddSimpleTrip


//------------------------------------------------- Surcharge d'opérateurs
ostream& operator<< ( ostream & os, const ComposedTrip & aComposedTrip )
// Algorithme :
//
{
    aComposedTrip.Display(os);
    return os;
} //----- Fin de operator<<


//-------------------------------------------- Constructeurs - destructeur

ComposedTrip::ComposedTrip ( )
// Algorithme :
// Calls generic ComposedTrip constructor
{
#ifdef MAP
    cout << "Appel au constructeur de <SimpleTrip>" << endl;
#endif
    List simpleTripList;
} //---- Fin de ComposedTrip


ComposedTrip::~ComposedTrip ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <ComposedTrip>" << endl;
#endif
} //----- Fin de ~ComposedTrip


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

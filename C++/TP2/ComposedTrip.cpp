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
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "ComposedTrip.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void ComposedTrip::Display ( ) const
// Algorithme :
//
{
    Node * iter = this->trips.GetFirst();

    while ( iter != nullptr )
    {
        iter->Display();
        if ( iter->GetNext() != nullptr )
        {
            cout << " - ";
        }
        iter = iter->GetNext();
    }
    cout << endl;
    delete iter;
} //----- Fin de Display

void ComposedTrip::AddSimpleTrip ( SimpleTrip * newSTrip )
// Algorithme :
// Adds a new simple trip to the composedTrip
{
    trips.AddTrip ( newSTrip );
    strcpy( start, trips.GetFirst()->GetTrip()->GetStart() );
    strcpy( end, newSTrip->GetEnd() );
} //----- Fin de AddSimpleTrip

//-------------------------------------------- Constructeurs - destructeur
ComposedTrip::ComposedTrip ( )
// Algorithme :
// Calls generic ComposedTrip constructor
{
#ifdef MAP
    cout << "Appel au constructeur de <ComposedTrip>" << endl;
#endif
    start = new char [ 64 ];
    end = new char [ 64 ];
    type = COMPOSED_TRIP;
    trips = List();
} //---- Fin de ComposedTrip

ComposedTrip::ComposedTrip ( List & list ) : Trip ( )
// Algorithme :
// Creates a composed trip object from a list
{
#ifdef MAP
    cout << "Appel au constructeur depuis une List de <ComposedTrip>" << endl;
#endif
    start = new char [ 64 ];
    end = new char [ 64 ];
    strcpy( start, list.GetFirst()->GetTrip()->GetStart() );
    trips = list;
    type = COMPOSED_TRIP;

    Node * iter = list.GetFirst();
    while ( iter->GetNext() != nullptr )
    {
        iter = iter->GetNext();
    }

    strcpy( end, iter->GetTrip()->GetEnd() );
} //----- Fin du constructeur de ComposedTrip depuis une List

ComposedTrip::~ComposedTrip ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <ComposedTrip>" << endl;
#endif
    cout << "Destructeur de composedTrip" << endl;
} //----- Fin de ~ComposedTrip
/*************************************************************************
                           ComposedTrip  -  Objet d'un trajet composé
                             -------------------
    début                : 03/01/2023
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
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
{
    Node * iter = this->trips.GetFirst();
    while ( iter != nullptr )
    {
        iter->Display();
        if ( iter->GetNext() != nullptr )
        {
            cout << " + ";
        }
        iter = iter->GetNext();
    }
    delete iter;
} //----- Fin de Display

void ComposedTrip::AddSimpleTrip ( SimpleTrip const * newSTrip )
// Algorithme :
// start correspond à la toute premiere ville de depart du ComposedTrip
// end correspond à la toute derniere ville d'arrivee du ComposedTrip,
// donc à la ville d'arrivée du dernier SimpleTrip ajouté au ComposedTrip
{
    trips.AddTrip (newSTrip );
    strcpy( start, trips.GetFirst()->GetTrip()->GetStart() );
    strcpy( end, newSTrip->GetEnd() );
} //----- Fin de AddSimpleTrip

void ComposedTrip::SaveTripToFile ( ofstream & tripStream )
{
    Trip::SaveTripToFile(tripStream);
    tripStream << ",-" << endl;

    Node * iter = trips.GetFirst();

    while( iter != nullptr )
    {   
        tripStream << 0 << ",";
        iter->GetTrip()->SaveTripToFile(tripStream);
        iter = iter->GetNext();
    } 
}

bool ComposedTrip::IsValid ( )
{

    Node * current = trips.GetFirst();

    Node * next = current->GetNext();


    while(next->GetNext() != nullptr)
    {
        if(strcmp(current->GetTrip()->GetEnd(),next->GetTrip()->GetStart()) != 0)
            return false;

        current = next;
        next = next->GetNext();
    }

    return !strcmp(trips.GetFirst()->GetTrip()->GetStart(),this->GetStart()) && !strcmp(next->GetTrip()->GetEnd(),this->GetEnd())
                                                            && !strcmp(current->GetTrip()->GetEnd(),next->GetTrip()->GetStart());

}

//-------------------------------------------- Constructeurs - destructeur
ComposedTrip::ComposedTrip ( )
// Algorithme :
// Appel du constructeur de List également car un ComposedTrip est une List
// de SimpleTrips
{
#ifdef MAP
    cout << "Appel au constructeur de <ComposedTrip>" << endl;
#endif
    start = new char [ 64 ];
    end = new char [ 64 ];
    type = COMPOSED_TRIP;
    trips = List();
} //---- Fin de ComposedTrip

ComposedTrip::ComposedTrip ( List const & list ) : Trip ( )
// Algorithme :
// Parcours d'une List de SimpleTrip pour créer un ComposedTrip à partir
// des SimpleTrips contenus dans la List
{
#ifdef MAP
    cout << "Appel au constructeur depuis une List de <ComposedTrip>" << endl;
#endif
    Node * iter = list.GetFirst();
    start = new char [ strlen( iter->GetTrip()->GetStart() ) + 1 ];
    strcpy( start, iter->GetTrip()->GetStart() );

    trips = list;
    type = COMPOSED_TRIP;
    while ( iter->GetNext() != nullptr )
    {
        iter = iter->GetNext();
    }
    end = new char [ strlen( iter->GetTrip()->GetEnd() ) + 1 ];
    strcpy( end, iter->GetTrip()->GetEnd() );
} //----- Fin de ComposedTrip (à partir d'une List)

ComposedTrip::~ComposedTrip ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <ComposedTrip>" << endl;
#endif
} //----- Fin de ~ComposedTrip
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

//-------------------------------------------- Constructeurs - destructeur


//----------------------------------------------------- Méthodes publiques

void ComposedTrip::Display ( ) const
// Algorithme :
//
{
    Node *iter = this->trips.GetFirst();

    while(iter != nullptr){
        iter->Display();
        if(iter->getNext() != nullptr) cout<<" - ";
        iter = iter->getNext();
    }

    cout<<endl;
    delete iter;
} //----- Fin de Display

void ComposedTrip::AddSimpleTrip (SimpleTrip* newSTrip)
// Adds a new simple trip to the composedTrip
//
{
    trips.AddTrip(newSTrip);

    strcpy(start,trips.GetFirst()->getTrip()->GetStart());

    strcpy(end,newSTrip->GetEnd());
} //----- Fin de AddSimpleTrip


//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur

ComposedTrip::ComposedTrip ( )
// Algorithme :
// Calls generic ComposedTrip constructor
{
#ifdef MAP
    cout << "Appel au constructeur de <ComposedTrip>" << endl;
#endif
    start = new char[64];
    end = new char[64];
    type = COMPOSED_TRIP;
    trips = List();
} //---- Fin de ComposedTrip


//----------------------------------------------------- Méthodes protégées
ComposedTrip::ComposedTrip(List & list) : Trip()
// Creates a composed trip object from a list
{
    start = new char[64];
    end = new char[64];
    strcpy(start,list.GetFirst()->getTrip()->GetStart());
    trips = list;
    type = COMPOSED_TRIP;

    Node *iter = list.GetFirst();

    while(iter->getNext() != nullptr){
        iter = iter->getNext();
    }

    strcpy(end,iter->getTrip()->GetEnd());

}


ComposedTrip::~ComposedTrip ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <ComposedTrip>" << endl;
#endif
} //----- Fin de ~ComposedTrip

//------------------------------------------------------------------ PRIVE

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

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//-------------------------------------------- Constructeurs - destructeur


//----------------------------------------------------- Méthodes publiques
void ComposedTrip::Display ( ostream& os ) const
// Algorithme :
//
{
    os << "not yet implemented!"; 
} //----- Fin de Display

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

ComposedTrip::ComposedTrip ( ) : Trip()
// Algorithme :
// Calls generic ComposedTrip constructor
{
#ifdef MAP
    cout << "Appel au constructeur de <ComposedTrip>" << endl;
#endif

    type = COMPOSED_TRIP;
    trips = List();
} //---- Fin de ComposedTrip


//----------------------------------------------------- Méthodes protégées
ComposedTrip::ComposedTrip(List & list) : Trip()
// Creates a composed trip object from a list
{
    trips = list;
    type = COMPOSED_TRIP;

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

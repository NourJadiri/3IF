/*************************************************************************
                           SimpleTrip  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <SimpleTrip> (fichier SimpleTrip.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "SimpleTrip.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void SimpleTrip::Display ( ostream& os ) const
// Algorithme :
//
{
    os << "de " << start << " a " << end << " en " << transportation; 
} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs
ostream& operator<<(ostream& os, const SimpleTrip& aSimpleTrip)
// Algorithme :
//
{
    aSimpleTrip.Display(os);
    return os;
} //----- Fin de operator <<


//-------------------------------------------- Constructeurs - destructeur
SimpleTrip::SimpleTrip (const char* aStart, const char* aEnd, const char* aTransportation)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <SimpleTrip>" << endl;
#endif
    
    strcpy(start, aStart);
    strcpy(end, aEnd);
    strcpy(transportation, aTransportation);
} //----- Fin de SimpleTrip


SimpleTrip::~SimpleTrip ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <SimpleTrip>" << endl;
#endif
} //----- Fin de ~SimpleTrip


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

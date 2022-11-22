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
// type SimpleTrip::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

void SimpleTrip::Display ( )
// Algorithme :
//
{
    std::cout << "de " << start << " a " << end << " en " << transportation; 
} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs
SimpleTrip & SimpleTrip::operator = ( const SimpleTrip & aSimpleTrip )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
SimpleTrip::SimpleTrip (char* aStart, char* aEnd, char* aTransportation)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <SimpleTrip>" << endl;
#endif
    
    start = aStart;
    end = aEnd;
    transportation = aTransportation;
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

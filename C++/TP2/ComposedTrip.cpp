/*************************************************************************
                           ComposedTrip  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <ComposedTrip> (fichier ComposedTrip.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;

//------------------------------------------------------ Include personnel
#include "ComposedTrip.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void ComposedTrip::Display ( ostream& os ) const
// Algorithme :
//
{
    os << "not yet implemented!"; 
} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs
ostream& ostream& operator<<(ostream & os, const ComposedTrip & aComposedTrip)
// Algorithme :
//
{
    aComposedTrip.Display(os);
    return os;
} //----- Fin de operator <<


//-------------------------------------------- Constructeurs - destructeur
ComposedTrip::ComposedTrip ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <ComposedTrip>" << endl;
#endif
} //----- Fin de ComposedTrip


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

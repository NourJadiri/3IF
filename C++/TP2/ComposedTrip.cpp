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
} //----- Fin de Display


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

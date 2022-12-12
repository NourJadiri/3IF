/*************************************************************************
                           Trip  -  Objet d'un trajet en général
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER,
                                        Vincent VOIGTLÄNDER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
                           vincent.voigtlander@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Trip> (fichier Trip.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Trip.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
char * Trip::GetStart ( ) const
{
    return start;
} //----- Fin de GetStart

char * Trip::GetEnd ( ) const
{
    return end;
} //----- Fin de GetEnd

int Trip::GetType ( ) const
{
    return type;
} //----- Fin de GetType

//------------------------------------------------- Surcharge d'opérateurs
bool Trip::operator == ( Trip const & aTrip ) const
// Algorithme :
// 2 Trip sont égaux si leurs villes de départ et arrivée sont égales
// sans distinction de leur type
// on ne compare donc que l'arrivée finale du ComposedTrip si nécessaire
{
    return ( !strcmp( start, aTrip.GetStart() ) && !strcmp( end, aTrip.GetEnd() ) );
} //----- Fin de operator ==

bool Trip::operator <= ( Trip const & aTrip ) const
// Algorithme :
// Trip inférieur ou égal à aTrip si :
// - sa ville de départ est avant dans l'ordre alphabétique
// - ou, s'ils ont les memes villes de départ, si sa ville d'arrivée est avant dans
// l'ordre alphabétique
// - ou, s'ils sont égaux
{
    return ( ( strcmp( start, aTrip.GetStart() ) < 0 )
             || ( !strcmp( start, aTrip.GetStart() )  && strcmp( end, aTrip.GetEnd() ) < 0 )
             || ( * this == aTrip ) );
} //----- Fin de operator <=

bool Trip::operator >= ( Trip const & aTrip ) const
// Algorithme :
// Trip supérieur ou égal à aTrip si :
// - sa ville de départ est après dans l'ordre alphabétique
// - ou, s'ils ont les memes villes de départ, si sa ville d'arrivée est après dans
// l'ordre alphabétique
// - ou, s'ils sont égaux
{
    return ( ( strcmp( start, aTrip.GetStart() ) > 0 )
             || ( !strcmp( start, aTrip.GetStart() )  && strcmp( end, aTrip.GetEnd() ) > 0 )
             || ( * this == aTrip ) );
} //----- Fin de operator >=

//-------------------------------------------- Constructeurs - destructeur
Trip::Trip ( )
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <Trip>" << endl;
#endif
    start = nullptr;
    end = nullptr;
    type = VIRTUAL;
} //----- Fin de Trip (constructeur par défaut)

Trip::Trip ( char const * startCity, char const * endCity )
{
#ifdef MAP
    cout << "Appel au constructeur paramétré de <Trip>" << endl;
#endif
    start = new char [ strlen( startCity ) + 1 ];
    end = new char [ strlen( endCity ) + 1 ];
    strcpy( start, startCity );
    strcpy( end, endCity );
    type = VIRTUAL;
} //----- Fin de Trip (constructeur paramétré)

Trip::Trip ( Trip const & aTrip)
{
#ifdef MAP
    cout << "Appel au constructeur par référence de <Trip>" << endl;
#endif
    start = new char [ strlen( aTrip.start ) + 1 ];
    end = new char [ strlen( aTrip.end ) + 1 ];
    strcpy( start, aTrip.start );
    strcpy( end, aTrip.end );
    type = VIRTUAL;
} //----- Fin de Trip (constructeur par référence)

Trip::~Trip ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Trip>" << endl;
#endif
    delete [ ] start;
    delete [ ] end;
} //----- Fin de ~Trip
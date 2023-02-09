/*************************************************************************
                           Node  -  élément d'un Graph
                             -------------------
    début                : 17/01/2023
    copyright            : (C) 2023 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Node> (fichier Node.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <map>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Node.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Node::AddReferer ( const Referer & aReferer )
// Algorithme :
// si le referer existe deja, incrementation du poids de l'arc entre ce
// referer et le noeud this
// sinon, creation de ce referer et initialisation du poids de l'arc a 1
// incrementation du nombre total de hits du noeud this
{
    if ( referers.find( aReferer ) != referers.end() )
    {
        referers[ aReferer ] += 1;
    }
    else
    {
        referers[ aReferer ] = 1;
    }
    hits++;
} //----- Fin de AddReferer

void Node::AddReferer ( const Node & aNode )
// Algorithme :
// Pour tous les referers de aNode, appel de la méthode
// AddReferer ( const string & ) afin de les rajouter aux referers
// du Node this
{
    for ( auto const & i : aNode.referers )
    {
        this->AddReferer ( i.first );
    }
} //----- Fin de AddReferer

const string & Node::GetName ( ) const
{
    return name;
} //----- Fin de GetName

void Node::Display ( ) const
// Algorithme :
//
{

} //----- Fin de Display

int Node::GetHits ( ) const
{
    return hits;
} //----- Fin de GetHits

int Node::GetId ( ) const
{
    return id;
} //----- Fin de GetId


//------------------------------------------------- Surcharge d'opérateurs
ostream & operator << ( ostream & os, Node & aNode )
// Algorithme :
// affichage des informations relatives du Noeud (nom , hits)
// Parcours de la map de referers et affichage du nom de chaque referer avec le nombre
// d'arcs correspondant
// de l'operateur <<
{
    os << "Node : " << aNode.name << " (" << aNode.hits << ( (aNode.hits == 1) ? "hit)" : "hits)" )<<endl;
    os << "Referers : " << endl;

    for ( auto const & i : aNode.referers )
    {
        os << "\t" << i.first << " : " << i.second << endl;
    }
    return os;
} //----- Fin de operator <<

bool operator < ( Node & a, Node & b )
// Algorithme :
// pour ordonner par nombre de hits, puis alphabetiquement deux noeuds differents
{
    return b.hits != a.hits ? b.hits > a.hits : b.name < a.name;
} //----- Fin de operator <


//-------------------------------------------- Constructeurs - destructeur
Node::Node ( )
// Algorithme :
// Initialise les champs du Node à des valeurs par défaut
// name = "-" , hits = 0 , id = 0
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <Node>" << endl;
#endif
    name = "-";
    hits = 0;
    id = 0;
} //----- Fin de Node (constructeur par défaut)

Node::Node( const Node & aNode )
// Algorithme :
// Copie des attributs simple de aNode vers this
// Copie en profondeur des referers de aNode
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Node>" << endl;
#endif
    id = aNode.id;
    name = aNode.name;
    hits = aNode.hits;
    for ( auto const & i : aNode.referers )
    {
        referers[ i.first ] = i.second;
    }
} //----- Fin de Node (constructeur de copie)

Node::Node ( const Referer & unReferer )
// Algorithme :
// Initialise hits à 0 (un referer n'a par défaut aucun referer, jusqu'à preuve du contraire)
// Le nom du Node devient celui du referer
{
#ifdef MAP
    cout << "Appel au constructeur paramétré de <Node>" << endl;
#endif
    id = 0;
    name = unReferer;
    hits = 0;
} //----- Fin de Node (constructeur paramétré)

Node::Node ( const Cible & uneCible, const Referer & unReferer )
// Algorithme :
// Initialise le nom du Node à <uneCible>.
// Insère le referer passé en paramètre à la map de referers de this
{
#ifdef MAP
    cout << "Appel au constructeur paramétré de <Node>" << endl;
#endif
    id = 0;
    name = uneCible;
    hits = 1;
    referers.insert( std::pair < Referer, int > ( unReferer, 1 ) );
} //----- Fin de Node (constructeur paramétré)

Node::~Node ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Node>" << endl;
#endif
} //----- Fin de ~Node
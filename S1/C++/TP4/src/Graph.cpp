/*************************************************************************
                           Graph  -  noeuds et arcs
                             -------------------
    début                : 17/01/2023
    copyright            : (C) 2023 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Graph> (fichier Graph.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Graph.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Graph::AddNode ( const Node & aNode )
// Algorithme :
// création du noeud s'il n'existe pas déjà dans les noeuds referencés
// ou bien mise à jour de ses referers s'il existait deja
// Un nouveau noeud aura un indice unique indexMax (attribut de Graph)
{
    const Cible & c = aNode.GetName();
    // si la cible existe déjà dans le graph
    if ( vertice.find( c ) != vertice.end() )
    {
        // ajout des referers de aNode dans le node qui est déjà present
        vertice[c]->AddReferer( aNode );
    }
    else // création du noeud pour cette cible
    {
        vertice[c] = make_shared < Node > ( aNode );
        vertice[c]->id = indexMax;
        indexMax++;
    }
} //----- Fin de AddNode

map < Cible, shared_ptr < Node > > Graph::GetVertice ( ) const
{
    return vertice;
} //----- Fin de GetVertice

map < pair < int, int >, int > Graph::GetEdges ( ) const
{
    return edges;
} //----- Fin de GetEdges

void Graph::Display ( )
// Algorithme :
// Parcours de la map vertice pour afficher le nombre de hits de chaque cible
{
    for ( auto const & i : vertice )
    {
        cout << * i.second;
    }
} //----- Fin de Display


//------------------------------------------------- Surcharge d'opérateurs
ostream & operator << ( ostream & os, Graph & g )
// Algorithme :
// Parcours de la map edges pour afficher l'id du referer, de la cible, et le nombre de hits d'une cible
{
    for ( auto const & e : g.edges )
    {
        os << "node" << e.first.first << " -> " << "node" << e.first.second << " : " << e.second << endl;
    }
    return os;
} //----- Fin de operator <<


//-------------------------------------------- Constructeurs - destructeur
Graph::Graph ( )
// Algorithme :
// Initialise indexMax a 0
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <Graph>" << endl;
#endif
    indexMax = 0;
} //----- Fin de Graph (constructeur par défaut)

Graph::Graph ( const shared_ptr < Connections > & logs )
// Algorithme :
// Prend un objet Connections et initialise les sommets du graph à partir de cet historique des connexions.
// Ajout dans la map des cibles des logs
// Ajout aussi dans la map des referers des logs (correspondent à des sommets aussi)
// Initialisation des arcs
{
#ifdef MAP
    cout << "Appel au constructeur paramétré de <Graph>" << endl;
#endif
    indexMax = 0;
    connections = logs;

    for ( auto const & log : connections->GetLogs() )
    {
        // ajout d'une cible + son referer
        AddNode( Node( log->GetCible(), log->GetShortReferer() ) );
        // ajout d'un simple referer
        AddNode( Node( log->GetShortReferer() ) );
    }

    // initialisation des arcs
    initEdges();
} //----- Fin de Graph (constructeur paramétré)

Graph::~Graph ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Graph>" << endl;
#endif
} //----- Fin de ~Graph


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void Graph::initEdges ( )
// Algorithme :
// Parcours de la map de sommets <vertice> et création d'un nouvel arc
// dans la map <edges> si le sommet a au moins un hit (s'il s'agit d'une cible)
// Le edge contiendra les informations < idReferer, idCible, nombreConsultations >
{
    // Parcours des sommets
    for ( auto const & vertex : vertice )
    {
        // Si le sommet correspond à un referer (n'a jamais été consulté)
        if ( vertex.second->hits == 0 )
        {
            // passe au suivant
            continue;
        }
        // Sinon le sommet est une cible, alors parcours de tous les referers de cette cible
        for ( auto const & ref : vertex.second->referers )
        {
            // création d'un nouvel edge qui contient < idCible, idReferer, nombreConsultations >
            edges[ pair < int, int > ( vertice[ ref.first ]->id, vertex.second->id ) ] = ref.second;
        }
    }
} //----- Fin de initEdges
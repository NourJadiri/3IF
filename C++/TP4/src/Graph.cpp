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
#include "Log_Utils.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Graph::AddNode ( const Node & aNode )
// Algorithme :
// creation du noeud s'il n'existe pas deja dans les noeuds references
// ou alors mise a jour de ses referers s'il existait deja
// Un nouveau noeud créé aura l'indice unique indexMax (attribut de graph)
{
    const Cible & c = aNode.GetName();
    // si la cible existe deja dans le graph
    if ( vertice.find( c ) != vertice.end() )
    {
        // ajout des referers de aNode dans le node qui est deja present
        vertice[c]->AddReferer( aNode );
    }
    else // creation du noeud pour cette cible
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
//
{
    for ( auto const & i : vertice )
    {
        cout << * i.second;
    }
} //----- Fin de Display

void Graph::DisplayEdges ( ) const
{
    for ( auto const & e : edges )
    {
        cout << "node" << e.first.first << " -> " << "node" << e.first.second << " : " << e.second << endl;
    }
}


//------------------------------------------------- Surcharge d'opérateurs
ostream & operator << ( ostream & os, Graph & g )
// Algorithme :
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
// Initialise indexMax à 0
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <Graph>" << endl;
#endif
    indexMax = 0;
} //----- Fin de Graph (constructeur par defaut)

Graph::Graph ( const shared_ptr < Connections > & logs )
// Algorithme :
// Prend un objet Connections et initialise les sommets du graph à partir de cet historique des connexions.
// On ajoutera dans la map des sommets les cibles des logs trouvées.
// On ajoutera aussi dans la map des sommet les referers des logs trouvées (correspondent à des sommets aussi)
// Initialise aussi les bords.
{
#ifdef MAP
    cout << "Appel au constructeur paramétré de <Graph>" << endl;
#endif
    indexMax = 0;
    connections = logs;

    for ( auto const & log : connections->GetLogs() )
    {
        AddNode( Node( log->GetCible(), log->GetShortReferer() ) );
        AddNode( Node( log->GetShortReferer() ) );
    }

    initEdges();

} //----- Fin de Graph (constructeur parametre)

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
// Parcours de la map de sommets <vertice> et creation d'un nouvel arc
// dans la map "edges" si le sommet a au moins un hit (s'il s'agit d'une cible)
// Le edge contiendra les informations < idReferer, idCible, nombreConsultations >
{
    // Parcours des sommets
    for ( auto const & vertex : vertice )
    {
        // Si le sommet correspond a un referer (aucune page ne l'a demande)
        if ( vertex.second->hits == 0 )
        {
            // passe au suivant
            continue;
        }
        // Sinon si le sommet est une cible, alors on parcourt tous les referers de cette cible
        for ( auto const & ref : vertex.second->referers )
        {
            // creation d'un nouvel edge qui contient < idCible, idReferer, nombreConsultations >
            edges[ pair < int, int > ( vertice[ ref.first ]->id, vertex.second->id ) ] = ref.second;
        }
    }
} //----- Fin de initEdges
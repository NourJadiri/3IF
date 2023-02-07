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

list < shared_ptr < Node > > Graph::Top10Logs ( )
// Algorithme :
// generation de la list des 10 documents les plus consultes
{
    list < shared_ptr < Node > > top10;

    // parcours de tous les noeuds dont on dispose
    for ( auto & node : vertice )
    {
        if ( node.second->GetHits() > 0 )
        {
            insertSorted( top10, node.second );
        }
        // si la list contient plus de 10 documents, enleve le dernier
        // qui contient donc le moins de hits
        if ( top10.size() > 10 )
        {
            top10.pop_back();
        }
    }
    return top10;
} //----- Fin de Top10Logs

map < Cible, shared_ptr < Node > > Graph::GetVertice ( ) const
{
    return vertice;
} //----- Fin de GetVertice

map < pair < int, int >, int > Graph::GetEdges ( ) const
{
    return edges;
} //----- Fin de GetEdges


//------------------------------------------------- Surcharge d'opérateurs
ostream & operator << ( ostream & os, Graph & g )
// Algorithme :
// Affichage des avertissements si necessaire, et affichage des elements
// du top 10 des pages les plus consultees
{
    if ( g.fileManager->GetLogs().empty() )
    {
        os << "/!\\ Warning: no target has been found /!\\" << endl;
    }
    else if ( g.fileManager->GetLogs().size() < 10 )
    {
        os << "/!\\ Warning: less than 10 targets have been found /!\\" << endl;
    }
    os << endl;

    for ( auto const & node : g.top10Logs )
    {
        os << * node;
    }
    return os;
} //----- Fin de operator <<


//-------------------------------------------- Constructeurs - destructeur
Graph::Graph ( )
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <Graph>" << endl;
#endif
} //----- Fin de Graph (constructeur par defaut)

Graph::Graph ( const string & path )
// Algorithme :
// TODO
{
#ifdef MAP
    cout << "Appel au constructeur paramétré de <Graph>" << endl;
#endif
    indexMax = 0;
    fileManager = make_shared < LogFile_Manager > ( path );
    
    for ( auto const & log : fileManager->GetLogs() )
    {
        AddNode( Node( log->GetCible(), log->GetShortReferer() ) );
        AddNode( Node( log->GetShortReferer() ) );
    }

    top10Logs = Top10Logs();
} //----- Fin de Graph (constructeur parametre)

Graph::Graph ( const shared_ptr < LogFile_Manager > & logs )
// Algorithme :
// TODO
{
#ifdef MAP
    cout << "Appel au constructeur paramétré de <Graph>" << endl;
#endif
    indexMax = 0;
    fileManager = logs;

    for ( auto const & log : fileManager->GetLogs() )
    {
        AddNode( Node( log->GetCible(), log->GetShortReferer() ) );
        AddNode( Node( log->GetShortReferer() ) );
    }

    initEdges();
    top10Logs = Top10Logs();
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
// TODO
{
    for ( auto const & vertex : vertice )
    {
        if ( vertex.second->hits == 0 )
        {
            continue;
        }
        for ( auto const & ref : vertex.second->referers )
        {
            edges[ pair < int, int > ( vertex.second->id,vertice[ ref.first ]->id ) ] = ref.second;
        }
    }
} //----- Fin de initEdges




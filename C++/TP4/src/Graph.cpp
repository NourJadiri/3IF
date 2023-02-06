/*************************************************************************
                           Graph  -  description
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
void Graph::AddNode( const Node & aNode )
// Algorithme :
//
{
    const Cible & c = aNode.GetName();
    // Si une des cibles existe déjà dans notre graph
    if ( nodes.count( c ) > 0 )
    {
        // On ajoute les referers de aNode dans le node qui est deja present
        nodes[c]->AddReferer( aNode );
    }
    else
    {
        nodes[c] = make_shared < Node > ( aNode );
    }
} //----- Fin de AddNode

void Graph::Display ( )
// Algorithme :
//
{
    for ( auto const & i : nodes )
    {
        cout << * (i.second);
    }
} //----- Fin de Display

list < shared_ptr < Node > > Graph::Top10Logs ( )
{
    list < shared_ptr < Node > > top10;

    for ( auto & node : nodes )
    {
        insertSorted( top10 , node.second );

        if ( top10.size( ) > 10 )
        {
            top10.pop_back( );
        }
    }

    return top10;
}

//------------------------------------------------- Surcharge d'opérateurs

ostream & operator << ( ostream & os , Graph & g )
{
    for ( auto const & node : g.top10Logs )
    {
        os << * node;
    }
    return os;
}

//-------------------------------------------- Constructeurs - destructeur
Graph::Graph ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <Graph>" << endl;
#endif
} //----- Fin de Graph (constructeur par defaut)

Graph::Graph ( const string & path, const int command )
{
#ifdef MAP
    cout << "Appel au constructeur paramétré de <Graph>" << endl;
#endif

    fileManager = make_unique < LogFile_Manager > ( path, command );

    AddNode( Node( "-" ) );
    
    for ( auto const & log : fileManager->GetLogs() )
    {
        AddNode( Node(log->GetCible(), log->GetShortReferer() ) );
        AddNode( Node(log->GetShortReferer() ) );
    }

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




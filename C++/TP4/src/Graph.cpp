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
    return os;
} //----- Fin de operator <<


//-------------------------------------------- Constructeurs - destructeur
Graph::Graph ( )
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <Graph>" << endl;
#endif
    indexMax = 0;
} //----- Fin de Graph (constructeur par defaut)

Graph::Graph ( const shared_ptr < LogFile_Manager > & logs )
// Algorithme :
// Prend un objet LogFile_Manager et initialise les sommets du graph à partir de l'historique des connexions.
// On ajoutera dans la map des sommets les cibles des logs trouvées.
// On ajoutera aussi dans la map des sommet les referers des logs trouvées (correspondent à des sommets aussi)
// Initialise aussi les bords.
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
// Parcourt de la map de sommets <vertice> et crée un nouveau bords
// dans la map "edges" si le sommet possède au moins un hit ( s'il s'agit d'une cible )
// Le edge contiendra les informations < idCible , idReferer , nombreConsultations >
{
    // Parcours des sommets
    for ( auto const & vertex : vertice )
    {
        // Si le sommet correspond à un referer ( aucune page ne l'a demandé )
        if ( vertex.second->hits == 0 )
        {
            // On le saute
            continue;
        }
        // Sinon si le sommet est une cible, alors on parcourt tous les referers de cette cible
        for ( auto const & ref : vertex.second->referers )
        {
            // On crée un nouveau edge qui contient < idCible , idReferer , nombreConsultations >
            edges[ pair < int, int > ( vertex.second->id,vertice[ ref.first ]->id ) ] = ref.second;
        }
    }
} //----- Fin de initEdges




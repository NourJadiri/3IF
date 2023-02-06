/*************************************************************************
                           Graph  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Graph> (fichier Graph.h) ----------------
#ifndef GRAPH_H
#define GRAPH_H
//--------------------------------------------------- Interfaces utilisées
#include <list>
#include "Node.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Graph>
//
//
//------------------------------------------------------------------------

class Graph
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void AddNode ( const Node & aNode );

    list< shared_ptr<Node> > CommandeDefaut ( );

    void Display ( );

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
    Graph ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    explicit Graph ( const std::string & path );

    virtual ~Graph ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    std::unique_ptr < LogFile_Manager > fileManager;
    std::map < Cible, std::shared_ptr < Node > > nodes;
};

//------------------------------ Autres définitions dépendantes de <Graph>
template < typename T >
void insertSorted( std::list < shared_ptr < T > > & list , const shared_ptr < T > & value )
// Algorithme :
//
{
    auto comp = [ ] ( const shared_ptr < T > & a, const shared_ptr < T > & b )
    {
        return * b < * a;
    };
    auto it = lower_bound( list.begin(), list.end(), value , comp );
    list.insert( it, value );
} //----- Fin de insertSorted

#endif //GRAPH_H
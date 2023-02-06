/*************************************************************************
                           Graph  -  description
                             -------------------
    début                : 17/01/2023
    copyright            : (C) 2023 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Graph> (fichier Graph.h) ----------------
#if ! defined ( GRAPH_H )
#define GRAPH_H

//--------------------------------------------------- Interfaces utilisées
#include <list>
#include "Node.h"

//------------------------------------------------------------------------
// Rôle de la classe <Graph>
//
//
//------------------------------------------------------------------------

class Graph
{
//----------------------------------------------------------------- PUBLIC

//------------------------------------------------- Surcharge d'opérateurs

    friend ostream & operator<< ( ostream & os , Graph & g );

public:
//----------------------------------------------------- Méthodes publiques
    void AddNode ( const Node & aNode );
    // Mode d'emploi :
    //
    // Contrat :
    //

    list < shared_ptr < Node > > Top10Logs ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void Display ( );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Graph ( );
    // Mode d'emploi (constructeur par defaut) :
    //
    // Contrat :
    //

    explicit Graph ( const std::string & path, int command = DEFAULT );
    // Mode d'emploi (constructeur parametre) :
    //
    // Contrat :
    //

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
    std::list < std::shared_ptr<Node> > top10Logs;
};

//-------------------------------- Autres définitions dépendantes de <Graph>
template < typename T >
void insertSorted ( std::list < shared_ptr < T > > & list, const shared_ptr < T > & value )
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
/*************************************************************************
                           Graph  -  noeuds et arcs
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

// TODO TOUS LES COMMENTAIRES RESTANTS
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
    // Mode d'emploi :
    // creation du noeud aNode s'il n'existe pas deja
    // sinon, au lieu d'ecraser le noeud portant deja le meme non,
    // ajout des referers de aNode aux referers du Node deja existant
    // Contrat :
    // aNode doit etre un Node bien forme

    list < shared_ptr < Node > > Top10Logs ( );
    // Mode d'emploi :
    // determination des 1O noeuds ayant le plus de hits
    // Contrat :
    // les noeuds doivent avoir ete prealablement filtres selon les
    // commandes utilisees par l'utilisateur

    void Display ( );

    void DisplayEdges ( ) const;

    std::map < Cible, std::shared_ptr < Node > > GetVertice ( ) const;
    // Mode d'emploi :
    // Renvoie la map des noeuds

    std::map < pair < int, int >, int > GetEdges ( ) const;
    // Mode d'emploi :
    // Renvoie la map des arcs


//------------------------------------------------- Surcharge d'opérateurs
    friend ostream & operator << ( ostream & os, Graph & g );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Graph ( );
    // Mode d'emploi (constructeur par defaut) :
    // Constructeur d'un Graph

    explicit Graph ( const std::string & path );
    // Mode d'emploi (constructeur parametre) :
    //
    // Contrat :
    //

    explicit Graph ( const shared_ptr < LogFile_Manager > & logs );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Graph ( );
    // Mode d'emploi :
    // Destructeur d'un Graph


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    void initEdges ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//----------------------------------------------------- Attributs protégés
    int indexMax; // TODO
    std::shared_ptr < LogFile_Manager > fileManager; // TODO
    std::map < Cible, std::shared_ptr < Node > > vertice; // TODO
    std::map < std::pair < int, int >, int > edges; // TODO
    // le top 10 des documents les plus consultes
    std::list < std::shared_ptr < Node > > top10Logs;
};


//-------------------------------- Autres définitions dépendantes de <Graph>
template < typename T >
void insertSorted ( std::list < shared_ptr < T > > & list, const shared_ptr < T > & value )
// Algorithme :
//
// Contrat :
{
    auto comp = [ ] ( const shared_ptr < T > & a, const shared_ptr < T > & b )
    {
        return * b < * a;
    };
    auto it = lower_bound( list.begin(), list.end(), value, comp );
    list.insert( it, value );
} //----- Fin de insertSorted

#endif //GRAPH_H
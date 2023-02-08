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

    std::map < Cible, std::shared_ptr < Node > > GetVertice ( ) const;
    // Mode d'emploi :
    // Renvoie la map des noeuds

    std::map < std::pair < int, int >, int > GetEdges ( ) const;
    // Mode d'emploi :
    // Renvoie la map des arcs

    void Display ( );

    void DisplayEdges ( ) const;


//------------------------------------------------- Surcharge d'opérateurs
    friend std::ostream & operator << ( std::ostream & os, Graph & g );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Graph ( );
    // Mode d'emploi (constructeur par defaut) :
    // Constructeur d'un Graph

    explicit Graph ( const std::shared_ptr < LogFile_Manager > & logs );
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
    // Initialise les bords du graph à partir des sommets de celui-ci.
    // Stock les bords dans une map qui associe chaque cible à son referer
    // ainsi que le nombre de consultations de la page.
    // Contrat :
    //

//----------------------------------------------------- Attributs protégés
    int indexMax; // determine l'identifiant d'un noeud

    // Objet recensant toutes les connexions dans le fichier de logs
    // ainsi que toutes les informations utiles (top 10)
    std::shared_ptr < LogFile_Manager > fileManager;

    std::map < Cible, std::shared_ptr < Node > > vertice; // sommets du graph
    std::map < std::pair < int, int >, int > edges; // arcs du graph
};

#endif //GRAPH_H
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

    void Display ( );

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
    Graph ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Graph ( const std::string & path );

    virtual ~Graph ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    std::unique_ptr<LogFile_Manager> fileManager;
    std :: map < Cible , std::shared_ptr<Node> > nodes;

};

//-------------------------------- Autres définitions dépendantes de <Graph>

#endif //GRAPH_H

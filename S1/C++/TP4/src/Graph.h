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
// Structure de données qui représente des relations entre des Nodes
// (aussi appelés sommets). Chaque sommet peut avoir plusieurs relations
// avec d'autres sommets, représentés par des arcs orientés.
// Les arcs ont une direction, indiquant la source et la destination
// d'une relation.
// Le Graph permet de stocker toutes les informations relatives au traçage
// du parcours de l'utilisateur pour un serveur web donné.
//------------------------------------------------------------------------

class Graph
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void AddNode ( const Node & aNode );
    // Mode d'emploi :
    // création du noeud aNode s'il n'existe pas déjà
    // sinon, au lieu d'écraser le noeud portant le meme non,
    // ajout des referers de aNode aux referers du Node déjà existant
    // Contrat :
    // aNode doit être un Node bien formé

    std::map < Cible, std::shared_ptr < Node > > GetVertice ( ) const;
    // Mode d'emploi :
    // Renvoie la map des noeuds

    std::map < std::pair < int, int >, int > GetEdges ( ) const;
    // Mode d'emploi :
    // Renvoie la map des arcs

    void Display ( );
    // Mode d'emploi :
    // Affichage du nombre de hits de chaque cible, utile pour le debug


//------------------------------------------------- Surcharge d'opérateurs
    friend std::ostream & operator << ( std::ostream & os, Graph & g );
    // Mode d'emploi :
    // Surcharge de << qui permet de print les informations relatives aux différents arcs
    // du Graph selon le format suivant :
    // node[i] -> node[j] : [hits]
    // avec i l'id d'un referer, et j celui d'une cible. hits correspond
    // au nombre de fois que j a été accedé depuis i
    // Contrat :
    // Le Graph g est un Graph bien formé, et les indices des sommets sont justes


//-------------------------------------------- Constructeurs - destructeur
    Graph ( );
    // Mode d'emploi (constructeur par défaut) :
    // Constructeur d'un Graph

    explicit Graph ( const std::shared_ptr < Connections > & logs );
    // Mode d'emploi (constructeur parametre) :
    // Le constructeur effectue une copie en surface de Connections et affecte
    // la valeur du pointeur logs a l'attribut connections.
    // Initialise tous les sommets et les arcs du Graph
    // Contrat :
    // logs doit avoir été correctement instancié

    virtual ~Graph ( );
    // Mode d'emploi :
    // Destructeur d'un Graph


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    void initEdges ( );
    // Mode d'emploi :
    // Initialise les arcs du graph à partir des sommets de celui-ci.
    // Stock les bords dans une map qui associe chaque cible à son referer
    // ainsi que le nombre de consultations de la page.
    // Contrat :
    // vertice doit avoir été correctement instancié

//----------------------------------------------------- Attributs protégés
    int indexMax; // détermine l'identifiant d'un noeud

    // Objet recensant toutes les connexions dans le fichier de logs
    // ainsi que toutes les informations utiles (top 10)
    std::shared_ptr < Connections > connections;

    std::map < Cible, std::shared_ptr < Node > > vertice; // sommets du Graph

    // arcs du graph, les arcs suivent le format suivant :
    // [ idReferer, idCible ], nbHits
    std::map < std::pair < int, int >, int > edges;
};

#endif //GRAPH_H
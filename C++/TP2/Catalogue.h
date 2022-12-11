/*************************************************************************
                           Catalogue  -  menu et interface utilisateur
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER,
                                        Vincent VOIGTLÄNDER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
                           vincent.voigtlander@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H

//--------------------------------------------------- Interfaces utilisées
#include "List.h"

//------------------------------------------------------------------------
// Rôle de la classe <Catalogue>
// La classe Catalogue permet de communiquer avec l'utilisateur à travers
// la sortie / entrée standard. Il peut faire 4 choix parmi :
// - afficher le catalogue -> affiche tous les trajets répertoriés
// - ajouter un trajet -> l'utilisateur décide s'il veut ajouter un trajet
// simple ou composé, et entre les villes de départ et d'arrivée ;
// ce trajet sera ensuite ajouté à la liste des trajets
// - recherche d'un trajet -> l'utilisateur décide d'une ville de départ
// et d'arrivée, et le programme cherche si ce trajet est répertorié dans
// la liste des trajets
// La classe Catalogue contient la List des trajets (simples ou composés)
//------------------------------------------------------------------------

typedef struct vertex{
    char* city;
    vertex* next;
}vertex;

class Catalogue
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Launch ( );
    // Mode d'emploi :
    // Menu de l'interface utilisateur sur la sortie standard, qui lui
    // propose plusieurs options, tant qu'il ne choisit pas de quitter
    // Contrat :
    // il faut entrer un CHIFFRE (ce qui est géré par les exceptions si on
    // utilise la librairie limits)

//-------------------------------------------- Constructeurs - destructeur
    Catalogue ( );
    // Mode d'emploi :
    // Construction d'un catalogue avec une liste vide de trajets

    virtual ~Catalogue ( );
    // Mode d'emploi :
    // Destructeur du catalogue

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    virtual void display ( ) const;
    // Mode d'emploi :
    // Affichage du catalogue en appelant la fonction de la classe List

    void add ( );
    // Mode d'emploi :
    // Ajout d'un SimpleTrip ou d'un ComposedTrip si l'utilisateur le décide
    // à la liste de Trips
    // Contrat :
    // L'utilisateur doit respecter les consignes qui s'affichent
    // c'est-à-dire ne pas mettre d'espaces. On suppose également
    // que les chaines de caractères entrées font moins de 64 caractères

    int nbUniqueCities() const;

    void fetch ( ) const;
    // Mode d'emploi :
    // Recherche du trajet demandé par l'utilisateur entre deux villes
    // Le trajet donné à l'utilisateur, s'il existe, sera soit un trajet
    // simple, soit un trajet composé
    // Contrat :
    // L'utilisateur ne doit pas rentrer d'espaces, et les chaines de caractères
    // entrées font moins de 64 caractères

//----------------------------------------------------- Attributs protégés
    List tripList;
    char vertices[][64];

};


#endif // CATALOGUE_H
/*************************************************************************
                           Catalogue  -  menu et interface utilisateur
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
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

    void fetch ( ) const;
    // Mode d'emploi :
    // Recherche du trajet demandé par l'utilisateur entre deux villes
    // Le trajet donné à l'utilisateur, s'il existe, sera soit un trajet
    // simple, soit un trajet composé
    // Contrat :
    // L'utilisateur ne doit pas rentrer d'espaces, et les chaines de caractères
    // entrées font moins de 64 caractères

    void import ( );
    // Mode d'emploi :
    // Demande a l'utilisateur d'entrer le nom du fichier qui contient les
    // trips a importer dans le catalogue
    // Verification que le fichier existe et lecture de ce fichier
    // L'utilisateur peut alors choisir entre quatre options de lecture :
    // 1. lire l'ensemble du fichier pour l'ajouter au catalogue
    // 2. lire un seul type de trajets pour l'ajouter au newSTripcatalogue
    // 3. lire les trajets correspondant a une recherche
    // 4. lire une selection de trajets compris dans un intervalle
    // Contrat :
    // Le nom du fichier doit etre correct (sans espace), et le fichier
    // doit exister et respecter le schema que l'on souhaite

    void importAll ( );

    void importCities ( );
    // Mode d'emploi :
    // Sert à sauvegarder des trips depuis un fichier une ville d'arrivee et/ou de depart
    // Demande a l'utilisateur de choisir entre trois options :
    // 1. depuis ville de depart
    // 2. depuis ville d'arrivee
    // 3. depuis les deux
    /// PAS DE CONTRAT?

    void save ( ) const;
    // Mode d'emploi :
    // Demande a l'utilisateur d'entrer le nom du fichier dans lequel il
    // souhaite enregistrer les fichiers
    // Verification que le fichier existe et ecriture dans ce fichier
    // L'utilisateur peut alors choisir entre quatre options d'ecriture :
    // 1. ecrire l'ensemble du catalogue sur le fichier
    // 2. ecrire un seul type de trajets sur le fichier
    // 3. ecrire les trajets correspondant a une recherche
    // 4. ecrire une selection de trajets compris dans un intervalle
    // Contrat :
    // Le nom du fichier doit etre correct (sans espace)


    void saveAll ( std::ofstream & tripStream ) const;
    // Mode d'emploi :
    //
    // Contrat :

    void saveType ( std::ofstream & tripStream ) const;
    // Mode d'emploi :
    //
    // Contrat :

    void saveFromCities ( std::ofstream & tripStream ) const;
    // Mode d'emploi :
    // Sert à restituer des trips dans un fichier selon une ville d'arrivee et/ou de depart
    // Demande a l'utilisateur de choisir entre trois options :
    // 1. depuis ville de depart
    // 2. depuis ville d'arrivee
    // 3. depuis les deux
    // Contrat :
    // L'utilisateur doit respecter les consignes qui s'affichent
    // c'est-à-dire ne pas mettre d'espaces. On suppose également
    // que les chaines de caractères entrées font moins de 64 caractères

    void saveInterval ( std::ofstream & tripStream ) const;
    // Mode d'emploi :
    //
    // Contrat :

//----------------------------------------------------- Attributs protégés
    List tripList;

};

#endif // CATALOGUE_H
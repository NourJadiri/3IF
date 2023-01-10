/*************************************************************************
                           Catalogue  -  menu et interface utilisateur
                             -------------------
    début                : 03/01/2023
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
// lastIndex est utilise pour la numerotation des trajets lors de
// l'écriture dans un fichier
// - on peut maintenant importer des trajets depuis un fichier, de quatre
// manières différentes (tous les trajets, un seul type de trajet, par
// selection de ville de départ et / ou d'arrivee, par intervalle)
// - on peut faire de même mais pour exporter des trajets du catalogue
// vers un fichier
// ces deux parties ont respectivement ete implementees dans
// CatalogueInputManager.cpp et CatalogueOutputManager.cpp
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
    // Affichage du catalogue en appelant la methode de la classe List

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

    //---------------------------------- Méthodes de CatalogueInputManager
    void import ( );
    // Mode d'emploi :
    // L'utilisateur peut choisir entre quatre options de lecture :
    // 1. lire l'ensemble du fichier pour l'ajouter au catalogue
    // 2. lire un seul type de trajets pour l'ajouter au newSTripcatalogue
    // 3. lire les trajets correspondant a une recherche
    // 4. lire une selection de trajets compris dans un intervalle
    // En fonction du choix de l'utilisateur, la methode adaptée sera appelée.
    // Contrat :
    // L'utilisateur doit entrer un CHIFFRE entre 1 et 5
    // le fichier doit être valide (non-corrompu, non-vide et existant)

    void importAll ( std::ifstream & tripStream );
    // Mode d'emploi :
    // La méthode sert à importer tous les trajets présents dans un fichier
    // vers le catalogue courant
    // Elle effectue un parcours du fichier ligne par ligne, et en fonction du type de trajet
    // rencontré à chaque ligne, elle appelle une des méthodes importSimpleTrip ou importComposedTrip
    // Contrat :
    // tripStream est un flux d'entrée valide, i.e. : le fichier existe et n'est pas vide ou corrompu

    void importAllSimpleTrips ( std::ifstream & tripStream );
    // Mode d'emploi :
    // Cette méthode est utile pour importer tous les trajets simples présents dans le Catalogue
    // Elle sera notemment utilisée dans les méthodes importAll et importTripsFromType
    // Contrat :
    // tripStream est un flux d'entrée valide,  i.e. : le fichier existe et n'est pas vide ou corrompu

    void importAllComposedTrips ( std::ifstream & tripStream );
    // Mode d'emploi :
    // Cette méthode est utile pour importer tous les trajets composés dans le Catalogue
    // Elle sera notemment utilisée dans les méthodes importAll et importTripsFromType
    // Contrat :
    // tripStream est un flux d'entrée valide, i.e. : le fichier existe et n'est pas vide ou corrompu

    void importType ( std::ifstream & tripStream );
    // Mode d'emploi :
    // Permet d'importer à partir d'un fichier tous les trajets qui répondent à un certain type
    // Contrat :
    // l'utilisateur doit entrer un CHIFFRE entre 1 et 3
    // tripStream est un flux d'entrée valide, i.e. : le fichier existe et n'est pas vide ou corrompu

    void importCities ( std::ifstream & tripStream );
    // Mode d'emploi :
    // Sert à sauvegarder des trips depuis un fichier selon une ville d'arrivee et/ou de depart
    // Demande a l'utilisateur de choisir entre trois options (+ option pour retourner au menu) :
    // 1. depuis ville de depart
    // 2. depuis ville d'arrivee
    // 3. depuis les deux
    // En fonction du choix de l'utilisateur, la methode adaptée sera appelée.
    // Contrat :
    // l'utilisateur entre un CHIFFRE entre 1 et 4
    // tripStream est un flux d'entrée valide, i.e : le fichier existe et n'est pas vide ou corrompu

    void importTripsFromDeparture ( std::ifstream & tripStream );
    // Mode d'emploi :
    // La methode se charge d'importer tous les trajets dont la ville de départ
    // correspond au choix de l'utilisateur.
    // Contrat :
    // La ville de départ entrée par l'utilisateur doit être valide (pas d'espace)
    // tripStream est un flux d'entrée valide, i.e. : le fichier existe et n'est pas vide ou corrompu

    void importTripsToArrival ( std::ifstream & tripStream );
    // Mode d'emploi :
    // La methode se charge d'importer tous les trajets dont la ville d'arrivée
    // correspond au choix de l'utilisateur.
    // Contrat :
    // La ville d'arrivée entrée par l'utilisateur doit être valide (pas d'espace)
    // tripStream est un flux d'entrée valide, i.e. : le fichier existe et n'est pas vide ou corrompu

    void importTripsFromTo ( std::ifstream & tripStream );
    // Mode d'emploi :
    // La methode se charge d'importer tous les trajets dont la ville de départ
    // ET la ville d'arrivée correspondent au choix de l'utilisateur.
    // Contrat :
    // Les villes de départ et d'arrivée entrées par l'utilisateur doivent
    // être valides (pas d'espace)
    // tripStream est un flux d'entrée valide, i.e. : le fichier existe et n'est pas vide ou corrompu

    void importInterval ( std::ifstream & tripStream );
    // Mode d'emploi :
    // La methode permet d'importer des trajets situés dans un intervalle que
    // l'utilisateur donne à l'application.
    // Contrat :
    // tripStream est un flux d'entrée valide, i.e. : le fichier existe et n'est pas vide ou corrompu
    // l'utilisateur doit entrer des bornes d'intervalles cohérentes et possibles
    // donc indice de début <= nb de trajets du fichier & indice début <= indice fin

    ifstream askNameFileImport ( ) const;
    // Mode d'emploi :
    // Demande a l'utilisateur d'entrer le nom du fichier qui contient les
    // trajets a importer dans le catalogue
    // La methode est appelée à chaque appel de la methode import().
    // Cela garantit que le nom du fichier et le fichier lui même sont valides.
    // Contrat :
    // Le fichier doit exister, être non vide et non corrompu
    // L'utilisateur ne doit pas mettre de caractères spéciaux ou de '.'
    // Il ne doit pas mettre l'extension non plus

    friend void importTrip ( Catalogue * c, std::ifstream & tripStream, std::string * data,
                             std::string & trip, int tripIndex );
    // Mode d'emploi :
    // Méthode amie à Catalogue qui sert à importer un trajet selon son type
    // La méthode fait appel à importSimpleTrip() ou importComposedTrip() selon
    // le type du trajet lu sur le fichier
    // Catalogue correspond à notre catalogue courant, data aux informations du trajet qui
    // est en train d'être lu, trip à la ligne lue, et tripIndex à son indice dans le fichier
    // Contrat :
    // tripStream est un flux d'entrée valide, i.e. : le fichier existe et n'est pas vide ou corrompu
    // le trajet doit être valide (doit respecter le format texte)

    friend void importComposedTrip ( Catalogue * c, std::ifstream & tripStream, std::string * data,
                                     std::string & trip, int tripIndex );
    // Mode d'emploi :
    // Méthode amie à Catalogue qui sert à importer à partir d'un ficher un seul trajet composé
    // Catalogue correspond à notre catalogue courant, data aux informations du trajet qui
    // est en train d'être lu, trip à la ligne lue, et tripIndex à son indice dans le fichier
    // Contrat :
    // le composedTrip doit être valide et suivre les contraintes du format texte (indices à 0 pour
    // les étapes notamment)
    // tripStream est un flux d'entrée valide, i.e. : le fichier existe et n'est pas vide ou corrompu

    friend void importSimpleTrip ( Catalogue * c, std::ifstream & tripStream, std::string * data,
                                   std::string & trip );
    // Mode d'emploi :
    // Méthode amie à Catalogue qui sert à importer à partir d'un fichier un seul trajet simple
    // Catalogue correspond à notre catalogue courant, data aux informations du trajet qui
    // est en train d'être lu, trip à la ligne lue, et tripIndex à son indice dans le fichier
    // Contrat :
    // le trajet doit être valide (doit respecter le format texte)
    // tripStream est un flux d'entrée valide, i.e. : le fichier existe et n'est pas vide ou corrompu

    //--------------------------------- Méthodes de CatalogueOutputManager
    void save ( );
    // Mode d'emploi :
    // si le catalogue est non vide :
    // L'utilisateur peut  choisir entre quatre options d'ecriture :
    // 1. ecrire l'ensemble du catalogue sur le fichier
    // 2. ecrire un seul type de trajets sur le fichier
    // 3. ecrire les trajets correspondant a une recherche
    // 4. ecrire une selection de trajets compris dans un intervalle
    // En fonction du choix de l'utilisateur, la méthode adaptée sera appelée.
    // Contrat :
    // L'utilisateur doit entrer un CHIFFRE entre 1 et 5
    // Le fichier doit etre valide (non-corrompu)

    void saveAll ( std::ofstream & tripStream );
    // Mode d'emploi :
    // La méthode sert à sauvegarder tous les trajets du catalogue
    // vers le fichier .csv designe par l'utilisateur
    // Contrat :
    // tripStream est un flux de sortie valide, i.e. : le fichier existe ou est créé et n'est pas corrompu

    void saveType ( std::ofstream & tripStream );
    // Mode d'emploi :
    // Permet d'exporter tous les trajets du catalogue qui répondent à un certain type
    // Contrat :
    // l'utilisateur doit entrer un CHIFFRE entre 1 et 3
    // tripStream est un flux de sortie valide, i.e. : le fichier existe ou est créé et n'est pas corrompu

    void saveCities ( std::ofstream & tripStream );
    // Mode d'emploi :
    // Sert à restituer des trips dans un fichier selon une ville d'arrivee et/ou de depart
    // Demande a l'utilisateur de choisir entre trois options (+ option pour retourner au menu) :
    // 1. depuis ville de depart
    // 2. depuis ville d'arrivee
    // 3. depuis les deux
    // En fonction du choix de l'utilisateur, la methode adaptée sera appelée.
    // Contrat :
    // l'utilisateur entre un CHIFFRE entre 1 et 4
    // tripStream est un flux de sortie valide, i.e. : le fichier existe ou est créé et n'est pas corrompu

    void saveTripsFromDeparture ( std::ofstream & tripStream );
    // Mode d'emploi :
    // La methode se charge de restituer tous les trajets dont la ville de départ
    // correspond au choix de l'utilisateur.
    // Contrat :
    // La ville de départ entrée par l'utilisateur doit être valide (pas d'espace)
    // tripStream est un flux de sortie valide, i.e. : le fichier existe ou est créé et n'est pas corrompu

    void saveTripsToArrival ( std::ofstream & tripStream );
    // Mode d'emploi :
    // La methode se charge de restituer tous les trajets dont la ville d'arrivée
    // correspond au choix de l'utilisateur.
    // Contrat :
    // La ville d'arrivée entrée par l'utilisateur doit être valide (pas d'espace)
    // tripStream est un flux de sortie valide, i.e. : le fichier existe ou est créé et n'est pas corrompu

    void saveTripsFromTo ( std::ofstream & tripStream );
    // Mode d'emploi :
    // La methode se charge de restituer tous les trajets dont la ville de départ
    // ET la ville d'arrivée correspondent au choix de l'utilisateur.
    // Contrat :
    // Les villes de départ et d'arrivée entrées par l'utilisateur doivent
    // être valides (pas d'espace)
    // tripStream est un flux de sortie valide, i.e. : le fichier existe ou est créé et n'est pas corrompu

    void saveInterval ( std::ofstream & tripStream );
    // Mode d'emploi :
    // La methode permet de restituer des trajets situés dans un intervalle que
    // l'utilisateur donne à l'application.
    // Contrat :
    // l'utilisateur doit entrer des bornes d'intervalles cohérentes et possibles
    // donc indice de début <= nb de trajets du catalogue & indice début <= indice fin
    // tripStream est un flux de sortie valide, i.e. : le fichier existe ou est créé et n'est pas corrompu

    ofstream askNameFileSave ( );
    // Mode d'emploi :
    // Demande a l'utilisateur d'entrer le nom du fichier dans lequel il faut exporter
    // les trajets du catalogue
    // La methode est appelée à chaque appel de la methode save().
    // Cela garantit que le nom du fichier et le fichier lui même sont valides
    // Appel de la méthode openingMode() pour déterminer, si le fichier existe, quel mode
    // d'ouverture l'utilisateur souhaite
    // Contrat :
    // Le fichier doit être non corrompu
    // L'utilisateur ne doit pas mettre de caractères spéciaux ou de '.'
    // Il ne doit pas mettre l'extension non plus

    void openingMode ( std::ifstream & tempStream, std::ofstream & tripStream, std::string & nameFile, bool & fileOk );
    // Mode d'emploi :
    // Si le fichier existe deja, demande a l'utilisateur s'il souhaite écrire à la suite (append) ou bien
    // écraser le contenu du fichier (overwrite), (ou alors annuler l'opération)
    // s'il faut append, alors appel de la méthode appendOutput()
    // nameFile correspond a la chaine de caractère constituant le nom du fichier
    // fileOk est transmis à la méthode appelante si le mode d'ouverture est résolu
    // Contrat :
    // l'utilisateur entre un CHIFFRE entre 1 et 3
    // nameFile doit respecter les conditions de validité (pas d'espaces, ni caractères spéciaux ou '.')
    // tripStream est un flux de sortie valide, i.e. : le fichier existe ou est créé et n'est pas corrompu
    // tempStream correspond au meme fichier que pour tripStream, mais en tant que flux d'entrée
    // tempStream doit donc être un flux d'entrée valide, i.e. : le fichier existe ou est créé et
    // n'est pas corrompu

    void appendOutput ( std::ifstream & tempStream, std::ofstream & tripStream, std::string & nameFile );
    // Mode d'emploi :
    // Méthode appelée uniquement si l'utilisateur fait le choix d'append son fichier
    // Si le fichier est non vide, récupération de l'indice du dernier trip du trajet
    // Contrat :
    // nameFile doit respecter les conditions de validité (pas d'espaces, ni caractères spéciaux ou '.')
    // tripStream est un flux de sortie valide, i.e. : le fichier existe ou est créé et n'est pas corrompu
    // tempStream correspond au meme fichier que pour tripStream, mais en tant que flux d'entrée
    // tempStream doit donc être un flux d'entrée valide, i.e. : le fichier existe ou est créé et
    // n'est pas corrompu

    //----------------------------------------------------- Attributs protégés
    List tripList;
    int lastIndex = 1;
};

#endif // CATALOGUE_H
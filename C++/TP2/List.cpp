/*************************************************************************
                           List - Structure de données qui gère les Trips
                             -------------------
    début                : 22/11/2022
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER,
                                        Vincent VOIGTLÄNDER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
                           vincent.voigtlander@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <List> (fichier List.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "List.h"
#include "Node.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void List::Display ( ) const
// Algorithme :
// Parcourt la liste et appelle la méthode display de chaque trip qui la compose
{
    // case if list empty already dealt with in Catalogue

    int simpleTrip_number = 1, composedTrip_number = 1;
    Node * current = first;
    while ( current != nullptr )
    {
        if ( current->GetTrip()->GetType() == SIMPLE_TRIP )
        {
            cout << "\tSimple Trip " << simpleTrip_number << " : ";
            simpleTrip_number++;
        }
        else
        {
            cout << "\tComposed Trip " << composedTrip_number << " : ";
            composedTrip_number++;
        }
        current->Display();
        cout << endl;
        current = current->GetNext();
    }
} //----- Fin de Display

void List::AddTrip ( Trip const * aTrip )
// Algorithme :
// Parcours jusqu'à la fin de la liste pour une liste attribuée
// à un ComposedTrip
// Ajout d'un Node qui stock aTrip à la fin de cette liste
{
    Node * toAdd = new Node( aTrip );

    // empty list
    if ( first == nullptr ){
        first = toAdd;
        size++;
        return;
    }

    Node * current = first;

    // Parsing through the linked list
    while ( current->GetNext() != nullptr ){
        current = current->GetNext();
    }
    // end of list insertion
    current->SetNext(toAdd);
    size++;
} //----- Fin de AddTrip

void List::AddTripSorted ( Trip const * aTrip )
// Algorithme :
// Ajout d'un Node (donc d'un trajet) en respectant l'ordre alphabetique
// allocation mémoire d'un nouvel élément + copie en profondeur
// size incrémentée
{
    Node * toAdd = new Node ( aTrip );

    // alphabetical sorting
    Node * current = first;

    // empty list or new Node needs to be first
    if ( size == 0 || * aTrip <= * first->GetTrip() )
    {
        toAdd->SetNext( first );
        first = toAdd;
        size++;
        return;
    }

    // checking for order condition and
    // parsing through the list until the last element
    while ( current->GetNext() != nullptr )
    {
        if ( * (current->GetTrip()) <= * (aTrip) && * (aTrip) <= * (current->GetNext()->GetTrip()) )
        {
            toAdd->SetNext( current->GetNext() );
            current->SetNext( toAdd );
            size++;
            return;
        }
        current = current->GetNext();
    }
    // insertion at end of List
    current->SetNext( toAdd );
    size++;
} //----- Fin de AddTripSorted

void List::FetchTrip ( char const * start, char const * end ) const
// Algorithme :
// Recherche d'un trajet par comparaison des chaines de caractères des villes de départ et d'arrivée
{
    // cas de la List nulle vérifié dans le Catalogue

    Node * current = first;
    bool found = false;
    while ( current != nullptr )
    {
        if ( !strcmp( start, current->GetTrip()->GetStart() ) && !strcmp( end, current->GetTrip()->GetEnd() ) )
        {
            if ( !found )
            // We print this line once whatever the number of matching trips found
            {
                cout << endl << "Trip found!" << endl;
            }
            found = true;
            cout << "\t-> ";
            current->Display();
        }
        current = current->GetNext();
    }

    if ( !found )
    {
        cout << endl << "Trip from " << start << " to " << end << " does not exist..." << endl;
    }
    cout << endl;
} //----- Fin de FetchTrip

bool List::FetchTripAdvanced (char const * start, char const * end, Trip * * storedTrips, bool found,
                              unsigned int i, bool suite ) const
// Algorithme :
// Recherche d'un trajet par appel récursif et comparaison des chaines de caractères
// Parcours de la liste jusqu'à trouver la ville de départ initiale, puis si nécessaire
// Parcours à nouveau de la liste pour trouver un trajet qui commence depuis la ville d'arrivee
// de ce dernier Trip, et ainsi de suite jusqu'à trouver ou non la ville d'arrivée finale
{
    // cas de la List nulle vérifié dans le Catalogue

    cout << "Checking si " << start << " to " << end << " existe " << endl;
    // if we reached the end of our catalogue
    if ( i >= size && !found )
    {
        return false;
    }
    if ( i >= size && found )
    {
        return true;
    }

    bool stored = false;

    Node * current = first;
    while (current != nullptr) {
        // si on recommence pour chercher une possible nouvelle solution
        if (!suite) i = 0;

        // comparaison des villes de départ
        if (!strcmp(start, current->GetTrip()->GetStart()))
        {
            // check if already stored
            int j;
            for (j = 0; j < i; j++) {
                if (current->GetTrip() == storedTrips[j]) {
                    stored = true;
                    break;
                }
            }

            // if the trip is not stored in our temporary array
            if (!stored) {
                storedTrips[i] = current->GetTrip();

                // if the fetching is done (end found)
                if (!strcmp(end, current->GetTrip()->GetEnd())) {
                    found = true;


                    cout << "\t-> ";
                    int k;
                    for (k = 0; k <= i; k++) {
                        if (k > 0) {
                            cout << " THEN ";
                        }
                        storedTrips[k]->Display();
                    }
                    cout << endl;
                }
                else
                {
                    found = FetchTripAdvanced(current->GetTrip()->GetEnd(), end, storedTrips, found, ++i, true);
                }
            }
        }
        current = current->GetNext();
    }

    return found;
} //----- Fin de FetchTripAdvanced

Node * List::GetFirst ( ) const
{
    return first;
} //----- Fin de GetFirst

int List::GetSize ( ) const
{
    return size;
} //----- Fin de GetSize

//-------------------------------------------- Constructeurs - destructeur
List::List ( )
// Algorithme :
// initialisation de la List, size null et premier element pointeur nul
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <List>" << endl;
#endif
    first = nullptr;
    size = DEFAULT_LIST_SIZE;
} //----- Fin de List (constructeur par défaut)

List::List ( Trip const * aTrip )
// Algorithme :
// - initialisation de la List avec un premier élément
// - incrémentation de la taille
{
#ifdef MAP
    cout << "Appel au constructeur paramétré de <List>" << endl;
#endif
    first = new Node( aTrip );
    size = 1;
} //----- Fin de List (constructeur paramétré)

List::~List ( )
// Algorithme :
// Appel du destructeur de Node sur List.first
// Chaque Node supprime son prochain
{
#ifdef MAP
    cout << "Appel au destructeur de <List>" << endl;
#endif
    delete first;
    size = DEFAULT_LIST_SIZE;
} //----- Fin de ~List
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
// Parcours la liste et appelle la méthode display de chaque trip qui la compose
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

        // if the current Trip is a SimpleTrip, line break for next Trip
        // else, no line break to display the next Trip in the ComposedTrip
        if ( current->GetTrip()->GetType() == SIMPLE_TRIP )
        {
            cout << endl;
        }
        current = current->GetNext();
    }
} //----- Fin de Display

void List::AddTrip(const Trip *aTrip)
// Algorithme :
// Parcours jusqu'à la fin de la liste
// Ajout d'un Node qui stock <aTrip> à la fin de cette liste
{
    Node *toAdd = new Node(aTrip);

    // Case of empty list
    if(first == nullptr){
        first = toAdd;
        return;
    }

    Node *current = first;

    // Parsing through the linked list
    while(current->GetNext() != nullptr){
        current = current->GetNext();
    }

    current->SetNext(toAdd);
    size++;

} //----- Fin de AddTrip

void List::AddTripSorted (Trip const * aTrip )
/* Algorithme :
 * Ajout d'un Node (donc d'un trajet) en respectant l'ordre alphabetique
 * allocation mémoire d'un nouvel élément + copie en profondeur
 * size incrémentée
 */
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
/* Algorithme :
 * Recherche d'un trajet par comparaison des chaines de caractères des villes de départ et d'arrivée
 */
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
} //----- Fin de FetchTrip

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
}


//----- Fin de ~List
/*************************************************************************
                           List  -  SMTGXXXXXXXXXXXX
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
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "List.h"
#include "Node.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void List::Display ( ) const
// Algorithme :
// Diplays the trips of the list
{
    // If the first element is null (list still empty)
    if ( first == nullptr )
    {
        cout << "Unfortunately, there are no trips in this list..." << endl;
        return;
    }

    int simpleTrip_number = 1, composedTrip_number = 1;
    Node * current = first;

    while ( current != nullptr )
    {
        if ( current->GetTrip()->GetType() == SIMPLE_TRIP )
        {
            cout << "Simple Trip " << simpleTrip_number << " : ";
            simpleTrip_number++;
        }
        else
        {
            cout << "Composed Trip " << composedTrip_number << " : ";
            composedTrip_number++;
        }
        current->Display();

        if ( current->GetTrip()->GetType() == SIMPLE_TRIP )
        {
            cout << endl;
        }
        current = current->GetNext();
    }
} //----- Fin de Display

void List::AddTrip ( Trip const * aTrip )
// Algorithme :
// Adds a new Node(Trip) to the end of the list and increments size
{
    // If the list is empty , set the first element to the node created
    if (size == 0)
    {
        first = new Node ( aTrip );
        size++;
        return;
    }

    Node * current = first;

    // Parsing through the list till the last element
    while ( current->GetNext() != nullptr )
    {
        current = current->GetNext();
    }

    current->SetNext( new Node( aTrip ) );
    size++;
} //----- Fin de AddTrip

void List::FetchTrip ( const char * start, const char * end ) const
// Algorithme :
// Searches a trip by start and end
// Returns the trip if found, else returns a default null trip
{
    if ( first == nullptr )
    {
        cerr << "error: fetching in empty list" << endl;
        return;
    }

    Node * current = first;
    bool found = false;
    while ( current != nullptr )
    {
        if ( !strcmp( start, current->GetTrip()->GetStart() ) && !strcmp( end, current->GetTrip()->GetEnd() ) )
        {
            if ( !found )
            { // if this is the first trip found, print a txt
                cout << "Trip found!" << endl;
            }
            found = true;
            cout << "\t-> ";
            current->Display();
        }
        current = current->GetNext();
    }

    if ( !found )
    {
        cout << "Trip from " << start << " to " << end << " does not exist..." << endl;
    }
} //----- Fin de FetchTrip

/*void List::Sort ( )
/// TODO : A FINIR !!!
 // Algorithme :
 //
{
    if ( first == nullptr || size == 1 ){
        cout << "Empty list or list with one node..."<<endl; /// TODO : Enlever cette ligne
        return;
    }

    List * sortedList = new List();
    List * temp = this;

    Node * minTrip = first;
    Node * iter = first;

    while ( iter->getNext() != nullptr )
    {
        if ( strcmp( iter->getTrip()->GetStart(), minTrip->getTrip()->GetStart() ) < 0 )
        // Si iter est inferieur au min
        {
            minTrip = iter;
        }
        else if ( !strcmp( iter->getTrip()->GetStart(), minTrip->getTrip()->GetStart() ) )
        // Si les deux trips ont la même start mais pas la même end
        {
            if ( strcmp( iter->getTrip()->GetEnd(), minTrip->getTrip()->GetEnd() ) < 0 )
            {
                minTrip = iter;
            }
        }

        iter = iter->getNext();
    }

} //----- Fin de Sort
*/

Node * List::GetFirst ( ) const
// Algorithme :
//
{
    return first;
} //----- Fin de GetFirst

int List::GetSize ( ) const
// Algorithme :
//
{
    return size;
} //----- Fin de GetSize

//-------------------------------------------- Constructeurs - destructeur
List::List ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <List>" << endl;
#endif
    first = nullptr;
    size = DEFAULT_LIST_SIZE;
} //----- Fin de List (constructeur par défaut)

List::List ( Trip * aTrip )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur paramétré de <List>" << endl;
#endif
    first = new Node( aTrip );
    size = 1;
} //----- Fin de List (constructeur paramétré)

List::~List ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <List>" << endl;
#endif
    cout << "Destructeur de list appelé" << endl;
    delete first;
    size = DEFAULT_LIST_SIZE;
} //----- Fin de ~List

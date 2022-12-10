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

//---------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <limits>
//#include <unistd.h>
using namespace std;

//------------------------------------------------------ Include personnel
#include "ComposedTrip.h"
#include "Catalogue.h"
#include "SimpleTrip.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Catalogue::Launch ( )
// Algorithme :
// Appel de la méthode adéquate en fonction du choix de l'utilisateur
// tant qu'il ne quitte pas le programme
{
    cout << endl << "Welcome to the worst version of Gouggle Mapse :)" << endl;

    int choice;
    for ( ; ; )
    {
        cout << endl << "---------------------------- Menu. ----------------------------" << endl;
        cout << "Enter a NUMBER corresponding to one of the options listed below" << endl;
        cout << "\t1: display the catalogue of the available trips" << endl;
        cout << "\t2: add a trip" << endl;
        cout << "\t3: look for a trip" << endl;
        cout << "\t4: close Gouggle Mapse" << endl;

        // pour gerer les exceptions
        for( ; ; )
        {
            cin >> choice;
            if ( !cin )
            {
                cout << "Wrong input, please enter a NUMBER" << endl;
                //sleep(1);
                // pour clear l'erreur
                cin.clear();
                // pour enlever ce qui reste dans le buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            else break;
        }

        switch ( choice )
        {
            case 1:
                display();
                break;
            case 2:
                add();
                break;
            case 3:
                fetch();
                break;
            case 4:
                goto end;
            default:
                cout << "Incorrect choice, please enter a number between 1 and 4!" << endl;
                //sleep(1);
                continue; // go back to menu
        }
    }
    end:
    cout << "See you soon on Gouggle Mapse :)" << endl;
} //----- Fin de Launch

//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue ( )
{
#ifdef MAP
    cout << "Appel au constructeur de <Catalogue>" << endl;
#endif
} //----- Fin de Catalogue

Catalogue::~Catalogue ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Catalogue>" << endl;
#endif
} //----- Fin de ~Catalogue


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void Catalogue::display ( ) const
{
    if ( tripList.GetSize() == 0 )
    {
        cout << "Unfortunately, there are no trips yet..." << endl;
        //sleep(1);
    } else {
        if ( tripList.GetSize() > 1 )
        {
            cout << "There are " << tripList.GetSize() << " trips ";
        }
        else
        {
            cout << "There is only 1 trip ";
        }
        cout << "available at the moment:" << endl;
        tripList.Display();
    }
} //----- Fin de Display

void Catalogue::add ( )
// Algorithme :
/*
 * Un SimpleTrip et un ComposedTrip sont toujours créés par défaut.
 * Si l'utilisateur n'ajoute qu'un SimpleTrip, le ComposedTrip est supprimé.
 * Si jamais l'utilisateur veut insérer un ComposedTrip, alors une suite de SimpleTrips
 * sera ajoutée au ComposedTrip tant qu'il le décidera.
 */
{
    char * start = new char [ 64 ];
    char * end = new char [ 64 ];
    char * transport = new char [ 64 ];

    cout << "Let's add a trip to our beautiful and (in)exhaustive catalogue!" << endl;
    cout << "Be a good samaritan and DO NOT INSERT SPACES!!! when you write your trip information (please...)" << endl;

    cout << "----- Enter the city of departure : ";
    cin >> start ;

    cout << "----- Enter the city of arrival : ";
    cin >> end;

    cout << "----- Enter the kind of transport used : ";
    cin >> transport;

    char * yesOrNo = new char [ 64 ];
    bool validInput;

    SimpleTrip * newSTrip = new SimpleTrip( start, end, transport );

    // We always consider the eventuality of having a composed trip
    ComposedTrip * newCTrip = new ComposedTrip();

    // Checks if the user input is valid (yes/no)
    do
    {
        cout << "Do you wish to make this trip a composed trip ? [yes/no] : ";
        cin >> yesOrNo;

        validInput = !strcmp( yesOrNo, "yes" ) || !strcmp( yesOrNo, "no" );

        if ( !validInput )
        {
            cout << "Please enter a valid input [yes/no]..." << endl;
            //sleep(1);
        }
    }
    while ( !validInput );

    bool isComposed = !strcmp( yesOrNo, "yes" );

    // If the user wants to make its trip a ComposedTrip
    if ( isComposed )
    {
        bool keepAdding;
        char * addNewStep = new char [ 64 ];
        newCTrip->AddSimpleTrip( newSTrip );

        validInput = false;

        // Adding new simple trips to the composed trip created
        do
        {
            // Force the link between the end of the previous trip and the start of the new trip
            strcpy( start,end );

            cout << "----- Enter the next city of arrival : ";
            cin >> end;

            cout << "----- Enter the kind of transport used : ";
            cin >> transport;

            newCTrip->AddSimpleTrip ( new SimpleTrip( start, end, transport ) );

            // Checks if the user input is valid [yes/no]
            do
            {
                cout << "Do you wish to add another step to this trip ? [yes/no] : ";
                cin >> addNewStep;

                validInput = !strcmp( addNewStep, "yes" ) || !strcmp( addNewStep, "no" );

                if ( !validInput ) {
                    cout << "Please enter a valid input [yes/no]..." << endl;
                    //sleep(1);
                }
            }
            while ( !validInput );

            keepAdding = !strcmp( addNewStep, "yes" );
        }
        while ( keepAdding );

        tripList.AddTrip( newCTrip );

        delete [ ] addNewStep;
    }
    // Else, if they only want to add a simpleTrip
    else
    {
        tripList.AddTrip( newSTrip );

        // Delete the temporary composedTrip created
        delete newCTrip;
    }

    // to free allocated memory in heap (délicieuse mémoire libérée)
    delete [ ] start;
    delete [ ] end ;
    delete [ ] transport;
    delete [ ] yesOrNo;
}

void Catalogue::fetch ( ) const
// Algorithme :
// Si la liste des Trips est non vide, appel de la méthode de la classe List
// pour rechercher le trajet
{
    if ( tripList.GetSize() == 0 ) {
        cout << "Unfortunately, there are no trips yet..." << endl;
    }
    else
    {
        cout << "Let's find you the best way to get to your destination!" << endl;

        char * start = new char [ 64 ];
        char * end = new char [ 64 ];
        cout << "Choose your departure city : ";
        cin >> start;
        cout << "Choose your destination city : " ;
        cin >> end;

        tripList.FetchTrip( start, end );

        // to free allocated memory in heap
        delete [ ] start;
        delete [ ] end;
    }
} //----- Fin de Fetch
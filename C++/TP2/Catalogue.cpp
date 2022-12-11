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
//#include <limits>
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
    cout << "\nWelcome to the worst version of Gouggle Mapse :)" << endl;

    int choice;
    for ( ; ; )
    {
        cout << "\n---------------------------- Menu. ----------------------------" << endl;
        cout << "Enter a NUMBER corresponding to one of the options listed below" << endl;
        cout << "\t1: display the catalogue of the available trips" << endl;
        cout << "\t2: add a trip" << endl;
        cout << "\t3: look for a trip" << endl;
        cout << "\t4: close Gouggle Mapse" << endl;

        cin >> choice;

        // si on pouvait importer la librairie <limits>
        // pour gerer les exceptions
        /*for( ; ; )
        {
            cin >> choice;
            // si on pouvait importer la librairie <limits>
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
        }*/

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
    cout << "\nSee you soon on Gouggle Mapse :)" << endl;
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
        cout << endl << "Unfortunately, there are no trips yet..." << endl;
        //sleep(1);
    } else {
        if ( tripList.GetSize() > 1 )
        {
            cout << endl << "There are " << tripList.GetSize() << " trips ";
        }
        else
        {
            cout << endl << "There is only 1 trip ";
        }
        cout << "available at the moment:" << endl;
        tripList.Display();
    }
} //----- Fin de Display

void Catalogue::add ( )
// Algorithme :
// Création d'un SimpleTrip et d'un ComposedTrip dans tous les cas
// Si jamais l'utilisateur veut insérer un ComposedTrip, alors une suite de SimpleTrips
// sera ajoutée au ComposedTrip tant qu'il le décidera
{
    char * start = new char [ 64 ];
    char * end = new char [ 64 ];
    char * transport = new char [ 64 ];

    cout << endl << "Let's add a trip to our beautiful and (in)exhaustive catalogue!" << endl;
    cout << "Be a good samaritan and DO NOT INSERT SPACES!!! when you write your trip information (please...)" << endl;

    cout << "----- Enter the city of departure: ";
    cin >> start ;

    cout << "----- Enter the city of arrival: ";
    cin >> end;

    cout << "----- Enter the kind of transport used: ";
    cin >> transport;

    // We consider the eventuality of having a composed trip
    // These things are useful trust me.
    char * yesOrNo = new char [ 64 ];
    bool validInput;

    SimpleTrip * newSTrip = new SimpleTrip( start, end, transport );
    ComposedTrip * newCTrip = new ComposedTrip();
    // Checks if the user input is valid (yes/no)
    do
    {
        cout << endl << "Do you wish to make this trip a composed trip? [yes/no]: ";
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
    if ( isComposed )
    {
        bool keepAdding;
        char * addNewStep = new char [ 64 ];
        newCTrip->AddSimpleTrip( newSTrip );

        do
        {
            strcpy( start,end );

            cout << "----- Enter the next city of arrival: ";
            cin >> end;

            cout << "----- Enter the kind of transport used: ";
            cin >> transport;

            newCTrip->AddSimpleTrip ( new SimpleTrip( start, end, transport ) );

            // Checks if the user input is valid [yes/no]
            do
            {
                cout << endl << "Do you wish to add another step to this trip? [yes/no]: ";
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

        tripList.AddTripSorted(newCTrip );

        delete [ ] addNewStep;
    }
    else
    {
        tripList.AddTripSorted(newSTrip );
        delete newCTrip;
    }

    // to free allocated memory in heap
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
        cout << endl << "Unfortunately, there are no trips yet..." << endl;
    }
    else
    {
        cout << endl << "Let's find you the best way to get to your destination!" << endl;

        char * start = new char [ 64 ];
        char * end = new char [ 64 ];
        cout << "----- Choose your departure city: ";
        cin >> start;
        cout << "----- Choose your destination city: " ;
        cin >> end;

        char * advanced = new char [ 64 ];
        bool validInput = false;
        do
        {
            cout << endl << "Do you wish to do an advanced search for this trip? [yes/no]: ";
            cin >> advanced;

            validInput = !strcmp( advanced, "yes" ) || !strcmp( advanced, "no" );

            if ( !validInput ) {
                cout << "Please enter a valid input [yes/no]..." << endl;
                //sleep(1);
            }
        }
        while ( !validInput );

        //tripList.FetchTrip( start, end );

        // if user wants a simple search only
        if ( !strcmp( advanced, "yes" ) )
        {
            cout << endl << "Here's what we can get you (or not): " << endl;
            bool found = tripList.FetchTripAdvanced( start, end );
            if ( !found )
            {
                cout << "Nothing, sorry..." << endl
                << "The trip from " << start << " to " << end << " does not exist..." << endl;
            }
            cout << endl;
        }
        else
        {
            tripList.FetchTrip( start, end );
        }

        // to free allocated memory in heap
        delete [ ] advanced;
        delete [ ] start;
        delete [ ] end;
    }
} //----- Fin de Fetch



// TODO : les composed trips se mettent au début de la liste alors qu'il faudrait les alphabétiser aussi
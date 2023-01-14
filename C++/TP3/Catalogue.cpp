/*************************************************************************
                           Catalogue  -  menu et interface utilisateur
                             -------------------
    début                : 03/01/2023
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
//#include <limits>
//#include <unistd.h>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Catalogue.h"

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
        cout << "\t4: import trips from a file" << endl;
        cout << "\t5: save trips to a file" << endl;
        cout << "\t6: close Gouggle Mapse" << endl;

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
                import(); // dans Catalogue_InputManager.cpp
                break;
            case 5:
                save(); // dans Catalogue_OutputManager.cpp
                break;
            case 6:
                goto end;
            default:
                cout << endl << "Incorrect choice, please enter a number between 1 and 6!" << endl;
                //sleep(1);
                continue; // go back to menu
        }
    }
    end:
    cout << endl << "See you soon on Gouggle Mapse :)" << endl;
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
} //----- Fin de display

void Catalogue::add ( )
// Algorithme :
// Création d'un SimpleTrip et d'un ComposedTrip dans tous les cas
// Si jamais l'utilisateur veut insérer un ComposedTrip, alors une suite de SimpleTrips
// sera ajoutée au ComposedTrip tant qu'il le décidera
{
    string start, end, transport;

    cout << endl << "Let's add a trip to our beautiful and (in)exhaustive catalogue!" << endl;
    cout << "Be a good samaritan and DO NOT INSERT SPACES!!! when you write your trip information (please...)" << endl;

    start = inputValidString( "city of departure" );
    end = inputValidString( "city of arrival" );
    transport = inputValidString(  "kind of transport used" );


    // We consider the eventuality of having a composed trip
    // These things are useful trust me.
    /*char * yesOrNo = new char [ 64 ];*/
    string yesOrNo;
    bool validInput;

    SimpleTrip * newSTrip = new SimpleTrip( start.c_str(), end.c_str(), transport.c_str() );
    ComposedTrip * newCTrip = new ComposedTrip();

    // Checks if the user input is valid (yes/no)
    do
    {
        cout << endl << "Do you wish to make this trip a composed trip? [yes/no]: ";
        cin >> yesOrNo;

        validInput = yesOrNo == "yes" || yesOrNo == "no";

        if ( !validInput )
        {
            cout << "Please enter a valid input [yes/no]..." << endl;
            //sleep(1);
        }
    }
    while ( !validInput );

    bool isComposed = ( yesOrNo == "yes" );
    if ( isComposed )
    {
        bool keepAdding;
        string addNewStep;

        newCTrip->AddSimpleTrip( newSTrip );

        do
        {
            start = end;

            end = inputValidString( "next city of arrival");
            transport = inputValidString( "kind of transport used");

            newCTrip->AddSimpleTrip ( new SimpleTrip( start.c_str(), end.c_str(), transport.c_str() ) );

            // Checks if the user input is valid [yes/no]
            do
            {
                cout << endl << "Do you wish to add another step to this trip? [yes/no]: ";
                cin >> addNewStep;

                validInput = addNewStep == "yes" || addNewStep == "no";

                if ( !validInput ) {
                    cout << "Please enter a valid input [yes/no]..." << endl;
                    //sleep(1);
                }
            }
            while ( !validInput );

            keepAdding = ( addNewStep == "yes" );
        }
        while ( keepAdding );

        tripList.AddTripSorted( newCTrip );

    }
    else
    {
        tripList.AddTripSorted( newSTrip );
        delete newCTrip;
    }

} //----- Fin de add

void Catalogue::fetch ( ) const
// Algorithme :
// Si la liste des Trips est non vide, appel de la méthode de la classe List
// pour rechercher le trajet
// Teste si la liste de trajets composant le catalogue est vide.
{
    if ( tripList.GetSize() == 0 ) {
        cout << endl << "Unfortunately, there are no trips yet..." << endl;
    }
    else
    {
        cout << endl << "Let's find you the best way to get to your destination!" << endl;

        string start, end;

        start = inputValidString( "city of departure" );
        end = inputValidString( "city of arrival" );

        string advanced;
        bool validInput;

        do
        {
            cout << endl << "Do you wish to do an advanced search for this trip? [yes/no]: ";
            cin >> advanced;

            validInput = advanced == "yes" || advanced == "no";

            if ( !validInput ) {
                cout << "Please enter a valid input [yes/no]..." << endl;
                //sleep(1);
            }
        }
        while ( !validInput );

        // if user wants the complete search
        if ( advanced == "yes" )
        {
            // allocated memory for an array of Trips to store the potential trips to fulfill request
            // The maximum size of this array will be the size of the trip List
            Trip * * tab = new Trip * [ this->tripList.GetSize() ];

            cout << endl << "Here's what we can get you (or not): " << endl;
            bool found = tripList.FetchTripAdvanced( start.c_str(), end.c_str(), tab );

            if ( !found )
            {
                cout << "Nothing, sorry..." << endl
                << "The trip from " << start << " to " << end << " does not exist..." << endl;
            }

            cout << endl;
        }
        else
        {
            tripList.FetchTrip( start.c_str(), end.c_str() );
        }

    }
} //----- Fin de fetch

/*************************************************************************
                           Catalogue  -  menu et interface utilisateur
                             -------------------
    début                : 22/11/2022
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
#include "ComposedTrip.h"
#include "CatalogueOutputManager.h"
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
                import();
                break;
            case 5:
                save();
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
} //----- Fin de add

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
        bool validInput;

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

        // if user wants the complete search
        if ( !strcmp( advanced, "yes" ) )
        {
            // allocated memory for an array of Trips to store the potential trips to fulfill request
            // The maximum size of this array will be the size of the trip List
            Trip * * tab = new Trip * [ this->tripList.GetSize() ];

            cout << endl << "Here's what we can get you (or not): " << endl;
            bool found = tripList.FetchTripAdvanced( start, end, tab );

            if ( !found )
            {
                cout << "Nothing, sorry..." << endl
                << "The trip from " << start << " to " << end << " does not exist..." << endl;
            }

            delete [ ] tab;
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
} //----- Fin de fetch

void Catalogue::import ( )
// Algorithme :
// Appending XXXXXX
{
    string nameFile;
    cout << "Enter the name of the file containing the trips to import: ";
    cin >> nameFile;
    //TODO : while pour checker que le nom du fichier est ok et que ce fichier existe

    int choice;
    for ( ; ; ) {
        cout << "Enter a NUMBER corresponding to one of the options listed below" << endl;
        cout << "\t1: import all the trips from the file into the Catalogue" << endl;
        cout << "\t2: import only the trips of a certain type from the file into the Catalogue" << endl;
        cout << "\t3: import only the trips corresponding to specific city(ies) conditions" << endl;
        cout << "\t4: import only an interval of trips from the file into the Catalogue" << endl;

        cin >> choice;

        switch ( choice ) {
            case 1:
                //TODO : import all
                break;
            case 2:
                //TODO : import type
                break;
            case 3:
                //TODO : import cities
                importCities();
                break;
            case 4:
                //TODO : import interval
                break;
            default:
                cout << endl << "Incorrect choice, please enter a number between 1 and 4!" << endl;
                //sleep(1);
                continue; // go back to options
        }
        break;
    }
} //----- Fin de import

void Catalogue::save ( ) const
// Algorithme :
// Appending XXXXXX
{
    string nameFile;
    cout << endl << "Enter the name of the file in which you want to save the trips." << endl;
    cout << "Know that the previous content of the file will be overwritten." << endl;
    cout << "Please, do NOT add the extension of the file, nor add '/' or any other special character!!" << endl;
    
    cin >> nameFile;
    //TODO : while pour checker que le nom du fichier est ok

    nameFile = "../C++/TP3/" + nameFile + ".txt";
    ofstream tripStream( nameFile.c_str() ); // without append

    //tripStream.open(namePath); // without append
    //tripStream.open(namePath, ios::app); // with append si on en a besoin un jour

    int choice;
    for ( ; ; ) {
        cout << endl << "Enter a NUMBER corresponding to one of the options listed below" << endl;
        cout << "\t1: save all the trips from the Catalogue into a file" << endl;
        cout << "\t2: save only the trips of a certain type from the Catalogue into a file" << endl;
        cout << "\t3: save only the trips corresponding to specific city(ies) conditions" << endl;
        cout << "\t4: save only an interval of trips from the Catalogue into a file" << endl;

        cin >> choice;

        switch ( choice ) {
            case 1:
                saveAll( tripStream );
                break;
            case 2:
                saveType( tripStream );
                break;
            case 3:
                //TODO : save cities advanced
                saveFromCities ( tripStream );
                break;
            case 4:
                saveInterval( tripStream );
                break;
            default:
                cout << endl << "Incorrect choice, please enter a number between 1 and 4!" << endl;
                //sleep(1);
                continue; // go back to options
        }
        break;
    }
    //tripStream.close();
} //----- Fin de save

void Catalogue::importCities ( )
// Algorithme :
// XXXX
{
    int choice;
    for ( ; ; ) {
        cout << endl << "Enter a NUMBER corresponding to one of the options listed below" << endl;
        cout << "\t1: import trips leaving from a certain city" << endl;
        cout << "\t2: import trips arriving at a certain city" << endl;
        cout << "\t3: import trips both leaving and arriving to the cities you want" << endl;

        cin >> choice;

        switch ( choice ) {
            case 1:
                //TODO : import trips a partir d'une ville de depart
                break;
            case 2:
                //TODO : import trips a partir d'une ville d'arrivee
                break;
            case 3:
                //TODO : import trips a partir des deux villes de depart & arrivee
                break;
            default:
                cout << endl << "Incorrect choice, please enter a number between 1 and 3!" << endl;
                //sleep(1);
                continue; // go back to options
        }
        break;
    }
} //----- Fin de importCities



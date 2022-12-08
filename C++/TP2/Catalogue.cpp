/*************************************************************************
                           Catalogue  -  repertoire de tous les trajets
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
#include <unistd.h>

//------------------------------------------------------ Include personnel
#include "ComposedTrip.h"
#include "Catalogue.h"
#include "SimpleTrip.h"

using namespace std;

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Catalogue::Launch ( )
// Algorithme :
// Menu de l'interface utilisateur sur la sortie standard, qui lui
// propose plusieurs options, tant qu'il ne choisit pas de quitter
{
    cout << "\nWelcome to the worst version of Gouggle Mapse :)" << endl;

    int choice;
    while (true)
    {
        cout << "\n-------------------- Menu. --------------------" << endl;
        cout << "Enter a NUMBER corresponding to one of the options listed below" << endl;
        cout << "\t1: display the catalogue of the available trips" << endl;
        cout << "\t2: add a trip" << endl;
        cout << "\t3: look for a trip" << endl;
        cout << "\t4: close Gouggle Mapse" << endl;

        // pour gerer les exceptions
        for( ; ; )
        {
            cin >> choice;
            if (!cin)
            {
                cout << "Wrong input, please enter a NUMBER" << endl;
                // pour clear l'erreur
                cin.clear();
                // pour enlever ce qui reste dans le buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            else break;
        }

        switch (choice)
        {
            case 1:
                Display();
                break;
            case 2:
                Add();
                break;
            case 3:
                Fetch();
                break;
            case 4:
                goto end;
            default:
                cout << "incorrect choice, please enter a number between 1 and 4" << endl;
                continue; // go back to menu
        }
    }
    end:
    cout << "See you soon on Gouggle Mapse :)" << endl;
} //----- Fin de Launch

//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue ( )
// Algorithme :
// Constructeur
{
#ifdef MAP
    cout << "Appel au constructeur de <Catalogue>" << endl;
#endif
} //----- Fin de Catalogue


Catalogue::~Catalogue ( )
// Algorithme :
// Destructeur
{
#ifdef MAP
    cout << "Appel au destructeur de <Catalogue>" << endl;
#endif
} //----- Fin de ~Catalogue


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void Catalogue::Display ( ) const
// Algorithme :
// Affichage du catalogue en appelant la fonction de la classe List
{
    if (tripList.GetSize() == 0)
    {
        cout << "Unfortunately, there are no trips yet..." << endl;
        sleep(1);
    } else {
        if (tripList.GetSize() > 1)
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


void Catalogue::Add()
{

    char* start = new char[64];
    char* end = new char[64];
    char* transport = new char[64];

    cout << "Let's add a trip to our beautiful and (in)exhaustive catalogue!" << endl;
    cout << "Be a good samaritan and DO NOT INSERT SPACES!!! when you write your trip information (please...)"<< endl;

    cout << "-----Enter the city of departure : ";
    cin >> start ;

    cout << "-----Enter the city of arrival : ";
    cin >> end;

    cout << "-----Enter the kind of transport used : ";
    cin >> transport;

    // We consider the eventuality of having a composed trip

    // These things are useful trust me.
    char* yesOrNo = new char[64];
    bool validInput;

    auto* newSTrip = new SimpleTrip(start , end , transport);
    auto *newCTrip = new ComposedTrip();
    // Checks if the user input is valid (yes/no)
    // TODO : REFACTOR THE CODE AND MAKE THIS A METHOD
    do
    {
        cout << "Do you wish to make this trip a composed trip ? [yes/no] :";
        cin >> yesOrNo;

        validInput = !strcmp(yesOrNo, "yes") || !strcmp(yesOrNo, "no");

        if(!validInput){
            cout << "Please enter a valid input..."<<endl;
            sleep(1);
        }

    }while (!validInput);


    bool isComposed = !strcmp(yesOrNo, "yes");


    if(isComposed)
    {
        bool keepAdding;
        char* addNewStep = new char[64];

        newCTrip->AddSimpleTrip(newSTrip);

        validInput = false;

        do{
            strcpy(start,end);

            cout << "-----Enter the new city of arrival :";
            cin >> end;

            cout << "-----Enter the kind of transport used :";
            cin >> transport;

            newCTrip->AddSimpleTrip(new SimpleTrip(start , end , transport));

            // Checks if the user input is valid [yes/no]
            // TODO : REFACTOR THE CODE AND MAKE THIS A METHOD
            do{
                cout << "Do you wish to add another step to this trip ? [yes/no] :";
                cin >> addNewStep;

                validInput = !strcmp(addNewStep, "yes") || !strcmp(addNewStep, "no");

                if(!validInput) {
                    cout << "Please enter a valid input [yes/no]..."<< endl;
                    sleep(1);
                }

            }while(!validInput);

            keepAdding = !strcmp(addNewStep, "yes");

        }while (keepAdding);

        tripList.AddTrip(newCTrip);
        //cout << "The new composed trip from " << newCTrip->GetStart() << " to " << newCTrip->GetEnd() << " has been successfully added !" << endl;

        delete[] addNewStep;
    }
    else
    {
        delete newCTrip;
        tripList.AddTrip(newSTrip);
    }


    delete [] start;
    delete [] end ;
    delete [] transport;
    delete [] yesOrNo;
}



void Catalogue::Fetch ( ) const
// Algorithme :
//
{
    if (tripList.GetSize() == 0) {
        cout << "Unfortunately, there are no trips yet..." << endl;

    }
    else
    {
        cout << "Let's find you the best way to get to your destination!" << endl;

        char* start = new char[64];
        char* end = new char[64];
        cout << "Choose your departure city : ";
        cin >> start;
        cout << "Please your destination city : " ;
        cin >> end;

        tripList.FetchTrip(start, end);

        delete[] start;
        delete[] end;
    }
} //----- Fin de Fetch
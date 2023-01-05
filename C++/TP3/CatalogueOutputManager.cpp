/*************************************************************************
                           CatalogueOutputManager  -  gestion des exports
                             -------------------
    début                : 04/01/2023
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Fichier source <CatalogueOutputManager> (fichier CatalogueOutputManager.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <fstream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Catalogue.h"

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void Catalogue::save ( ) const
// Algorithme :
// Appending XXXXXX
{
    ofstream tripStream = askNameFileSave();
    if ( !tripStream.good() )
    {
        cerr << "Error opening the file, going back to the menu..." << endl;
        return; // going back to menu
    }

    int choice;
    for ( ; ; )
    {
        cout << endl << "Enter a NUMBER corresponding to one of the options listed below" << endl;
        cout << "\t1: save all the trips from the Catalogue into a file" << endl;
        cout << "\t2: save only the trips of a certain type from the Catalogue into a file" << endl;
        cout << "\t3: save only the trips corresponding to specific city(ies) conditions" << endl;
        cout << "\t4: save only an interval of trips from the Catalogue into a file" << endl;

        cin >> choice;

        switch ( choice )
        {
            case 1:
                saveAll( tripStream );
                break;
            case 2:
                saveType( tripStream );
                break;
            case 3:
                saveCities ( tripStream );
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
    tripStream.close();
} //----- Fin de save

void Catalogue::saveAll ( ofstream & tripStream ) const
// Algorithme :
// XXX
{
    if ( tripList.GetFirst() == nullptr )
    {
        cout << endl << "Catalogue is empty... Nothing to add to the file :(";
        return;
    }

    int index = 1;
    Node * iter = tripList.GetFirst();

    while ( iter != nullptr ) // Parses through tripList
    {
        // Saves all the trips to file
        tripStream << index << ",";

        iter->GetTrip()->SaveTripToFile(tripStream);
        iter = iter->GetNext();

        index++;
    }
} //----- Fin de saveAll

void Catalogue::saveType ( ofstream & tripStream ) const
// Algorithme :
// XXX
{
    if ( tripList.GetFirst() == nullptr )
    {
        cout << endl << "Catalogue is empty... Nothing to add to the file :(";
        return;
    }

    int index = 1;
    Node * iter = tripList.GetFirst();

    int choice;
    for ( ; ; ) {
        cout << endl << "Enter the NUMBER corresponding to the desired type of trip:" << endl;
        cout << "\t1: save SIMPLE trips only" << endl;
        cout << "\t2: save COMPOSED trips only" << endl;

        cin >> choice;

        if ( choice != 1 && choice != 2 )
        {
            cout << endl << "Incorrect choice, please enter a number between 1 and 2!" << endl;
        }
        else break;
    }

    while ( iter != nullptr ) // Parses through tripList
    {
        // Saves all the trips of the chosen type to file
        if ( iter->GetTrip()->GetType() == choice )
        {
            tripStream << index << ",";
            iter->GetTrip()->SaveTripToFile(tripStream);
            index++;
        }
        iter = iter->GetNext();
    }
} //----- Fin de saveType

void Catalogue::saveCities ( ofstream & tripStream ) const
// Algorithme :
// XXXX
{
    if ( tripList.GetFirst() == nullptr )
    {
        cout << endl << "Catalogue is empty... Nothing to add to the file :(";
        return;
    }

    int index = 1;
    Node * iter = tripList.GetFirst();

    int choice;
    char * start = new char [ 64 ];
    char * end = new char [ 64 ];

    for ( ; ; ) {
        cout << "Enter a NUMBER corresponding to one of the options listed below" << endl;
        cout << "\t1: save trips leaving from a certain city" << endl;
        cout << "\t2: save trips arriving at a certain city" << endl;
        cout << "\t3: save trips both leaving and arriving to the cities you want" << endl;

        cin >> choice;

        switch ( choice ) {
            case 1:
                cout << endl << "Please enter the city of departure (no spaces!): " << endl;
                cin >> start;
                while ( iter != nullptr ) // Parses through tripList
                {
                    if ( iter->GetTrip()->GetStart() == start )
                    {
                        tripStream << index << ",";
                        iter->GetTrip()->SaveTripToFile( tripStream );
                        index++;
                    }
                    iter = iter->GetNext();
                }
                break;
            case 2:
                cout << endl << "Please enter the city of arrival (no spaces!): " << endl;
                cin >> end;
                while ( iter != nullptr ) // Parses through tripList
                {
                    if ( iter->GetTrip()->GetEnd() == end )
                    {
                        tripStream << index << ",";
                        iter->GetTrip()->SaveTripToFile( tripStream );
                        index++;
                    }
                    iter = iter->GetNext();
                }
                break;
            case 3:
                cout << endl << "Please enter the city of departure (no spaces!): " << endl;
                cin >> start;
                cout << endl << "Please enter the city of arrival (no spaces!): " << endl;
                cin >> end;

                while ( iter != nullptr ) // Parses through tripList
                {
                    if ( iter->GetTrip()->GetStart() == start && iter->GetTrip()->GetEnd() == end )
                    {
                        tripStream << index << ",";
                        iter->GetTrip()->SaveTripToFile( tripStream );
                        index++;
                    }
                    iter = iter->GetNext();
                }
                break;
            default:
                cout << endl << "Incorrect choice, please enter a number between 1 and 3!" << endl;
                //sleep(1);
                continue; // go back to options
        }
        break;
    }
    delete [ ] start;
    delete [ ] end;
} //----- Fin de saveFromCities

void Catalogue::saveInterval ( ofstream & tripStream ) const
// Algorithme :
// XXX
{
    if ( tripList.GetFirst() == nullptr )
    {
        cout << endl << "Catalogue is empty... Nothing to add to the file :(";
        return;
    }

    int start, end;

    for ( ; ; )
    {
        cout << endl << "From which trip NUMBER do you wish to save into the file?" << endl;
        cin >> start;

        if ( start > tripList.GetSize() )
        {
            cout << endl << "Please enter a number inferior or equal to " << tripList.GetSize() << endl;
        }
        else break;
    }

    for ( ; ; )
    {
        cout << "Until which trip NUMBER?" << endl;
        cin >> end;

        if ( end > tripList.GetSize() )
        {
            cout << endl << "Please enter a number inferior or equal to " << tripList.GetSize() << endl;
        }
        else break;
    }

    int index = 1, currPos = 1;
    Node * iter = tripList.GetFirst();

    while ( iter != nullptr ) // Parses through tripList
    {
        // Saves all the trips in the desired interval
        if ( currPos >= start && currPos <= end )
        {
            tripStream << index << ",";
            iter->GetTrip()->SaveTripToFile(tripStream);
            index++;
        }
        iter = iter->GetNext();
        currPos++;
    }
} //----- Fin de saveInterval

ofstream Catalogue::askNameFileSave ( ) const
{
    string nameFile;
    ofstream tripStream;

    bool fileOk = false; // to check if name of file respects the conditions and already exists

    while ( !fileOk )
    {
        cout << endl << "Enter the name of the file in which you want to save the trips." << endl;
        cout << "Names such as '.' or '..' are NOT valid!" << endl;
        cout << "Please, do NOT add the extension of the file, nor add '/' or any other special character!!" << endl;

        cin >> nameFile;

        if ( nameFile.empty() )
        {
            cerr << "No input, going back to the menu..." << endl;
            return tripStream;
        }
        if ( nameFile == "." || nameFile == ".." )
        {
            cout << "This name of file is NOT valid..." << endl;
            continue;
        }

        nameFile = "../C++/TP3/" + nameFile + ".txt";
        tripStream.open( nameFile.c_str() );

        bool appendOk = false;
        while ( !appendOk )
        {
            // if file already exists, ask the user if they want to append to it, overwrite it, or cancel
            if ( tripStream.good() )
            {
                int mode;
                for ( ; ; )
                {
                    cout << endl << "File " << nameFile << " already exists." << endl;
                    cout << "Enter the number corresponding to the option about the management of the file:" << endl;
                    cout << "\t1. Append to it" << endl;
                    cout << "\t2. Overwrite it" << endl;
                    cout << "\t3. Cancel the operation and choose another file (it can be non-existent)" << endl;

                    cin >> mode;

                    switch ( mode )
                    {
                        case 1:
                            tripStream.open( nameFile, ios_base::app ); // appending
                            appendOk = true;
                            fileOk = true; // the file is now okay
                            break;
                        case 2:
                            tripStream.open( nameFile ); // default mode, overwriting
                            appendOk = true;
                            fileOk = true; // the file is now okay
                            break;
                        case 3:
                            cout << "Operation cancelled, choose another file..." << endl;
                            // the file is still not okay so goes through the first while loop once again
                            break;
                        default:
                            cout << endl << "Incorrect choice, please enter a number between 1 and 4!" << endl;
                            //sleep(1);
                            continue; // go back to options
                    }
                    break; // getting out of the for loop if went through case 1 2 or 3
                }
            }
            else // else the file does not exist, hence the mode is the default one
            {
                fileOk = true;
            }
        }
    }

    cout << endl << "Saving trips into " << nameFile << endl;
    return tripStream;
} //----- Fin de askNameFileSave
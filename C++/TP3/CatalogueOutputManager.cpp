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
#include <iostream>
#include <fstream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Catalogue.h"
#include "CatalogueUtils.h"

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void Catalogue::save ( )
// Algorithme :
// Appending XXXXXX
{
    if ( tripList.GetFirst() == nullptr )
    {
        cout << endl << "Catalogue is empty... Nothing to add to the file :(" << endl;
        return;
    }

    ofstream tripStream( askNameFileSave() );

    if ( !tripStream.good() )
    {
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
        cout << "\t5: go back to the main menu" << endl;

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
            case 5:
                break;
            default:
                cout << endl << "Incorrect choice, please enter a number between 1 and 5!" << endl;
                //sleep(1);
                continue; // go back to options
        }
        break;
    }
    tripStream.close();
} //----- Fin de save

void Catalogue::saveAll ( ofstream & tripStream )
// Algorithme :
// XXX
{
    Node * iter = tripList.GetFirst();

    while ( iter != nullptr ) // Parses through tripList
    {
        // Saves all the trips to file
        tripStream << lastIndex << ",";

        iter->GetTrip()->SaveTripToFile(tripStream);
        if ( iter->GetNext() != nullptr ) // if there's a trip after to add, then add a new line
        {
            tripStream << endl;
        }
        iter = iter->GetNext();

        lastIndex++;
    }
} //----- Fin de saveAll

void Catalogue::saveType ( ofstream & tripStream )
// Algorithme :
// XXX
{
    Node * iter = tripList.GetFirst();

    int choice;
    for ( ; ; )
    {
        cout << endl << "Enter the NUMBER corresponding to the desired type of trip:" << endl;
        cout << "\t1: save SIMPLE trips only" << endl;
        cout << "\t2: save COMPOSED trips only" << endl;
        cout << "\t3: go back to save menu" << endl;

        cin >> choice;

        if ( choice != 1 && choice != 2 && choice != 3 )
        {
            cout << endl << "Incorrect choice, please enter a number between 1 and 3!" << endl;
        }
        else break;
    }

    if ( choice == 3 )
    {
        cout << endl << "Going back to save menu..." << endl;
        return; // going back to save menu
    }

    while ( iter != nullptr ) // Parses through tripList
    {
        // Saves all the trips of the chosen type to file
        if ( iter->GetTrip()->GetType() == choice )
        {
            tripStream << lastIndex << ",";
            iter->GetTrip()->SaveTripToFile(tripStream);
            if ( iter->GetNext() != nullptr ) // if there's a trip after to add, then add a new line
            {
                tripStream << endl;
            }
            lastIndex++;
        }
        iter = iter->GetNext();
    }
} //----- Fin de saveType

void Catalogue::saveCities ( ofstream & tripStream )
// Algorithme :
// XXXX
{
    int choice;

    for ( ; ; )
    {
        cout << "Enter a NUMBER corresponding to one of the options listed below" << endl;
        cout << "\t1: save trips leaving from a certain city" << endl;
        cout << "\t2: save trips arriving at a certain city" << endl;
        cout << "\t3: save trips both leaving and arriving to the cities you want" << endl;
        cout << "\t4: go back to save menu" << endl;

        cin >> choice;

        switch ( choice ) {
            case 1:
                saveTripsFromDeparture( tripStream );
                break;
            case 2:
                saveTripsToArrival( tripStream );
                break;
            case 3:
                saveTripsFromTo( tripStream );
                break;
            case 4:
                cout << endl << "Going back to save menu..." << endl;
                return;  // going back to save menu
            default:
                cout << endl << "Incorrect choice, please enter a number between 1 and 4!" << endl;
                //sleep(1);
                continue; // go back to options
        }
        break;
    }

} //----- Fin de saveFromCities

void Catalogue::saveTripsFromDeparture ( std::ofstream & tripStream )
{
    int count = 0;
    string start;

    cout << endl << "Please enter the city of departure (no spaces!): " << endl;
    cin >> start;

    Node * iter = tripList.GetFirst();

    while ( iter != nullptr ) // Parses through tripList
    {
        if ( iter->GetTrip()->GetStart() == start )
        {
            count++;
            tripStream << lastIndex << ",";
            iter->GetTrip()->SaveTripToFile( tripStream );
            if ( iter->GetNext() != nullptr ) // if there's a trip after to add, then add a new line
            {
                tripStream << endl;
            }
            lastIndex++;
        }
        iter = iter->GetNext();
    }
    if ( count == 0 ){
        cout << "Sorry, no trips starting from " << start << " are available..." << endl;
    }
    else
    {
        cout << count << " trips starting from " << start << " have been found!" << endl;
    }
} //----- Fin de saveTripsFromDeparture

void Catalogue::saveTripsToArrival ( std::ofstream & tripStream )
{
    int count = 0;
    string end;

    cout << endl << "Please enter the city of arrival (no spaces!): " << endl;
    cin >> end;

    Node * iter = tripList.GetFirst();

    while ( iter != nullptr ) // Parses through tripList
    {
        if ( iter->GetTrip()->GetEnd() == end )
        {
            count++;
            tripStream << lastIndex << ",";
            iter->GetTrip()->SaveTripToFile( tripStream );
            if ( iter->GetNext() != nullptr ) // if there's a trip after to add, then add a new line
            {
                tripStream << endl;
            }
            lastIndex++;
        }
        iter = iter->GetNext();
    }
    if ( count == 0 )
    {
        cout << "Sorry, no trips going to " << end << " are available..." << endl;
    }
    else
    {
        cout << count << " trips going to " << end << " have been found !" << endl;
    }
} //----- Fin de saveTripsToArrival

void Catalogue::saveTripsFromTo ( std::ofstream & tripStream )
{
    int count = 0;
    string start, end;

    cout << endl << "Please enter the city of departure (no spaces!): " << endl;
    cin >> start;
    cout << endl << "Please enter the city of arrival (no spaces!): " << endl;
    cin >> end;

    Node * iter = tripList.GetFirst();

    while ( iter != nullptr ) // Parses through tripList
    {
        if ( iter->GetTrip()->GetStart() == start && iter->GetTrip()->GetEnd() == end )
        {
            count++;
            tripStream << lastIndex << ",";
            iter->GetTrip()->SaveTripToFile( tripStream );
            if ( iter->GetNext() != nullptr ) // if there's a trip after to add, then add a new line
            {
                tripStream << endl;
            }
            lastIndex++;
        }
        iter = iter->GetNext();
    }
    if ( count == 0 )
    {
        cout << "Sorry, no trips starting from " << start << " and going to " << end
             << " are available..." << endl;
    }
    else
    {
        cout << count << " trips starting from " << start << " and going to " << end
             << " have been found !" << endl;
    }
} //----- Fin de saveTripsFromTo

void Catalogue::saveInterval ( ofstream & tripStream )
// Algorithme :
// XXX
{
    int start, end;
    int size = tripList.GetSize();

    for ( ; ; )
    {
        cout << endl << "From which trip NUMBER do you wish to save into the file ?" << endl;
        cout << "Enter 0 to go back to save menu" << endl;
        cin >> start;

        if ( start == 0 )
        {
            cout << endl << "Going back to save menu..." << endl;
            return;  // going back to save menu
        }

        if ( start > size )
        {
            cout << endl << "Starting index is bigger than the number of trips (" << size << ")..." << endl;
            cout << "Please enter a number less than or equal to " << size << endl;
        }
        else break;
    }

    for ( ; ; )
    {
        cout << endl << "To which trip NUMBER do you wish to finish the saving?" << endl;
        cin >> end;

        if ( end < start )
        {
            cout << endl << "Ending index is less than starting index (" << start << ")..." << endl;
            cout << "Please enter a number less than or equal to " << start << endl;
            continue;
        }

        if ( end > size )
        {
            cout << endl << "Ending index is bigger than the number of trips (" << size << ")..." << endl;
            cout << "Please enter a number less than or equal to " << size << endl;
        }
        else break;
    }

    int currPos = 1;

    Node * iter = tripList.GetFirst();

    while ( iter != nullptr ) // Parses through tripList
    {
        // Saves all the trips in the desired interval
        if ( currPos >= start && currPos <= end )
        {
            tripStream << lastIndex << ",";
            iter->GetTrip()->SaveTripToFile(tripStream);
            if ( iter->GetNext() != nullptr ) // if there's a trip after to add, then add a new line
            {
                tripStream << endl;
            }
            lastIndex++;
        }
        iter = iter->GetNext();
        currPos++;
    }
} //----- Fin de saveInterval

ofstream Catalogue::askNameFileSave ( )
{
    string nameFile;
    ofstream tripStream;
    ifstream tempStream;

    bool fileOk = false; // to check if name of file respects the conditions and already exists

    while ( !fileOk )
    {
        cout << endl << "Enter the name of the file in which you want to save the trips (can be non-existent)." << endl;
        cout << "Names containing '.' or '..' are NOT valid!" << endl;
        cout << "Please, do NOT add the extension of the file, nor add '/' or any other special character!!" << endl;

        //nameFile = ""; // reset the file name
        cin >> nameFile;

        if (nameFile.find('.') != string::npos) // if there's at least one '.' in the input name
        {
            cout << endl << "This name of file is NOT valid..." << endl;
            continue;
        }

        nameFile.insert( 0, "../C++/TP3/" );
        nameFile.append( ".csv" );

        openingMode( tempStream, tripStream, nameFile, fileOk );
    }

    if ( !tripStream.good() )
    {
        cerr << "Error opening the file, going back to the menu..." << endl;
    }
    else
    {
        cout << endl << "Saving files into file " << nameFile << endl;
    }
    return tripStream;
} //----- Fin de askNameFileSave

void Catalogue::appendOutput ( ifstream & tempStream, ofstream & tripStream, string & nameFile )
{
    lastIndex = findNextTripIndex( tempStream );
    tempStream.close();

    tripStream.open( nameFile.c_str(), ios_base::app ); // appending

    // a new line after the last trip must be added if the file is not empty
    tripStream.seekp( 0, ios_base::end );
    // goes to end of file
    long size;
    size = tripStream.tellp(); // get current position = size of file

    if ( size > 0 ) // file is not empty
    {
        tripStream << endl;
    }
    ///POUR CSV
    else // add the first line in the .csv file
    {
        tripStream << "index,type,departure,arrival,transportation" << endl;
    }
}

void Catalogue::openingMode ( ifstream & tempStream, ofstream & tripStream, string & nameFile, bool & fileOk )
{
    bool appendOk = false;

    tempStream.open( nameFile.c_str() ); // input stream to check if file already exists

    // this loop is to check with the user the opening mode of the stream
    while ( !appendOk )
    {
        // if file already exists, ask the user if they want to append to it, overwrite it, or cancel
        if ( tempStream.good() )
        {
            int mode;
            for ( ; ; )
            {
                cout << endl << "File " << nameFile << " already exists." << endl;
                cout << endl << "Enter the number corresponding to the option about the management of the file:" << endl;
                cout << "\t1. Append to it" << endl;
                cout << "\t2. Overwrite it" << endl;
                cout << "\t3. Cancel the operation and choose another file (it can be a non-existent one)" << endl;

                cin >> mode;

                switch ( mode )
                {
                    case 1:
                        appendOutput( tempStream, tripStream, nameFile );

                        appendOk = true;
                        fileOk = true; // the file is now okay
                        break;
                    case 2:
                        tempStream.close();

                        tripStream.open( nameFile.c_str() ); // default mode, overwriting
                        lastIndex = 1;

                        // first line in .csv
                        tripStream << "index,type,departure,arrival,transportation" << endl;

                        appendOk = true;
                        fileOk = true; // the file is now okay
                        break;
                    case 3:
                        tempStream.close();
                        cout << "Operation cancelled, choose another file..." << endl;
                        appendOk = true;
                        // the file is still not okay so goes through the first while loop once again
                        break;
                    default:
                        cout << endl << "Incorrect choice, please enter a number between 1 and 3!" << endl;
                        //sleep(1);
                        continue; // go back to options
                }
                break; // getting out of the for loop if went through case 1 2 or 3
            }
        }
        else // else the file does not exist, hence the mode is the default one
        {
            tempStream.close();

            tripStream.open( nameFile.c_str() );
            lastIndex = 1;

            // first line in .csv
            tripStream << "index,type,departure,arrival,transportation" << endl;

            appendOk = true;
            fileOk = true;
        }
    }
}
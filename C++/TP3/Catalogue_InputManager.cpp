/*************************************************************************
                           Catalogue_InputManager  -  gestion des imports
                             -------------------
    début                : 04/01/2023
    copyright            : (C) 2022 par Nour ELJADIRI, Marie ROULIER
    e-mail               : mohamed-nour.eljadiri@insa-lyon.fr
                           marie.roulier@insa-lyon.fr
*************************************************************************/

//---------- Fichier source <Catalogue_InputManager> (fichier Catalogue_InputManager.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
//#include <limits>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Catalogue.h"
#include "SimpleTrip.h"
#include "ComposedTrip.h"
#include "CatalogueUtils.h"

//------------------------------------------------------------------ PRIVE

//--------------------------------------------------------- Méthodes amies
void importTrip ( Catalogue * c , ifstream & tripStream , string * data , string & trip , int tripIndex )
// Algorithme :
// Appelle la méthode adaptée au type du trajet à importer en fonction de son type
// Le type du trajet est transmis grace au tableau data.
{
    if ( data[1] == "S" )
    {
        importSimpleTrip( c, tripStream, data, trip );
    }
    else if ( data[1] == "C")
    {
        importComposedTrip( c, tripStream, data, trip, tripIndex );
    }
    else
    {
        cout << "Trip type is not valid. Aborting..." << endl;
        delete [ ] data;
        return;
    }
} //----- Fin de importTrip

void importComposedTrip ( Catalogue * c, ifstream & tripStream, string * data,
                          string & trip, int tripIndex )
// Algorithme :
// La méthode permet d'importer un trajet composé à partir de sa version texte
// Tant qu'on n'arrive pas à une ligne vide, et que les indices des étapes
// du composedTrip sont logiques (=0), le trajet composé se voit rajouter
// une nouvelle étape.
// Si le trajet n'est pas valide, ou que le format texte n'est pas respecté,
// le trajet n'est pas importé
// string * data correspond à un tableau qui contient les informations relatives
// au trajet qu'on est entrain de traiter
{
    ComposedTrip * composedTrip = new ComposedTrip();

    // We delete the first line that has been used to determine the type of the trip
    delete [ ] data;

    // While there is no empty string
    while ( getline( tripStream, trip ) && !trip.empty() )
    {
        data = split( trip, ',' );

        // If one of the steps has an index different than 0, break out of the loop
        if ( data[0] != "0" )
        {
            cerr << "Error in composed trip of index " << tripIndex << "." << endl;
            cerr << "Step " << data[2] << " to " << data[3] << " has a non zero index." << endl;
            cerr << "Aborting..." << endl;

            delete [ ] data;
            delete composedTrip;
            return;
        }

        composedTrip->AddSimpleTrip( new SimpleTrip( data[2].c_str(),
                                                     data[3].c_str(), data[4].c_str() ) );

        delete [ ] data;
    }

    // If the composed trip is valid
    if ( composedTrip->IsValid() )
    {
        // The composed trip gets added in a sorted way in our catalogue
        c->tripList.AddTripSorted( composedTrip );
    }
    else
    {
        cout << "Composed trip number " << tripIndex << " is not valid... Not saving it..." << endl;
        delete composedTrip;
    }
} //----- Fin de importComposedTrip

void importSimpleTrip ( Catalogue * c, ifstream & tripStream, string * data, string & trip )
// La méthode permet d'importer un trajet simple à partir de sa version texte
// string * data correspond à un tableau qui contient les informations relatives
// au trajet qu'on est entrain de traiter
{
    c->tripList.AddTripSorted( new SimpleTrip( data[2].c_str(),
                                               data[3].c_str(), data[4].c_str() ) );

    delete [ ] data;
} //----- Fin de importSimpleTrip

//----------------------------------------------------- Méthodes protégées
void Catalogue::import ( )
// Algorithme :
// Appelle la méthode askNameFileImport() pour connaitre le nom du fichier
// Demande une entrée de l'utilisateur
// Appelle la méthode d'import adaptée en fonction de l'entrée de l'utilisateur
{
    ifstream tripStream( askNameFileImport() );
    if ( !tripStream.is_open() )
    {
        return; // going back to menu
    }

    int choice;
    for ( ; ; )
    {
        cout << endl << "Enter a NUMBER corresponding to one of the options listed below" << endl;
        cout << "\t1: import all the trips from the file into the Catalogue" << endl;
        cout << "\t2: import only the trips of a certain type from the file into the Catalogue" << endl;
        cout << "\t3: import only the trips corresponding to specific city(ies) conditions" << endl;
        cout << "\t4: import only an interval of trips from the file into the Catalogue" << endl;
        cout << "\t5: go back to the main menu" << endl;

        cin >> choice;

        switch ( choice )
        {
            case 1:
                importAll( tripStream );
                break;
            case 2:
                importType( tripStream );
                break;
            case 3:
                importCities ( tripStream );
                break;
            case 4:
                importInterval ( tripStream );
                break;
            case 5:
                cout << "Going back to main menu..." << endl;
                break;
            default:
                cout << endl << "Incorrect choice, please enter a number between 1 and 5!" << endl;
                //sleep(1);
                continue; // go back to options
        }
        break;
    }
    tripStream.close();
} //----- Fin de import

void Catalogue::importAll ( ifstream & tripStream )
// Algorithme :
// Parcours du fichier csv
// A chaque ligne, on sépare la chaine de caractère contenue dans la ligne
// en utilisant ',' comme séparateur, grâce à la méthode split( string, char )
// Puis on extrait les données qui y sont présentes, et en fonction
// du type de trajet, on appelle la méthode adaptée.
// La méthode effectue ces actions pour tous les trajets contenus dans le fichier.
{
    string trip;
    string * data;

    // While the stream does not return an error
    while ( tripStream.good() )
    {
        // Read a line from the stream
        getline( tripStream, trip );

        // If the line is empty, continue
        if ( trip.empty() )
        {
            continue;
        }

        // Else we get the line, and split it with the ',' delimiter and store it in a string array
        data = split( trip, ',' );

        // Store the lastIndex of the trip (useful)
        int tripIndex = stoi( data[0] );

        importTrip( this, tripStream, data, trip, tripIndex );
    }
    tripStream.clear();
    tripStream.seekg(0);
} //----- Fin de importAll

void Catalogue::importType ( ifstream & tripStream )
// Algorithme :
// L'utilisateur choisit le type de trajets à importer à partir du fichier
// Pour chaque ligne parcourue dans le fichier csv, on extrait l'information du type de trajet
// grâce à la méthode split( string, char ).
// Si le type est le bon, on appelle la méthode adaptée pour importer les trajets en question
// dans le Catalogue.
{
    const int CANCEL = 3;
    cout << "Please enter the type of trips you want to import from the file : " << endl;
    cout << "\t1: import SIMPLE trips only" << endl;
    cout << "\t2: import COMPOSED trips only" << endl;
    cout << "\t3: go back to import menu" << endl;

    int type;
    do
    {
        cin >> type;

        /// Commented code checks if the input is numeric (not asked in the specifications)
      /*if(!cin)
        {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Input must be purely numeric, please try again..."<<endl;
            continue;
        }*/

        if ( ( type != CANCEL && type != SIMPLE_TRIP && type != COMPOSED_TRIP ) )
        {
            cout << endl << "Incorrect choice, please enter a number between 1 and 2!" << endl;
        }

    }
    while ( !cin || (type != CANCEL && type != SIMPLE_TRIP && type != COMPOSED_TRIP ) );

    if ( type == SIMPLE_TRIP )
    {
        importAllSimpleTrips( tripStream );
    }
    else if ( type == COMPOSED_TRIP )
    {
        importAllComposedTrips( tripStream );
    }
    else if ( type == CANCEL )
    {
        cout << endl << "Going back to import menu..." << endl;
        return;
    }
} //----- Fin de importType

void Catalogue::importAllSimpleTrips ( ifstream & tripStream )
// Algorithme :
// Parcours de tout le fichier.
// Chaque ligne est traitée à l'aide de la méthode split.
// Si le trajet s'avère être simple, et qu'il ne s'agit pas d'une étape d'un trajet composé,
// on appelle la méthode importSimpleTrip().
{
    string trip;

    while ( tripStream.good() )
    {
        getline( tripStream, trip ) ;

        if ( trip.empty() )
        {
            continue;
        }

        string * data = split( trip, ',' );

        if ( data[1] == "S" && data[0] != "0" ) // si trajet simple et non une etape
        {
            importSimpleTrip( this, tripStream, data, trip );
        }
        else
        {
            delete [ ] data;
        }
    }
    tripStream.clear();
    tripStream.seekg(0);
} //----- Fin de importAllSimpleTrips

void Catalogue::importAllComposedTrips ( ifstream & tripStream )
// Algorithme :
// Parcours de tout le fichier
// Pour chaque ligne parcourue, on extrait les informations
// relatives au trajet renseigné dans cette ligne et on les
// stock dans un tableau de string grace à la méthode split.
// Si le trajet s'avère être un trajet composé, on appelle la méthode
// importComposedTrip()
{
    string trip;
    int tripIndex;
    string * data;

    while ( tripStream.good() )
    {
        getline( tripStream, trip );

        if ( trip.empty() )
        {
            continue;
        }

        data = split( trip, ',' );

        tripIndex = stoi( data[0] );
        if ( data[1] == "C" )
        {
            importComposedTrip( this, tripStream, data, trip, tripIndex );
        }
        else
        {
            delete [ ] data;
        }
    }
    tripStream.clear();
    tripStream.seekg(0);
} //----- Fin de importAllComposedTrips

void Catalogue::importCities ( ifstream & tripStream )
// Algorithme :
// La méthode permet d'importer des trajets en fonction d'information relatives
// aux villes qui les constituent.
// L'utilisateur a le choix entre importer les trajets qui partent d'une ville connue,
// qui finissent dans une ville connue, ou qui vérifient les deux conditions en même temps.
// En fonction du choix de l'utilisateur, la méthode adaptée sera appelée.
{
    int choice;

    string start , end;

    for ( ; ; )
    {
        cout << endl << "Enter a NUMBER corresponding to one of the options listed below" << endl;
        cout << "\t1: import trips leaving from a certain city" << endl;
        cout << "\t2: import trips arriving at a certain city" << endl;
        cout << "\t3: import trips both leaving and arriving to the cities you want" << endl;
        cout << "\t4: go back to import menu" << endl;

        cin >> choice;

        switch ( choice )
        {
            case 1:
                importTripsFromDeparture( tripStream );
                break;
            case 2:
                importTripsToArrival( tripStream );
                break;
            case 3:
                importTripsFromTo( tripStream );
                break;
            case 4:
                cout << endl << "Going back to import menu..." << endl;
                return;
            default:
                cout << endl << "Incorrect choice, please enter a number between 1 and 4!" << endl;
                //sleep(1);
                continue; // go back to options
        }
        break;
    }
} //----- Fin de importCities

void Catalogue::importTripsFromDeparture ( ifstream & tripStream )
// Algorithme :
// Demande à l'utilisateur d'entrer la ville de départ
// des trajets qu'il souhaite importer.
// Parcours de tout le fichier ligne par ligne,
// et extraction des informations de chaque ligne grâce à la
// méthode split() .
// Si la ville de départ correspond bien, on importe le trajet
// quelque soit son type.
{
    string trip;
    string departureCity;

    cout << "Please enter the city of departure (no spaces!): " << endl;
    cin >> departureCity;

    int count = 0;
    int tripIndex;

    while ( tripStream.good() )
    {
        getline( tripStream,trip );
        if ( trip.empty() )
        {
            continue;
        }

        string * data = split( trip,',' );

        if ( data[2] == departureCity && data[0] != "0" )
        {
            count++;
            tripIndex = stoi( data[0] );
            importTrip( this, tripStream, data, trip, tripIndex );
        }
    }

    if ( count == 0 )
    {
        cout << "Sorry, no trips starting from " << departureCity << " are available..." << endl;
    }
    else
    {
        cout << count << " trips starting from " << departureCity << " have been found!" << endl;
    }
} //----- Fin de importTripsFromDeparture

void Catalogue::importTripsToArrival ( ifstream & tripStream )
// Algorithme :
// Demande à l'utilisateur d'entrer la ville d'arrivée
// des trajets qu'il souhaite importer.
// Parcours de tout le fichier ligne par ligne,
// et extraction des informations de chaque ligne grâce à la
// méthode split() .
// Si la ville d'arrivée correspond bien, on importe le trajet
// quelque soit son type.
{
    int count = 0;
    int tripIndex;

    string trip;
    string arrivalCity;

    cout << "Please enter the city of arrival (no spaces!): " << endl;
    cin >> arrivalCity;

    while ( tripStream.good() )
    {
        getline(tripStream,trip);
        if ( trip.empty() )
        {
            continue;
        }

        string * data = split( trip,',' );

        if ( data[3] == arrivalCity && data[0] != "0" )
        {
            count++;
            tripIndex = stoi( data[0] );
            importTrip( this, tripStream, data, trip, tripIndex );
        }
    }

    if ( count == 0 )
    {
        cout << "Sorry, no trips going to " << arrivalCity << " are available..." << endl;
    }
    else
    {
        cout << count << " trips going to " << arrivalCity << " have been found !" << endl;
    }
} //----- Fin de importTripsToArrival

void Catalogue::importTripsFromTo ( ifstream & tripStream )
// Algorithme :
// Demande à l'utilisateur d'entrer les villes de départ et d'arrivée
// des trajets qu'il souhaite importer.
// Parcours de tout le fichier ligne par ligne,
// et extraction des informations de chaque ligne grâce à la
// méthode split() .
// Si les informations données correspondent bien, on importe le trajet
// quelque soit son type.
{
    int count = 0;
    int tripIndex;

    string trip;
    string departureCity , arrivalCity;

    cout << "Please enter the city of departure (no spaces!): " << endl;
    cin >> departureCity;
    cout << "Please enter the city of arrival (no spaces!): " << endl;
    cin >> arrivalCity;

    while ( tripStream.good() )
    {
        getline( tripStream, trip );

        if ( trip.empty() )
        {
            continue;
        }

        string * data = split( trip, ',' );

        if ( data[0] != "0" && data[2] == departureCity && data[3] == arrivalCity )
        {
            count++;
            tripIndex = stoi( data[0] );
            importTrip( this, tripStream, data, trip, tripIndex );
        }
    }

    if ( count == 0 )
    {
        cout << "Sorry, no trips starting from " << departureCity << " and going to " << arrivalCity
             << " are available..." << endl;
    }
    else
    {
        cout << count << " trips starting from " << departureCity << " and going to " << arrivalCity
             << " have been found !" << endl;
    }
} //----- Fin de importTripsFromTo

void Catalogue::importInterval ( ifstream & tripStream )
// Algorithme :
// L'utilisateur entre l'index de début de son import et l'index de fin.
// Parcours du fichier jusqu'à trouver l'index de début
// puis on importe (fin - début + 1) trajets dans le catalogue.
// La méthode vérifie si l'entrée utilisateur est valide (fin >= début et si début <= nb
// de trajets dans le fichier)
{
    int start, end, interval, tripIndex;

    int lastTripIndex = findNextTripIndex( tripStream ) - 1;
    // -1 because the method returns the index of next trip ; so last trip index + 1
    cout << lastTripIndex << endl;
    string trip, * data;

    for ( ; ; )
    {
        cout << endl << "From which trip NUMBER do you wish to start the import? " << endl;
        cout << "Enter 0 to go back to import menu" << endl;
        cin >> start;
        if ( start == 0 )
        {
            cout << endl << "Going back to import menu..." << endl;
            return; // going back to import menu
        }

        if ( start > lastTripIndex )
        {
            cout << endl << "Starting index is bigger than the index of the last trip in your file (" << lastTripIndex << ")..." << endl;
            cout << "Please enter a number less than or equal to " << lastTripIndex << endl;
        }
        else break;
    }
    tripIndex = start;

    for ( ; ; )
    {
        cout << endl << "To which trip NUMBER do you wish to finish the import ? " << endl;
        cin >> end ;
        if ( end < start )
        {
            cout << endl << "Ending index is less than starting index (" << start << ")..." << endl;
            cout << "Please enter a number less than or equal to " << start << endl;
            continue;
        }

        if ( end > lastTripIndex )
        {
            cout << endl << "Ending index is bigger than the index of the last trip in your file (" << lastTripIndex << ")..." << endl;
            cout << "Please enter a number less than or equal to " << lastTripIndex << endl;
        }
        else break;
    }

    interval = end - start;

    while ( getline( tripStream, trip ) )
    {
        if ( trip.empty() )
        {
            continue;
        }

        data = split( trip, ',' );

        if ( stoi(data[0] ) == start )
        {
            //cout << "importing " << trip << endl;
            importTrip( this, tripStream, data, trip, tripIndex );
            interval--;
            break;
        }
    }

    while ( interval >= 0 )
    {
        getline( tripStream , trip );

        if ( trip.empty() )
        {
            continue;
        }

        data = split( trip, ',');
        tripIndex = stoi( data[0] );
        importTrip( this, tripStream, data, trip, tripIndex );
        interval--;
    }
} //----- Fin de importInterval

ifstream Catalogue::askNameFileImport ( ) const
// Algorithme :
// Demande à l'utilisateur d'entrer le nom (sans l'extension) d'un fichier EXISTANT et valide
// c'est-à-dire non-vide et non-corrompu
// tant que l'utilisateur ne respecte pas les contraintes, demande à nouveau le nom de fichier
{
    string nameFile;
    ifstream tripStream;

    bool fileOk = false; // to check if name of file respects the conditions and exists

    while ( !fileOk )
    {
        cout << endl << "Enter the name of the file containing the trips to import (file must exist)." << endl;
        cout << "Names containing '.' or '..' are NOT valid!" << endl;
        cout << "Please, do NOT add the extension of the file, nor add spaces or any special character!!" << endl;
        cout << "Enter '...' to cancel and go back to the import menu" << endl;

        cin >> nameFile;

        if ( nameFile == "..." )
        {
            cout << endl << "Going back to main menu..." << endl;
            return tripStream;
        }

        if ( nameFile.find('.') != string::npos ) // if there's at least one '.' in the input name
        {
            cout << endl << "This name of file is NOT valid..." << endl;
            continue;
        }

        nameFile.append( ".csv" );

        tripStream.open( nameFile.c_str() );

        if ( !tripStream.good() )
        {
            cout << endl << "File " << nameFile << " doesn't exist." << endl;
            cout << "Please choose a file already existing." << endl;
            continue;
        }

        // to check if file is empty
        tripStream.seekg( 0, ios_base::end );
        // goes to end of file
        long size;
        size = tripStream.tellg(); // get current position = size of file

        if ( size == 0 ) // file is empty
        {
            cout << endl << "File " << nameFile << " is empty." << endl;
            cout << "Please choose a non-empty (and existing) file." << endl;
            continue;
        }
        else
        {
            tripStream.clear();
            tripStream.seekg(0);
        }
        fileOk = true;
    }

    if ( !tripStream )
    {
        cerr << "Error opening the file, going back to the menu..." << endl;
    }
    else
    {
        cout << endl << "Importing trips from " << nameFile << endl;
    }
    string firstLineSkipped;

    // We skip the first line of the file (there is no trip in it)
    getline(tripStream , firstLineSkipped );

    return tripStream;
} //----- Fin de askNameFileImport
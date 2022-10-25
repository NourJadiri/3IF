//
// Created by Nour on 24/10/2022.
//

#ifndef PROG_C___ENSEMBLE_H
#define PROG_C___ENSEMBLE_H
#define CARD_MAX 5

#include <iostream>

using namespace std;

class Ensemble {
private :
    unsigned int card_max , card_actuelle; //card_actuelle peut être considérée comme size du tableau
    int *elements;
public :

    //constructeurs
    Ensemble();
    Ensemble(unsigned int card_max = CARD_MAX);


    void Afficher();
    /*Ensemble(int tab[] ,unsigned int size);
    Ensemble ( const Ensemble & e ); //constructeur de copie

    //méthodes
    void afficher();
    bool estEgal(const Ensemble & e) const;
    unsigned int estInclus(const Ensemble & e) const;
    int ajouter(int element);
    bool retirer(int element);
    unsigned int retirer(const Ensemble e);
    int reunir(const Ensemble & e);
    unsigned int intersection(const Ensemble & e);
    unsigned int ajuster(int delta);*/

    //destructeur
    virtual ~Ensemble();
/*private:

    bool contains(int value);*/


};


#endif //PROG_C___ENSEMBLE_H

//
// Created by Nour on 24/10/2022.
//

#ifndef PROG_C___ENSEMBLE_H
#define PROG_C___ENSEMBLE_H
#define CARD_MAX 5

#include <iostream>

using namespace std;

class Ensemble_old {
private :
    unsigned int card_max , card_actuelle; //card_actuelle peut être considérée comme size du tableau
    int *elements;
public :

    //constructeurs
    Ensemble_old();
    Ensemble_old(unsigned int card_max = CARD_MAX);


    void Afficher();
    /*Ensemble_old(int tab[] ,unsigned int size);
    Ensemble_old ( const Ensemble_old & e ); //constructeur de copie

    //méthodes
    void afficher();
    bool estEgal(const Ensemble_old & e) const;
    unsigned int estInclus(const Ensemble_old & e) const;
    int ajouter(int element);
    bool retirer(int element);
    unsigned int retirer(const Ensemble_old e);
    int reunir(const Ensemble_old & e);
    unsigned int intersection(const Ensemble_old & e);
    unsigned int ajuster(int delta);*/

    //destructeur
    virtual ~Ensemble_old();
/*private:

    bool contains(int value);*/


};


#endif //PROG_C___ENSEMBLE_H

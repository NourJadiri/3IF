//
// Created by Nour on 24/10/2022.
//

#include "Ensemble.h"

//fonctions utiles parce que monsieur a décidé de ne pas nous laisser utiliser les fonctions de la stdlib
bool contains(const int *tab , int size , int value);

//constructeur par défaut


Ensemble::Ensemble(unsigned int card_max) {

    this->card_max = card_max;

    if(card_max == 0){
        this->elements = NULL;
    }
    else this->elements = new int[card_max];
    this->card_actuelle = 0;
}


/*Ensemble::Ensemble(int tab[], unsigned int size) {
    this->card_max = size;
    this->card_actuelle = 0;
    this->elements = new int[size];
    int i = 0;

    while (i < card_max) {
        if (!contains(tab[i])) elements[card_actuelle++] = tab[i];
        i++;
    }
    //sort(this->elements,this->elements + this->card_actuelle);
}

//constructeur de copie
Ensemble::Ensemble(const Ensemble & e){
    this->elements = new int[e.card_actuelle];
    int i;
    for(i = 0 ; i < card_actuelle ; i++){
        this->elements[i] = e.elements[i];
    }

    this->card_actuelle = e.card_actuelle;
    this->card_max = e.card_max;

#ifdef MAP
    cout << "Appel au constructeur de copie de <Ensemble>" << endl;
#endif
}*/

void Ensemble::Afficher(){
    cout << this->card_actuelle << endl;
    cout << this->card_max << endl;

    if(this->card_actuelle == 0) cout << "{}" << endl;
    else if(this->card_actuelle == 1) cout << "{" << this->elements[0] << "}" << endl;
    else{
        cout << "{" ;
        int i;
        for( i = 0 ; i < this->card_actuelle ; i++){
            if(i != this->card_actuelle - 1) cout << this->elements[i] << ",";
            else cout << this->elements[i];
        }
        cout << "}" << endl;
    }
}

/*bool Ensemble::estEgal(const Ensemble &e) const {
    bool estEgal = true;

    if(this->card_actuelle != e.card_actuelle || (this->elements == NULL && e.elements != NULL)
            || (this->elements != NULL && e.elements == NULL)) return false;
    else if(this->elements == NULL && e.elements == NULL) return true;
    else{
        int i;
        for(i = 0 ; i < this->card_actuelle ; i++){
            if(this->elements[i] != e.elements[i]){
                estEgal = false;
            }
        }
    }

    return estEgal;
}

unsigned int Ensemble::estInclus(const Ensemble &e) const {
    enum inclusion { NON_INCLUSION ,  INCLUSION_STRICTE ,  INCLUSION_LARGE };

    if(this->card_actuelle > e.card_actuelle) return NON_INCLUSION; //si l'ensemble est plus grand, then il est forcement pas inclus

    //on commence à l'indice ou on trouve le premier element de notre ensemble (since les ensembles sont triés)
    int index = find(e.elements , e.elements + e.card_actuelle , this->elements[0]) - e.elements;

    int n = 0;
    int i;
    for(i = index ; i < e.card_actuelle ; i++){
        n++;
        if(this->elements[i-index] != e.elements[i]){
            return NON_INCLUSION;
        }
    }
    if(n == e.card_actuelle) return INCLUSION_LARGE;
    else if(n < e.card_actuelle)  return INCLUSION_STRICTE;

}*/

Ensemble::~Ensemble(){
    delete[] elements;
    ///delete this : ON NE DELETE JAMAIS THIS PCQ ON NA PAS ACTIVEMENT ALLOCATE THIS

#ifdef MAP
    cout << "Appel au destructeur de <Ensemble>" << endl;
#endif
}

/*
bool Ensemble::contains(int value) {
    int i;
    for(i = 0 ; i < card_actuelle ; i++)
        if(elements[i] == value) return true;

    return false;
}*/


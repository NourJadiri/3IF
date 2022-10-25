/*************************************************************************
                           Ensemble  -  description
                             -------------------
    début                : 25/10
    copyright            : (C) 2022 par ELJADIRI N, ROULIER M, VOIGTLAENDER V
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Ensemble> (fichier Ensemble.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Ensemble.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Ensemble::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

void Ensemble::Afficher ( )
// Algorithme :
{
    Sort();
    cout << cardActuelle << "\r\n";
    cout << cardMax << "\r\n";

    if(this->cardActuelle == 0) cout << "{}" << "\r\n";
    else if(this->cardActuelle == 1) cout << "{" << this->elements[0] << "}" << "\r\n";
    else{
        cout << "{" ;
        unsigned int i;
        for( i = 0 ; i < cardActuelle ; i++){
            if(i != cardActuelle - 1) cout << this->elements[i] << ",";
            else cout << this->elements[i];
        }
        cout << "}" << "\r\n";
    }
} //----- Fin de Méthode


bool Ensemble::Contains ( int value ) const
// Algorithme :
{
    unsigned i;
    for(i = 0 ; i < cardActuelle ; i++)
        if(elements[i] == value) return true;

    return false;
} //----- Fin de Méthode


bool Ensemble::EstEgal(const Ensemble &unEnsemble) const
{
    bool estEgal = true;

    if (cardActuelle != unEnsemble.cardActuelle || (elements == NULL && unEnsemble.elements != NULL)
        || (elements != NULL && unEnsemble.elements == NULL))
        return false;
    else if (elements == NULL && unEnsemble.elements == NULL) return true;
    else
    {
        int i;
        for (i = 0; i < cardActuelle; i++) {
            if (elements[i] != unEnsemble.elements[i]) estEgal = false;
        }
    }

    return estEgal;
} //----- Fin de Méthode


crduEstInclus Ensemble::EstInclus(const Ensemble &unEnsemble) const
{
    int i;
    for(i = 0 ; i < cardActuelle ; i++){
        if ( !unEnsemble.Contains(elements[i]) ) return NON_INCLUSION;
    }
    if(cardActuelle == unEnsemble.cardActuelle) return INCLUSION_LARGE;
    return INCLUSION_STRICTE;

} //----- Fin de Méthode


crduAjouter Ensemble::Ajouter ( int aAjouter )
{
    // si valeur deja presente
    if ( Contains(aAjouter) ) return DEJA_PRESENT;
        // si ensemble plein
        // deja_present l'emporte bien sur plein avec la condition else if car on ne test pas la fullness d'elements
    else if ( cardActuelle == cardMax ) return PLEIN;
    // si ni plein ni deja_present on peut ajouter l'element
    elements[cardActuelle] = aAjouter;
    cardActuelle++;
    // on sort des lors qu'on ajoute something new
    Sort();
    return AJOUTE;
} //----- Fin de Méthode

unsigned int Ensemble::Ajuster ( int delta )
{
    // reduction pas dans les limites du possible (suppression d'elements)
    if (cardMax + delta <= cardActuelle ) cardMax = cardActuelle;
    else
    {
        cardMax += delta;
    }

    // quand on est sur qu'on va pas supprimer des elem on peut reajuster la taille du tableau
    int *copieElem = new int [cardMax];
    unsigned int i;
    for (i = 0; i < cardActuelle; i++)
    {
        copieElem[i] = elements[i];
    }
    delete [] elements;
    elements = copieElem;

    return cardMax;
} //----- Fin de Méthode

bool Ensemble::Retirer ( int element )
{
    // on cherche dabord si element existe dans ensemble
    // dans tous les cas, il faut ajuster cardActuelle = cardMax

    // on n'appelle pas Contains pcq on aura besoin de l'index de elem anyway
    unsigned int index = 0;
    for (index = 0; index < cardActuelle; index++)
    {
        if (elements[index] == element) break;
    }
    // si element n'existe pas dans ensemble
    if ( index == cardActuelle ) {
        Ajuster(cardActuelle - cardMax);
        return false;
    }

    // si element existe
    elements[index] = elements[cardActuelle - 1];
    cardActuelle--;
    Ajuster(cardActuelle-cardMax);
    // once again on trie pcq on a fait des modifs dans ensemble
    Sort();

    return true;
} //----- Fin de Méthode


unsigned int Ensemble::Retirer ( const Ensemble & unEnsemble )
{
    unsigned int count = 0;

    // on garde les valeurs initiales pour les ajustements après
    int cardActuIni = unEnsemble.cardActuelle;
    int cardMaxIni = cardMax;

    // on va creer un tableau de tous les elements a supprimer
    int *toDelete = new int [ unEnsemble.cardActuelle ];

    unsigned int i;
    for (i = 0; i < cardActuIni; i++)
    {
        toDelete[i] = unEnsemble.elements[i];
    }

    // on essaie de les retirer un par un
    // on oublie pas le compteur
    for (i = 0; i < cardActuIni; i++)
    {
        if (Retirer(toDelete[i])) count++;
        // en faisant appel a Retirer on a bien un ajustement de cardActuelle
    }

    delete [] toDelete;

    // on ajuste la taille
    Ajuster(cardMaxIni - cardMax);

    // pareil on oublie pas le sorting
    Sort();

    return count;
} //----- Fin de Méthode


int Ensemble::Reunir ( const Ensemble & unEnsemble )
{
    // JSP COMMENT FAIRE LA MAIS C EST L IDEE
    if (unEnsemble.EstInclus( this.Ensemble ) != NON_INCLUSION) return 0;

} //----- Fin de Méthode

//------------------------------------------------- Surcharge d'opérateurs
//Ensemble & Ensemble::operator = ( const Ensemble & unEnsemble )
// Algorithme :
//
//{
//} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
//Ensemble::Ensemble ( const Ensemble & unEnsemble )
// Algorithme :
//
//{
#ifdef MAP
//  cout << "Appel au constructeur de copie de <Ensemble>" << endl;
#endif
//} //----- Fin de Ensemble (constructeur de copie)


Ensemble::Ensemble ( unsigned int card_max )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Ensemble>" << endl;
#endif
    cardMax = card_max;
    cardActuelle = 0;
    if(card_max == 0){
        elements = NULL;
    }
    else elements = new int[card_max];

} //----- Fin de Ensemble


Ensemble::Ensemble ( int tab [], unsigned int size )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Ensemble>" << endl;
#endif
    cardMax = size;
    cardActuelle = 0;
    elements = new int[cardMax];

    unsigned i;
    for (i = 0; i < size; i++)
    {
        if ( !Contains(tab[i]) && cardActuelle != cardMax ) // not already in array nor full array
        {
            elements[cardActuelle] = tab[i];
            cardActuelle++;
            Sort();
        }

    }
} //----- Fin de Ensemble


Ensemble::~Ensemble ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Ensemble>" << endl;
#endif
    delete [ ] elements;
    ///delete this : ON NE DELETE JAMAIS THIS PCQ ON NA PAS ACTIVEMENT ALLOCATE THIS

} //----- Fin de ~Ensemble


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void Ensemble::Sort ( )
{
    bool estTrie = false;
    int temp = 0;

    while ( !estTrie )
    {
        estTrie = true;

        unsigned int i;
        for (i = 0; i < cardActuelle - 1 && cardActuelle != 0; i++)
        {
            if (elements[i] > elements[i+1])
            {
                temp = elements[i];
                elements[i] = elements[i+1];
                elements[i+1] = temp;
                estTrie = false;
            }
        }
    }
}
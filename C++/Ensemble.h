/*************************************************************************
                           Ensemble  -  description
                             -------------------
    début                : 25/10
    copyright            : (C) 2022 par ELJADIRI N, ROULIER M, VOIGTLAENDER V
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Ensemble> (fichier Ensemble.h) ----------------
#if ! defined ( ENSEMBLE_H )
#define ENSEMBLE_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes
const int CARD_MAX = 5;
//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Ensemble>
//
//
//------------------------------------------------------------------------

enum crduEstInclus { NON_INCLUSION , INCLUSION_LARGE , INCLUSION_STRICTE };
enum crduAjouter { DEJA_PRESENT , PLEIN , AJOUTE };

class Ensemble
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Afficher ( );
    // Mode d'emploi :
    // affiche caracteristiques de Ensemble

    bool Contains ( int value ) const;
    // Mode d'emploi :
    // verifie si element est deja dans le tableau des elements

    bool EstEgal ( const Ensemble &unEnsemble ) const;
    // Mode d'emploi :
    // check si deux ensembles sont egaux (memes cardinalite actuelle + memes elements inside)

    crduEstInclus EstInclus ( const Ensemble &unEnsemble ) const;
    // Mode d'emploi :
    // check si deux ensembles sont egaux (inclusion large)
    // ou Ensemble inclut dans unEnsemble (inclusion stricte)
    // ou Ensemble pas du tout inclus dans unEnsemble (non inclusion)

    crduAjouter Ajouter ( int aAjouter );
    // Mode d'emploi :
    // ajoute element aAjouter dans ensemble si cest possible et necessaire

    unsigned int Ajuster ( int delta );
    // Mode d'emploi :
    // agrandit, reduit, ou n'agit pas sur la taille de l'ensemble en fonction de la valeur de delta
    // retourne la cardinalite max de l'ensemble
    // Contrat :
    // si on veut proceder a une reduction
    // delta ne doit pas etre trop negatif pour ne pas enlever des elements de l'ensemble

    bool Retirer ( int element );
    // Mode d'emploi :
    // retirer element de ensemble s'il existe, renvoie true si retire, false si non retire
    // + reajustement

    unsigned int Retirer ( const Ensemble & unEnsemble );
    // Mode d'emploi :
    // retire si possible les elements donnes dans unEnsemble
    // renvoie le nombre d'elements retires

    int Reunir ( const Ensemble & unEnsemble );
    // Mode d'emploi :
    // rajoute a l'ensemble courant les elements d'unEnsemble qui ne sont pas deja dedans
    // renvoie un chiffre <0 si reajustement ; >0 si pas de reajustement
    // renvoie nombre elements rajoutes en valeur absolue

    unsigned int Intersection( const Ensemble & unEnsemble );
    //Mode d'emploi :
    // modifie l'ensemble courant en ne gardant que les elements communs a unEnsemble
    // renvoie le nombre d'elements retires
    // reajustement obligatoire au plus juste

//------------------------------------------------- Surcharge d'opérateurs
    //Ensemble & operator = ( const Ensemble & unEnsemble );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    //Ensemble ( const Xxxx & unXxxx );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Ensemble ( unsigned int carMax = CARD_MAX);
    // Mode d'emploi :
    // cree tableau de int de taille max carMax ou de taille CARD_MAX = 5 par defaut
    // Contrat :
    //

    Ensemble ( int t[], unsigned int nbElements);
    // Mode d'emploi :
    // cree tableau de int de taille nbElements, met valeurs dans t
    // Contrat :
    // nbElements >= nb elements ≠ dans t

    virtual ~Ensemble ( );
    // Mode d'emploi :
    // destructeur de Ensemble
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    void Sort ( );
// Mode d'emploi :
// tri l'array d'elements

//----------------------------------------------------- Attributs protégés
    int * elements;
    unsigned int cardActuelle; // peut être considere comme size du tableau
    unsigned int cardMax;

};

//-------------------------------- Autres définitions dépendantes de <Ensemble>

#endif // ENSEMBLE_H
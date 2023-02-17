function [V2,lambda2,A] = wielandt(A,prec)
%WIELANDT transforme A pour enlever la eigenval de plus grand module
%   fonctionne avec puissance iteree en alterne pour trouver toutes les
%   eigenval de la matrice A
%   on aura besoin de 2 eigenvec u et v qui ne peuvent pas se déduire l'un 
%   de l'autre! il faut donc les calculer séparemment
%   u est le eigenvec ligne associé à la plus grande eigenval (puissanceIt)
%   v est le eigenvec colonne associé
%   Av = λv & uA = λu

%input
%   A : matrice A dont on cherche les eigenval/vec et qu'on va transformer
%   prec : precision voulue pour les eigenval/vec
%output
%   V2 : eigenvec associé à la prochaine eigenval de plus grand module
%   lambda2 : prochaine eigenval de plus grand module
%   A : matrice A transformée (on a enlevé la plus grande eigenval)

[V1,lambda1] = puissanceIt(A, prec);

% on calcule U1 avec la transposée de A
[U,~] = puissanceIt(A',prec);
U1 = U';

% déflation de wielandt 
A = A - (lambda1 * (V1*U1)/(U1*V1));

% on cherche la eigenval suivante + son eigenvec associé
[V2,lambda2] = puissanceIt(A,prec);

end

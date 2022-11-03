function [X,lambda] = puissanceIt(A,prec)
%PUISSANCEIT trouve eigenval de plus grand module et eigenvec associe
%   fonctionne en alternance avec déflation de Wielandt pour trouver
%   toutes les eigenval d'une matrice
%   on norme à chaque itération pcq il faut faire gaffe à la gestion de la
%   taille quand même, bien que la norme n'importe pas
%   méthode qui ne permet d'extraire que la plus grande eigenval, 
%   une fois utilisée, elle ne peut pas extraire une autre eigenval
%   (sauf si on l'utilise en alternance avec wielandt :))

n = size(A,1); % nombre de coordonnées

% Y random, que l'on va faire évoluer jusqu'à atteindre le eigenvec
% SI PAR COINCIDENCE c'est déjà un eigenvec alors la méthode ne retournera
% pas la eigenval de plus grand module
Y = rand(n,1);

% juste pour rentrer dans le while
lambda = 2;
X = Y / norm(Y);

% tant que le vecteur updated n'est pas assez colinéaire avec le eigenvec
while (max(abs(lambda*X-Y)) >= prec)
    X = Y / norm(Y); % on a dit qu'on retournait un eigenvec normé
    Y = A * X;

    % juste pour get un index i tel qu'on n'ait pas de div par 0
    [~,i] = max(abs(X));
    lambda = Y(i) / X(i); % eigenval correspond au coef de proportionnalite
end

% once again, on veut un eigenvec normé
X = Y / norm(Y);

end
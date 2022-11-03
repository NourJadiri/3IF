function [X, it, omegaOpti] = Relaxation(A, B, prec)
%RELAXATION

%inputs
%   A : matrice A
%   B : vecteur B
%   prec : precision
%outputs
%   X : vecteur solution de AX = B

taille = max(size(diag(A)));

% on initialise randomly un vecteur solution de gauss
X = diag(rand(taille));
% vecteur resultat de l'iteration precedente
Y = diag(zeros(taille));

% on initialise randomly un vecteur solution de relax
Z = diag(rand(taille));

it = 0; % nombre d'iterations
err = inf; % erreur pour iteration boucle while

% matrice sur laquelle on va compute le rayon spectral
pi = zeros(taille);
D = diag(diag(A)); % enleve tout sauf diagonale
U = triu(A) - D; % upper triang
L = A - U; % lower triang

omegaOpti = 0; % parametre de pondération
rs = 1; % rayon spectral

% calcul du omega opti
for omega = 0.01 : 1e-2 : 1.99
    pi = (D + omega * L) \ ((1 - omega) * D - omega * U);
    if rayonSpectral(pi) < rs
        omegaOpti = omega;
        rs = rayonSpectral(pi);
    end
end

% procede d'iteration
while err > prec && it < 1e4

    for i = 1 : 1 : taille 

        Y(i) = B(i);
        
        for j = 1 : 1 : i-1
            Y(i) = Y(i) - A(i,j) * Y(j);
        end

        for j = i+1 : 1 : taille
            Y(i) = Y(i) - A(i,j) * X(j);
        end

        Y(i) = Y(i) / A(i,i);

    end
    X = Y; % update du vecteur solution de gauss
    Z = (1 - omegaOpti) * Z + omegaOpti * X; % update vect sol relax
    err = max(abs(A*Z-B));
    it = it + 1;

end 

end
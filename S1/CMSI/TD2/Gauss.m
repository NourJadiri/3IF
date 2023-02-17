function [X, it] = Gauss(A, B, prec)
%GAUSS

%inputs
%   A : matrice A
%   B : vecteur B
%   prec : precision
%outputs
%   X : vecteur solution de AX = B

taille = max(size(diag(A)));

% on initialise randomly un vecteur solution
X = diag(rand(taille));
% vecteur resultat de l'iteration precedente
Y = diag(zeros(taille));

err = inf; % condition arret boucle while
it = 0; % nombre d'iterations

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
    X = Y; % update du vecteur solution
    err = max(abs(A*X-B));
    it = it + 1;

end

end
function [val,vec] = chercher(A,prec,nb)
%CHERCHER cree vecteur val avec les 'nb' eigenval de plus grand module de A
%         et vecteur vec qui contient un eigenvec associe
%input
%   A : matrice A dont on cherche les eigenval/vec
%   prec : precision voulue, condition d'arret
%   nb : nombre d'eigenval/vec a chercher

n = size(A,1);

val = zeros(1,nb); % eigenval en ligne
vec = zeros(n,nb); % nb eigenvec en colonne

% d'abord on get la eigenval de plus grand module
% (ou la plus petite si on a mis l'inverse d'une matrice)
[v,lambda] = puissanceIt(A,prec);
val(1) = lambda;
for i = 1 : n
    vec(i,1) = v(i);
end

% maintenant on get les eigenval restants
for i = 2 : nb
    [v,lambda,A] = wielandt(A,prec);
    val(i) = lambda;
    for j = 1 : n
        vec(j,i) = v(j);
    end
end

end
function [] = diagDominant(A)
%DIAGDOMINANT
%   checks if matrix is diagonally dominant

[~, M] = size(A);

for i = 1 : M
    somme = sum(abs(A(i,:))) - abs(A(i,i));

    if somme > abs(A(i,i))
        disp("Matrix A is not diagonally dominant!");
        return;
    end

end
end
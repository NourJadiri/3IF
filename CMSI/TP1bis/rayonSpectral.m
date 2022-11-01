function [r] = rayonSpectral(A)
%RAYONSPECTRAL
%   calcule le plus grand module des eigenvalues

%input
%   A : matrice A
%output
%   r : rayon spectral de A

r = max(abs(eig(A)));

end


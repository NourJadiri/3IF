function tambour()
%TAMBOUR application sur le tambour
%   initialisation de la matrice qui correspond à la peau du tambour
%etapes :
%   recherche des eigenval en alternant methodes puissanceIt et wielandt
%   determination des 80 avec le plus petit module -> basses freq
%   determination des 25 avec le plus grand module -> hautes freq
%   determination de la eigenval la plus proche en module de 0.73
%   visualisation des vibrations correspondantes avec les eigenvec

% initialisation de A (zeros la ou la peau est fixee, comme début tp2)
lines = 20;
columns = 50;

B = ones(20,50);
% points fixes
% cote gauche
B(:,1) = 0;
% cote droit
B(:,end) = 0;
% bord haut
B(1,26:end) = 0;
% bord bas
B(end,1:24) = 0;
% rectangle
B(8:10,20:30) = 0;
B = reshape(B',lines*columns,1);

A = zeros(lines*columns, lines*columns);
% 1 la ou B à une valeur nulle (points fixes) et -4 la ou y en a pas
for i = 1 : size(B,1)
    if B(i,1) == 0 % point fixe
        A(i,i) = 1;
    else
        A(i,i) = -4;
        % tout sauf bord droit qui n'a pas de voisin à droite
        if mod(i,columns) ~= 0
            A(i,i+1) = 1;
        else
            A(i,i) = A(i,i) + 1; % on lui retire donc un voisin
        end
        % tout sauf bord gauche qui n'a pas de voisin à gauche
        if mod(i,columns) ~= 1
            A(i,i-1) = 1;
        else
            A(i,i) = A(i,i) + 1; % on lui retire donc un voisin
        end
        % tout sauf bord haut qui n'a pas de voisin au dessus
        if i > columns
            A(i,i-columns) = 1;
        else
            A(i,i) = A(i,i) + 1; % on lui retire donc un voisin
        end
        % tout sauf bord bas qui n'a pas de voisin en dessous
        if i <= size(B,1) - columns
            A(i,i+columns) = 1;
        else
            A(i,i) = A(i,i) + 1; % on lui retire donc un voisin
        end
        
    end
end

% pour verifier le laplacien et avoir AU = -λU
A = -A;
%max(eig(A))

% let's chercher (et trouver) les eigenval/vec
% mettre une bonne precision quand meme pcq sinon le resultat est pas ouf
precision = 1e-6;

% les 25 plus hautes fréquences
[lambda25,v25] = chercher(A,precision,25);
disp("les 25 plus hautes freq sont : ");
disp(lambda25);

% les 80 plus basses fréquences
[lambda80,v80] = chercher(inv(A),precision,80);
lambda80 = 1./lambda80;
disp("les 80 plus basses freq sont : ");
disp(lambda80);

% freq (eigenval) la plus proche de 0.73
% deja cest logique de partir des freq les plus basses pcq faible valeur
% ensuite, on va chercher une eigeval de (A - 0.73I) très proche de 0
% avec I la matrice identité
[lambda73,v73] = chercher(inv(A-0.73*eye(columns*lines)),precision,1);
lambda73 = 0.73 + 1./lambda73;
disp("la freq la plus proche de 0.73 est : ");
disp(lambda73);

% let's do la visualisation des vibrations
% first on va rassembler tous les eigenvec dans une seule big matrice
vib = zeros(lines*columns,25+80+1);
for i = 1 : 25
    for j = 1 : lines*columns
        vib(j,i) = v25(j,i);
    end
end
for i = 26 : (80+25)
    for j = 1 : lines*columns
        vib(j,i) = v80(j,i-25);
    end
end
for j = 1 : lines*columns
    vib(j,80+25+1) = v73(j,1);
end

% now on va faire comme tp2 et visualiser les vibrations pour chaque freq

figure(1)
for i = 0 : 80+25
    surf(reshape(vib(i*columns*lines+1 : (i+1)*columns*lines),[50,20])')
    title('vibration a une certaine frequence')
    axis([0 50 0 20 -0.2 0.2]);
    pause(.5) % pour avoir le time de visualiser les surf - 2 par seconde -
end

end
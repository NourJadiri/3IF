function [outputArg1,outputArg2] = untitled(inputArg1,inputArg2)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
outputArg1 = inputArg1;
outputArg2 = inputArg2;

% cotes droit et gauche
for i = 1 : lines-2
    % droit
    A(50*i + 1,50*i + 1) = -3;
    A(50*i + 1,50*i + 1 - 50) = 1; % voisin du dessus
    A(50*i + 1,50*i + 1 + 50) = 1; % voisin du dessous
    A(50*i + 1,50*i + 1 + 1) = 1; % voisin de droite

    % gauche
    A(50*i + 50,50*i + 50) = -3;
    A(50*i + 50,50*i + 50 - 50) = 1; % voisin du dessus
    A(50*i + 50,50*i + 50 + 50) = 1; % voisin du dessous
    A(50*i + 50,50*i + 50 - 1) = 1; % voisin de gauche
end

% coin haut gauche
A(1,1) = -2;
A(1,1+1) = 1; % voisin de droite
A(1,1+50) = 1; % voisin du dessous

% coin haut droite
A(columns,columns) = -2;
A(columns,columns-1) = 1; % voisin de gauche
A(columns,columns+50) = 1; % voisin du dessous

% coin bas gauche
A(end-49,end-49) = -2;
A(end-49,end-49+1) = 1; % voisin de droite
A(end-49,end-49-50) = 1; % voisin du dessus

% coin bas droite
A(end,end) = -2;
A(end,end-1) = 1; % voisin de gauche
A(end,end-50) = 1; % voisin du dessus

% bords haut et bas
for i = 1 : 23
    % bas
    A(951+i,951+i) = -3;
    A(951+i,951+i-1) = 1; % voisin de gauche
    A(951+i,951+i+1) = 1; % voisin de droite
    A(951+i,951+i-50) = 1; % voisin de dessus

    % haut
    A(25+i,25+i) = -3;
    A(25+i,25+i-1) = 1; % voisin de gauche
    A(25+i,25+i+1) = 1; % voisin de droite
    A(25+i,25+i+50) = 1; % voisin de dessous
end
% juste le dernier point de la premiere ligne
A(49,49) = -3;
A(49,49-1) = 1; % voisin de gauche
A(49,49+1) = 1; % voisin de droite
A(49,49+50) = 1; % voisin de dessous

% le rectangle du milieu
for i = 0 : 2
    for j = 0 : 10
        A(370+i+50*j,370+i+50*j) = -3;
        A(370+i+50*j,370+i+50*j-1) = 1; % voisin de gauche
        A(370+i+50*j,370+i+50*j+1) = 1; % voisin de droite
        A(370+i+50*j,370+i+50*j-50) = 1; % voisin de dessus
        A(370+i+50*j,370+i+50*j+50) = 1; % voisin de dessous
    end
end

end
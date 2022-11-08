function evolLibre(A, B, time)
%EVOLLIBRE evolution libre jusque etat d'equilibre 
% (ou ce qu'il en est au bout de 'time')

X = A\B;

% on update A car à t=0+, la t° n'est plus fixée

% BORDS ORANGES
for i = 2 : 49
    % bord haut
    A(i,i) = -3;
    A(i,i-1) = 1; % voisin de gauche
    A(i,i+1) = 1; % voisin de droite
    A(i,i+50) = 1; % voisin du dessous

    % bord bas
    A(950+i,950+i) = -3;
    A(950+i,950+i-1) = 1; % voisin de gauche
    A(950+i,950+i+1) = 1; % voisin de droite
    A(950+i,950+i-50) = 1; % voisin du dessus
end

% coin haut gauche
A(1,1) = -2;
A(1,1+1) = 1; % voisin de droite
A(1,1+50) = 1; % voisin du dessous

% coin bas droite
A(end,end) = -2;
A(end,end-1) = 1; % voisin de gauche
A(end,end-50) = 1; % voisin du dessus

% cotes droit et gauche
for i = 1 : 9
    % droit
    A(50*i + 1,50*i + 1) = -3;
    A(50*i + 1,50*i + 1 - 50) = 1; % voisin du dessus
    A(50*i + 1,50*i + 1 + 50) = 1; % voisin du dessous
    A(50*i + 1,50*i + 1 + 1) = 1; % voisin de droite

    % gauche
    A(50*i + 500,50*i + 500) = -3;
    A(50*i + 500,50*i + 500 - 50) = 1; % voisin du dessus
    A(50*i + 500,50*i + 500 + 50) = 1; % voisin du dessous
    A(50*i + 500,50*i + 500 - 1) = 1; % voisin de gauche
end

% les jointures ont deja ete faites sauf les entrees des jointures
% (ya un decalage de 450 ± 1)
% entree droite
A(50,50) = -4;
A(50,50-1) = 1; % voisin de gauche
A(50,500+1+1) = 1; % voisin de droite (de l'autre cote)
A(50,50+50) = 1; % voisin du dessous
A(50,500+1-50) = 1; % voisin du dessus (de l'autre cote)
% entree gauche
A(501,501) = -4;
A(501,501+1) = 1; % voisin de droite
A(501,51-1-1) = 1; % voisin de gauche (de l'autre cote)
A(501,501+50) = 1; % voisin du dessous
A(501,501-50) = 1; % voisin du dessus
%sortie droite
A(500,500) = -4;
A(500,500-1) = 1; % voisin de gauche
A(500,950+1+1) = 1; % voisin de droite (de l'autre cote)
A(500,500+50) = 1; % voisin du dessous
A(500,500-50) = 1; % voisin du dessus
% sortie gauche
A(951,951) = -4;
A(951,501-1-1) = 1; % voisin de gauche (de l'autre cote)
A(951,951+1) = 1; % voisin de droite
A(951,501-1-50) = 1; % voisin du dessous (de l'autre cote)
A(951,951-50) = 1; % voisin du dessus

% RECTANGLE BLEU
for i = 1 : 9
    % cote gauche
    A(50*i+158,50*i+158) = -4;
    A(50*i+158,50*i+158-50) = 1;
    A(50*i+158,50*i+158+50) = 1;
    A(50*i+158,50*i+158-1) = 1;
    A(50*i+158,50*i+158+1) = 1;
    % cote droit
    A(50*i+159,50*i+159) = -4;
    A(50*i+159,50*i+159-50) = 1;
    A(50*i+159,50*i+159+50) = 1;
    A(50*i+159,50*i+159-1) = 1;
    A(50*i+159,50*i+159+1) = 1;
end

% POINTS ROUGES
for i = 0 : 2
    for j = 0 : 2
        A(50*i+341+j,50*i+341+j) = -4;
        A(50*i+341+j,50*i+341+j-50) = 1;
        A(50*i+341+j,50*i+341+j+50) = 1;
        A(50*i+341+j,50*i+341+j-1) = 1;
        A(50*i+341+j,50*i+341+j+1) = 1;
    end
end

% on simule l'évolution en ouvrant une fenetre de figure
E = expm(A); % exponentielle de la matrice
figure(2)
surf(reshape(X,[50,20])')
for t = 1 : time
    X = E * X; % a chaque pas de temps on update
    surf(reshape(X,[50,20])')
    title('evolution de la repartition de temperature au cours du temps')
    axis([0 50 0 20 200 350]) % si on veut eviter le rescaling
    pause(.001) % pour avoir le temps de visualiser les surf
end

disp(['la temperature a l equilibre est de ' num2str(mean(X))]);

end
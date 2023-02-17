L'objectif ici sera de modéliser une surface avec plusieurs points dont la température est connue.
La surface sera modélisée par une matrice 20x50.
```Matlab
%surf : matrice modélisant la surface étudiée
%lines : nombre de lignes de la matrice (utile for later)
%columns : nombre de colonnes de la matrice (aussi utile later)

Xa = zeros(20,50);
lines = size(Xa,1);
columns = size(Xa,2);
```
La définition de nos trucs terminée, il s'agira de fill les valeurs particulières qui nous ont déja été passées:
    -Les bords sont à 300°C
    -Y'a 9 points bizarres qui sont à 500°C
    -T'as un rectangle chelou qui est à 100°C
```Matlab
%Setting des bords en prenant en compte la jointure
for i = 1:lines
    if i < 12 
        Xa(i,1) = 300;
    end
    if i >= 11
        Xa(i,columns) = 300;
    end
end

% Xa(1:lines,1) = 300;
% Xa(1:lines,columns) = 300;
Xa(1,1:columns) = 300;
Xa(lines,1:columns) = 300;

%Setting des points chelous à 500°C
Xa(7:9,columns-10 : columns - 8) = 500;

%Setting du rectangle bleu à 100°C
Xa(5:13,8) = 100;
Xa(5:13,9) = 100;

surf(Xa);
```
--- Trouver un moyen de rajotuer des images ---

On cherche une matrice A, qui permettra de modéliser le problème sous la forme A.X = B.
A correspond aux coefficients qui sont présents dans la relation : $\Delta u = u(x-1,y) + u(x+1,y) + u(x,y-1) + u(x,y+1) - 4u(x,y)$

Dans le cas général : $\Delta u = u(x-1,y) + u(x+1,y) + u(x,y-1) + u(x,y+1) - 4u(x,y) = du/dt$

Il faudra remplir alors la matrice A en prenant en compte si on est situés au niveau d'un bord, puisque dans ce cas, on aura un (ou plusieurs) des voisins qui n'existent tout simplement pas.

La première étape consiste à extraire la surface à l'équilibre, caractérisé par une température constante par rapport au temps, i.e : $du/dt=0$. Cela revient un peu à résoudre le système  où A sera la matrice à déterminer, et dont les coefficients seront extraits comme suit:

   <i>Pour un indice i , les cases dont la température est inconnue donneront A(i,i) = -4, celles ci correspondant au facteur $-4u(x,y)$ . Ce facteur représente la température de la case actuelle.
   Autour de cette case, on mettra des 1 pour les coefficients des termes représentants les voisins de la case (au indices i-50 pour le voisin du dessus, i-1 pour le voisin de gauche etc...)
   Cependant, pour les cases ou la température est connue à l'état final (exemple, les bords sont à 300°), du coté du système, cela se traduit par l'équation suivante : $u(x,y) = 300°C$ . Therefore, le seul cofficient qui 
   sera présent à cet indice i sera A(i,i) = 1.</i>

La fonction permettant de calculer l'état de notre plaque est donnée comme suit:

```Matlab
function X = surfaceEquilibre(surface)

    
    %A : Matrice qui stock les coeffients de pondération du Laplacien
    %B : Version 1D de la surface (se réferer à la doc de reshape cuz flemme d'expliquer)
    
    A = zeros(1000,1000);
    B = reshape(surface',1000,1);
    
    %On met des 1 la ou B à une valeur fixe et -4 la ou y en a pas
    for i=1:size(B,1)
        if B(i,1) ~= 0
            A(i,i) = 1;
        else
            
            A(i,i) = -4;
            A(i,i-50) = 1;
            A(i,i+50) = 1;
            A(i,i-1) = 1;
            A(i,i+1) = 1;
        end
    end
    
    % On résout le système A.X = B pour avoir les températures à l'équilibre
    X = A\B;
    
    %Et on reshape pour l'avoir sous forme de surface sexy
    X = reshape(X,[50,20]);
end
```
Au final, il suffit de faire un simple appel à notre fonction :
   
```Matlab
Xa = surfaceEquilibre(Xa); % Se référer à la partie functions plus bas
surf(Xa);
```
---Inserer deuxième image---

Then on update la matrice qui possède les coefficients de pondérations pour visualiser l'évolution de la température, cette fois en fonction du temps. Le remplissage de la matrice sera sensiblement différent vu que cette fois, aucune température à l'état final n'est connue. Il faudra alors faire gaffe aux voisins de chaque points (vérifier si ceux ci existent notemment).

<b> Par exemple : </b> le coin supérieur gauche, qui correspond à la première ligne de notre matrice aura seulement deux voisins, ce qui fait que A(1,1) sera égal à -2 au lieu de -4.
On raisonne de manière similaire pour les bords, et on fait attention à la partie ou il y'a une "connexion", car ici les voisins de droite/gauche ne seront pas simplement aux indices i+1 , i-1. Un facteur +450 interviendra. 

Une implémentation dégueulasse en spaghetti code de la fonction qui créerait cette matrice ressemble à ça :

```Matlab
function A = matriceCoefs(surface)

% JE NE SUIS PAS FIER DE MON SPAGHETTI CODE LA

    A = zeros(1000,1000);
    B = reshape(surface',1000,1);
    
    for i = 1:1000
        A(i,i) = -4;
    
        if i == 1 % Coin haut gauche
            A(i,i) = -2;
            A(i,i+1) = 1;
            A(i , i + 50) = 1;
        
    
        elseif i == 1000 % Coin bas droit
            A(i,i) = -2;
            A(i,i -50) = 1;
            A(i , i-1) = 1;

        elseif i == 50 % Coin haut droit
            A(i,i) = -4;
            A(i,i-1) = 1;
            A(i,i+50)= 1;
            A(i , i+451+1) = 1;
            A(i , i + 451 - 50) = 1;

        elseif i == 951 % Coin bas gauche
            A(i,i) = -4;
            A(i,i-50) = 1;
            A(i,i+1) = 1;
            A(i , i - 451 -1) = 1;
            A(i , i-401) = 1;

    
        elseif i > 1 && i < 50 % Bord supérieur sauf partie jointe
            A(i,i) = -3;
            A(i , i-1) = 1;
            A(i , i+1) = 1;
            A(i , i + 50) = 1;
        
    
        elseif i > 951 && i < 1000 % Bord inférieur sauf partie jointe
            A(i,i) = -3;
            A(i , i-1) = 1;
            A(i , i+1) = 1;
            A(i , i-50) = 1;
        
    
        elseif i > 1 && i < 500 && mod(i,50) == 1 % Bord gauche sauf partie jointe
            A(i,i) = -3;
            A(i , i+1) = 1;
            A(i , i+50) = 1;
            A(i , i-50) = 1;
        
    
        elseif i > 500 && i < 1000 && mod(i,50) == 0 % Bord droit sauf partie jointe
            A(i,i) = -3;
            A(i , i-1) = 1;
            A(i , i-50) = 1;
            A(i , i+50) = 1;

        elseif i > 500 && mod(i,50) == 1 % Jointure gauche
            A(i,i) = -4;
            A(i , i+1) = 1;
            A(i , i+50) = 1;
            A(i , i-50) = 1;
            A(i , i - 451 - 1) = 1;

        elseif i < 500 && mod(i,50) == 0 % Jointure droite
            A(i,i) = -4;
            A(i,i-1) = 1;
            A(i,i-50) = 1;
            A(i,i+50) = 1;
            A(i,i+451+1) = 1;
        
        else % Sinon pour les cases "normales"            
            A(i,i) = -4;
            A(i,i-50) = 1;
            A(i,i+50) = 1;
            A(i,i-1) = 1;
            A(i,i+1) = 1;
        end
    end
    
    
end
```
<i> On dirait c'est un gros truc, mais c'est juste beaucoup de cas à considérer (du if else à la chaine) </i>

Cela se traduit par l'image suivante : les case entourées par la même couleur ont les mêmes voisins.

---Inserer la troisième image---
On fait un appel à cette fonction du coup:

```Matlab
% A : Matrice qui stock les coeffients de pondération du Laplacien

A = matriceCoefs(Xa); 
```

Maintenant que notre matrice A a été construite, il suffit de l'utiliser pour caractériser l'évolution libre de la température.

L'évolution libre de la température est literallement ce que décrit l'équation différentielle $\Delta u = u(x-1,y) + u(x+1,y) + u(x,y-1) + u(x,y+1) - 4u(x,y) = du/dt$.

Une solution à cette équation, pour chaque case, s'écrit de la forme $u(x,y) = U_{0}.e^{cste * t + B}$ (fais moi confiance).

Pour un vecteur alors, on peut juste appliquer cette solution à l'ensemble des éléments du vecteur. L'implémentation sur matlab est assez facile. Petite précision par contre, la constante "cste" dans le cas d'une écriture vectorielle représente la matrice A qu'on a extrait juste avant. Il faudra alors se comporter avec des exponentielles de matrices (tkt c'est pas dur et puis sur matlab t'as la fonction expm(A) qui le fait).

J'arrive pas à écrire la démo, alors je vais faire genre que c'est un exercice pour le lecteur, mais en gros $U(t+\Delta t) = e^{A*\Delta t}.U(t)$
```Matlab
[Xeq,t] = evolution_temperature(Xa);
```
Avec la fonction evolution_température qui ressemble à ça :

```Matlab 
function [X,t] = evolution_temperature(surface)

    A = matriceCoefs(surface);

    B1 = reshape(surface',1000,1);

    X = B1;
    Xa = B1 - B1;
    
    t = 0;
    while max(abs(X - Xa)) >= 0.01
        
        %On passe en version surface
        Y = reshape(X,50,20);
        
        Y = Y';
        surf(Y);
        
        Xa = X;
        
        X = expm(A)*Xa;
       
        t = t+1;
        pause(0.1);
    end
    Y = reshape(X,50,20);
    Y = Y';
    surf(Y); %Equilibre final
end
```
Pour la partie avec chauffage, il suffit juste de rajouter dans le while au dessus les lignes qui vont set les températures des points à 500°C à chaque fois.

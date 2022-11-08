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
%Setting des bords
for i = 1:lines
    if i < 12 
        Xa(i,1) = 300;
    end
    if i >= 11
        Xa(i,columns) = 300;
    end
end

for i = 1:columns
    Xa(1,i) = 300;
    Xa(lines,i) = 300;
end

%Setting des points chelous à 500°C
for i = 7:9
    for j = columns - 10: columns - 8
        Xa(i,j) = 500;
    end
end

%Setting du rectangle bleu à 100°C
for i = 5:13
    Xa(i, 8) = 100;
    Xa(i, 9) = 100;
end
%disp(Xa)
```
Résolution du système se fera en traduisant la surface réchauffée par un vecteur X, de taille 1000 qui stockera toutes les valeurs u(x,y), qui représentent les différentes températures aux différentes abscisses.

On cherche une matrice A, qui permettra de modéliser le problème sous la forme A.X = B.
A correspond aux coefficients qui sont présents dans la relation :   
$$\Delta u = u(x-1,y) + u(x+1,y) + u(x,y-1) + u(x,y+1) - 4u(x,y)$$
A sera par conséquent une matrice pseudo-diagonale, dont la diagonale principale sera remplie de -4 avec des 1 au niveau des indices qui représentent les voisins:

  <b>• i - 50 : voisin du dessus


  • i + 50 : voisin du dessous


  • j - 1 : voisin de gauche


  • j + 1 : voisin de droite</b>

```Matlab
%A : Matrice qui stock les coeffients de pondération du Laplacien

A = zeros(1000,1000);
B = reshape(Xa',1000,1);
disp(B)

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
```
On fait passer la matrice surface sous forme de vecteur 1D
```Matlab
X = gaussModifie(A, B, 0.1);
x_2 = A \ B;
X = reshape(X,[50,20]); %On reshape en ligne
x_2 = reshape(x_2,50,20);
surf(X);
surf(x_2);
```

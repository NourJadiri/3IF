% DEFINE A and B

A = [8 2 3 1 ;
     0 6 4 0 ;
     2 3 9 3 ;
     1 2 3 7 ;];

omega = find_optimal_omega(A);

B = [25 ; 24 ; 47 ; 42];

% DEFINE Tolerance
tol = 1e-6;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% CHECK IF MATRIX IS SQUARE
[M , N] = size(A);

if M ~= N 
    error("Matrix A is not square !");
end

% CHECK IF MATRIX IS DIAGONALLY DOMINANT

for i = 1 : M
    row = abs(A(i,:));
    somme = sum(row) - row(i);
    if somme >= row(i)
        error("Matrix A is not diagonally dominant");
    end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% THE ACTUAL GAUSS SEIDEL METHOD
x = ones(size(A,1),1);
y = x;
err = inf;
iter = 0;
while err > tol
    for i = 1 : size(A,1)
        y(i) = B(i);
        for j = 1 : i-1
            y(i) = y(i) - A(i,j) * y(j);
        end
        for j = i+1 : size(A,1)
            y(i) = y(i) - A(i,j) * x(j);
        end
        y(i) = y(i)/A(i,i);
        
        y(i) = omega * y(i) + (1 - omega)*x(i);
    end
    err = max(abs(x - y));
    x = y;
    iter = iter + 1;
end

disp(x);
disp("Nombre d'iterations : " + iter);

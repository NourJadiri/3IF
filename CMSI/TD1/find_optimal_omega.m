% DEFINE A 

A = [8 2 3 1 ;
     0 6 4 0 ;
     2 3 9 3 ;
     1 2 3 7 ;];

% FINDING THE OPTIMAL OMEGA

find_optimal_omega(A)

function omega_optimal = find_optimal_omega(A)

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



% DEFINE AN INITIAL OMEGA AND SPECTRAL RADIUS

    omega_optimal = 1;
    rayon_optimal = 1;
    
% DEFINE THE MATRICES NECESSARY TO COMPUTE OMEGA
    
    D = diag(diag(A));
    L = tril(A);
    U = triu(A);
    
    for omega = 0 : 0.05 : 2

        % WE COMPUTE THE Pi MATRIX (dans le sujet)

        T = (D - omega*L)\((1 - omega) * D - omega * U);

        % UPDATE THE RADIUS (Le rayon spectral r(M) d'une matrice M est le
        % plus grand module de ses valeurs propres.)

        rayon = max(abs(eig(T)));
        
        % WE ONLY KEEP THE MINIMAL RADIUS

        if rayon < rayon_optimal 
            rayon_optimal = rayon;
            omega_optimal = omega;
        end
    end
    
end



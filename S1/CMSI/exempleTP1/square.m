function [] = square(A)
%SQUARE
%   checks if matrix is square and invertible
[M, N] = size(A);

if M ~= N
    disp("Matrix A is not square!");
    return;
end

if det(A) == 0
    disp("Matrix A is not invertible!");
    return;
end
end
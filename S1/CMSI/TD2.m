% size
m = 50; % numberOfColums
n = 20; % numberOfRows

B = NaN([n, m]);

% boundary conditions
B(1, :) = 300; % orange edge
B(end, :) = 300; % orange edge
B(2:11, 1) = 300; % orange edge
B(10:19, end) = 300; % orange edge
B(5:13, 8:9) = 100; % blue edge
B(7:10, 40:43) = 500; % red dots

b = reshape(B', [], 1); % convert boundary conditions to 1d

% calculation
A = zeros(m*n); % forward declaration
for y = 1:n
    for x = 1:m
        i = xy2i(m, x, y);
        if ~isnan(b(i)) % temperature already known
            A(i, i) = 1;
        else % temperature unknown
            b(i) = 0;
            A(i, i) = -4;
            A(i, xy2i(m, x, y-1)) = 1;
            A(i, xy2i(m, x, y+1)) = 1;
            if x == 1 % right side of connected edges
                A(i, xy2i(m, m, y-10)) = 1;
                A(i, xy2i(m, x+1, y)) = 1;
            elseif x == m % left side of connected edges
                A(i, xy2i(m, x-1, y)) = 1;
                A(i, xy2i(m, 1, y+10)) = 1;
            else % normal point
                A(i, xy2i(m, x-1, y)) = 1;
                A(i, xy2i(m, x+1, y)) = 1;
            end
        end
    end
end

t = A\b;
T = reshape(t, [m, n])'; % convert soultion back to 2d

%plot
[X,Y] = meshgrid(1:m,1:n);
surf(X,Y,T)

% functions
function i = xy2i(m, x, y)
    i = x + (y-1)*m;
end

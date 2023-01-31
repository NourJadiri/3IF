function [y] = x5_bis(t)

y = zeros(size(t));
count = 1;

    for x = t
        if mod(x,0.1) >= -0.05 && mod(x,0.1) <= 0.05
            y(count) = 1;
        end
        count = count + 1;
    end
end


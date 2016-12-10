function [f, grad] = nls_wrapper(x, cost, grad_cost)
    f = cost(x);
    grad = grad_cost(x);
end

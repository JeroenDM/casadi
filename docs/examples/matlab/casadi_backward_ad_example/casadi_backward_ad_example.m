% An implementation nonlinear least squares using casadi's backward AD tool
% A solution to an exercise for the course "Optimization of Mechatronic 
% Systems" (B-KUL-H04U1C) at KU Leuven
% Based on the example code for session 7 and with the help from Joris
% Gillis
% Jeroen De Maeyer, 2016


% Try to fit a nonlinear curve to given data (yi, ti) for i = 1...m
% c(t, x) = x1 + x2 * exp(-(x3-t)^2/x4 + x5 * cos(x6*t)
% With a vector x containing 6 decision variables
% We aim to minimize sum( (yi - c(ti, x))^2 )  sum over i = 1...m
import casadi.*

% load example data
load('nls_data.mat');

% Dicision variables as a symbolic vector
x = SX.sym('x',6,1);

% Initial values dicision variables
x0 = ones(6,1);

% Define cost function as a casadi function
J = casadi.Function('J',{x},{nls(x, ys, ts)});
% J.print_dimensions;

% Calculate the gradient using backward AD
Jrev = J.reverse(1);
% Jrev.print_dimensions;

% Convert cost function and gradient to matlab functions
cost = @(x) full(J(x));
grad_cost = @(x) full(Jrev(x, 0, 1));

% Solve the optimization problem using Matlab,s fminunc
options = optimoptions('fminunc', 'GradObj', 'on', 'Algorithm', 'quasi-newton');
[xstar2,fval2,exitflag2,output2] = fminunc(@(x) nls_wrapper(x, cost, grad_cost), x0, options);


[t_fit2, y_fit2] = decay_oscillation(xstar2, 0, 20, 100, 0, 0);

% subplot(2,1,2);
plot(ts, ys, '.'); hold on
plot(t_fit2, y_fit2, 'xr');
legend('data points', 'backward AD casadi');


function [ts, ys] = decay_oscillation(x0, tmin, tmax, m, sig_t, sig_y)

fun = @(t, x) x(1) + x(2)*exp(-(x(3)-t)^2/x(4)) + x(5)*cos(x(6)*t);
ts = linspace(tmin,tmax,m)' + sig_t*randn(m, 1);
ys = [];
for i=1:length(ts)
    ys = [ys; fun(ts(i), x0)];
end
ys = ys + sig_y*randn(m, 1);

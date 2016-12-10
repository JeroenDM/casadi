function v = nls(x, ys, ts)

m = length(ys);
v = 0;

for i = 1:m
    y = ys(i,:);
    t = ts(i);
    
    x7 = (x(3)-t)^2;
    x8 = x7/x(4);
    x9 = exp(-x8);
    x10 = x(2)*x9;
    x11 = cos(x(6)*t);
    x12 = x(5)*x11;
    x13 = x10+x12;
    x14 = x(1) + x13;
    x15 = (y-x14)^2;
    
    v = v+x15;
end

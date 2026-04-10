clc;
clear;
close;
for n = 5:5:100
    L = 1000;   
    dmax = 150;   
    [g] = NL_T_LocalityConnex(n, L, dmax);
    ind = 1;
    NL_G_ShowGraphN(g, ind);
    xtitle("Network with "+string(n)+" nodes");
    sleep(1000);  
    clf();
end

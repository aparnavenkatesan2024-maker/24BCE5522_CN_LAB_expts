clc;
clear;
close;
L = 1000;
dmax = 150;
[g1] = NL_T_LocalityConnex(200, L, dmax);
scf(1);
NL_G_ShowGraphN(g1, 1);
xtitle("Network with 200 Nodes");

[g2] = NL_T_LocalityConnex(300, L, dmax);
scf(2);
NL_G_ShowGraphN(g2, 1);
xtitle("Network with 300 Nodes");


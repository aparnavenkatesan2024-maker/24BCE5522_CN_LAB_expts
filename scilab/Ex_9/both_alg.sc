L = 1000;
dmax = 150;
k = 1;
for n = 5:5:100
    [g] = NL_T_LocalityConnex(n, L, dmax);
    source = 1;
    // routing with bellmanford
    timer();
    [distBF, predBF] = NL_R_BellmanFord(g, source);
    bf_time(k) = timer();

    // routing with djikstra
    timer();
    [distDJ, predDJ] = NL_R_Dijkstra(g, source);
    dj_time(k) = timer();
    nodes(k) = n;
    k = k + 1;
end

plot(nodes, bf_time, '--ro');
plot(nodes, dj_time, '--bo');


leg = legend("Bellman-Ford", "Dijkstra");
leg.legend_location = "out_upper_right";
xtitle("Routing Duration comparison btwn Bellman-Ford & Djikstra", "No. of nodes", "Time");

clc;
clear;
function duration=ARC_congestion(num_nodes)
    tic();
    rate = 10;
    threshold = 50;
    max_queue = 100;
    for i = 1:num_nodes
        queue = grand(1,1,"uin",0,max_queue);
        if queue > threshold then
            rate = rate * 0.5;
        else
            rate = rate + 1;
        end


        for j = 1:1000
            temp = sin(j) * cos(j);
        end
    end
    duration = toc();
endfunction
n1 = 200;
A1 = rand(n1, n1);
time1 = ARC_congestion(n1);
n2 = 300;
A2 = rand(n2, n2);
time2 = ARC_congestion(n2);

disp("Duration for 200 node network:");
disp(time1);
disp("Duration for 300 node network:");
disp(time2);
nodes = [200 300];
times = [time1 time2];
figure();
bar(nodes, times);
xlabel("Number of Nodes");
ylabel("Duration (seconds)");
title("ARC Congestion Control Durations of 200 node and 300 node networks");

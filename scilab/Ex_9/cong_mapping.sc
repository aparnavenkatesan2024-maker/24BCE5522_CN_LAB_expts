nodes_list = [500 400 300 200 100];
num_methods = 5;
durations = zeros(num_methods, length(nodes_list));
function A=generate_network(method, N)
    select method
        case 1
            // random method
            A = rand(N,N) > 0.75;
            A = A - diag(diag(A));
        case 2
            // ring/lattice method
            A = zeros(N,N);
            for i=1:N
                A(i,modulo(i,N)+1)=1;
                A(modulo(i,N)+1,i)=1;
            end



            for i=1:N
                for k=1:5
                    j = ceil(rand()*N);
                    if i<>j then A(i,j)=1; A(j,i)=1; end
                end
            end
        case 3
            // small world method
            A = zeros(N,N);
            for i=1:N
                A(i,modulo(i,N)+1)=1;
                A(modulo(i,N)+1,i)=1;
            end
            for i=1:N
                for k=1:10
                    j = ceil(rand()*N);
                    if i<>j then A(i,j)=1; A(j,i)=1; end
                end
            end
        case 4
            // multi-branch method (here, 3 children per node)
            A = zeros(N,N);
            for i=2:N
                parent = floor((i-2)/3)+1;
                A(i,parent)=1; A(parent,i)=1;
            end
        case 5
            // fully connected method
            A = ones(N,N)-eye(N,N);
    end
endfunction
// we consider here durations = max node degree
for m=1:num_methods
    for n_idx=1:length(nodes_list)
        N = nodes_list(n_idx);
        A = generate_network(m,N);
        congestion = sum(A,2);
        durations(m,n_idx) = max(congestion);
    end
end

clf;
colors = ['r','g','b','m','c'];
methods = ["Random Graph","Ring/Lattice+Links","Small-World","Tree (3-branch)","Fully Connected"];

for m=1:num_methods
    plot(nodes_list, durations(m,:), colors(m)+"o-", "LineWidth", 2, "MarkerSize", 6);
End

xlabel("Number of Nodes");
ylabel("Network Duration (max congestion)");
title("Network Duration vs Nodes for 5 Methods");
legend(methods,"location","best");
grid on;

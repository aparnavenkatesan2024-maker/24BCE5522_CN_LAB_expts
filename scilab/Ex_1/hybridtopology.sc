// Experiment : Hybrid using Star + Ring + Bus topologies
clear;
clc;
NameOfNetwork = 'Hybrid Topology (Star + Ring + Bus)';
NumberOfNodes = 27;
//STAR (1–9)
StarStart = [2 3 4 5 6 7 8 9];
StarEnd   = [1 1 1 1 1 1 1 1];
// RING (10–17)
RingStart = [10 11 12 13 14 15 16 17];
RingEnd   = [11 12 13 14 15 16 17 10];
//BUS (18–27) 
BusStart = [18 19 20 21 22 23 24 25 26];
BusEnd   = [19 20 21 22 23 24 25 26 27];
//hybrid connecs.
HybridStart = [1 17];
HybridEnd   = [10 18];
StartingNodes = [StarStart RingStart BusStart HybridStart];
EndingNodes   = [StarEnd   RingEnd   BusEnd   HybridEnd];


//nodes
XCoordinatesOfNodes = [500 500 500 200 200 200 800 800 800 100 200 300 400 500 600 700 400 100 200 300 400 500 600 700 800 900 1000];
YCoordinatesOfNodes = [500 200 800 800 200 500 200 500 800 300 400 500 600 700 600 400 300 100 100 100 100 100 100 100 100 100 100];
[TopologyGraph] = NL_G_MakeGraph( NameOfNetwork, NumberOfNodes, StartingNodes, EndingNodes, XCoordinatesOfNodes, YCoordinatesOfNodes);
//displaying
WindowIndex = 1;
NL_G_ShowGraph(TopologyGraph, WindowIndex);
xtitle("Hybrid Topology","X-Nodes","Y-Nodes");

//numbering for the nodes and edges
WindowIndex = 2;
NL_G_ShowGraphNE(TopologyGraph, WindowIndex);
xtitle("Node and Edge Numbering","X-Nodes","Y-Nodes");

//color
NodeColor = 2;
BorderThickness = 10;
NodeDiameter = 25;
WindowIndex = 3;
ListOfNodes = 1:NumberOfNodes; // all nodes
[Go,F]=NL_G_HighlightNodes(TopologyGraph, ListOfNodes, NodeColor, BorderThickness, NodeDiameter, WindowIndex);

//edges
EdgeColor = 4;
EdgeWidth = 5;
WindowIndex = 4;
[n,l]=NL_G_GraphSize(TopologyGraph); // all edges

ListOfEdges = 1:l
[Go,F]=NL_G_HighlightEdges(TopologyGraph, ListOfEdges, EdgeColor, EdgeWidth, WindowIndex);

disp("Node    Number of Edges");
MaxEdges = 0;
MaxNode = 1;
for i = 1:NumberOfNodes
    EdgeSet = NL_G_EdgesOfNode(TopologyGraph, i);
    EdgeCount = length(EdgeSet);
    mprintf("%d\t%d\n", i, EdgeCount);
    if EdgeCount > MaxEdges then
        MaxEdges = EdgeCount;
        MaxNode = i;
    end
end
disp("Node with maximum edges:");
disp(MaxNode);
disp("Maximum number of edges:");
disp(MaxEdges);

// total no. of nodes and edges
[ExtractNode, ExtractEdge] = NL_G_GraphSize(TopologyGraph);
disp("Total number of nodes:");
disp(ExtractNode);
disp("Total number of edges:");
disp(ExtractEdge);

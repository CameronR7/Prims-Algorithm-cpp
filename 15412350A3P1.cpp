// Student Name: Cameron Rajbally
// Student Number: 15412350
/*Question asked to AI: 1.Generate C++ code that will use Prim’s algorithm using ADT with a time complexity of O(n^2)
*/


#include <iostream>
#include <vector>
#include <fstream>
#include <climits>

using namespace std;

// Function to find the vertex with the minimum key value
// changed: The `min_Key` function remains the same to find the minimum key value from the set of vertices.
int min_Key(vector<int>& key, vector<bool>& mstSet, int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

// Function to print the constructed MST
// changed: This function prints the edges in the MST and their corresponding weights.
void printMST(vector<int>& parent, vector<vector<int>>& graph, int V) {
    cout << "Minimum Spanning Tree using Prim's Algorithm:\nEdge \tWeight\n";
    for (int i = 1; i < V; i++)
        cout << parent[i] << " - " << i << " \t" << graph[i][parent[i]] << " \n";
}

// Function to construct and print MST for a graph represented using adjacency matrix representation
// changed: This function implements Prim's algorithm to construct the MST.
void primMST(vector<vector<int>>& graph, int V) {
    vector<int> parent(V); 
    vector<int> key(V);   
    vector<bool> mstSet(V); 

    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    
    key[0] = 0;     
    parent[0] = -1; 

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++) {
     
        int u = min_Key(key, mstSet, V);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    // Print the constructed MST
    printMST(parent, graph, V);
}

int main() {
    
    // changed: This block reads the vertex count, edge count, and Weight
    ifstream file("c:\\data\\fiberdata.txt");
    if (!file) {
        cerr << "Unable to open file";
        exit(1); // Call system to stop
    }

    int V, E;
    file >> V >> E;

    // Initialize the graph with 0s
    vector<vector<int>> graph(V, vector<int>(V, 0));

    // Read edges and weights from the file
    for (int i = 0; i < E; i++) {
        int u, v, w;
        file >> u >> v >> w;
        graph[u][v] = w;
        graph[v][u] = w; 
    }

    file.close();

    //Run and print Prim
    primMST(graph, V);

    return 0;
}

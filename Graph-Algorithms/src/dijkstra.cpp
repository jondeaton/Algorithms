/**
 * File: dijkstra.cpp
 * ------------------
 * implementation of Dijkstra's Algorithm
 */

#include "graph.cpp"
#include <stdio>
#include <iostream>
using namespace std;

template <class T>
void make_graph(Graph<T> &graph) {
    char* line = NULL;
    getline(line, &size, cin);
    int N = atoi(line);
    for (int i = 0; i < N; i++) graph.nodes.add();
}



int main(int argc, char* argv[]) {
    Graph<int> graph;
    make_graph(graph);
    cout << dijkstra(graph, 0) << endl;
}
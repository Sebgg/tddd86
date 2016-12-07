// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include "pqueue.h"
#include <queue>
#include <limits>
// TODO: include any other headers you need; remove this comment
using namespace std;

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    /*start->visited = true;
    if(graph.compare(start, end)){
        return path;
    }
    for(auto neighbour : graph.getNeighbors(start)){
        if(!neighbour->visited){
            path.push_back(neigbour);
            depthFirstSearch(graph, neighbour, end);

        }
    }*/
    return path;
}

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    vector<Vertex*> tmpPath;
    PriorityQueue<Node *> que;
    Set<Node *> vertexSet = graph.getVertexSet();
    for(auto vertex : vertexSet){
        if(!graph.compare(start, vertex)){
            vertex->cost = numeric_limits<double>::max();
        }
        que.enqueue(vertex, vertex->cost);
        Node* myNode = graph.getNode(vertex->name);
        myNode->setColor(YELLOW);
    }

    while(!que.isEmpty()){
        Vertex *u = que.dequeue();

        if(graph.compare(u, end)){
            while(u->previous != nullptr){
                tmpPath.push_back(u);
                u = u->previous;
            }
            while(!tmpPath.empty()){
                path.push_back(tmpPath.back());
                tmpPath.pop_back();
            }
        }
        for(auto neighbour : graph.getNeighbors(u)){
            double altDist = u->cost + (graph.getEdge(u, neighbour)->cost);
            if(altDist < neighbour->cost){
                neighbour->cost = altDist;
                neighbour->previous = u;
                que.changePriority(neighbour, altDist);
            }
        }
    }

    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}

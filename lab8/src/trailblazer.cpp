// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include "pqueue.h"
#include <queue>
#include <limits>
#include <algorithm>
// TODO: include any other headers you need; remove this comment
using namespace std;



vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    /*vector<Vertex*> tmpPath;
    path.push_back(start);
    start->visited = true;
    if(graph.compare(start, end) == 0){
        path.push_back(end);
        start->setColor(GREEN);
        return path;
    } else {
        for(auto neighbour : graph.getNeighbors(start)){
            if(neighbour->visited == false){
                neighbour->visited = true;
                neighbour->setColor(YELLOW);
                path.push_back(neighbour);
                tmpPath = depthFirstSearch(graph, neighbour, end);
                path.insert(path.end(), tmpPath.begin(), tmpPath.end());
                return path;
            } else {
                neighbour->setColor(GRAY);
                return path;
            }
        }
    }*/

}
    /*
    vector<Vertex*> tmpPath;
    tmpPath.push_back(start);
    Vertex *curr;
    while(!tmpPath.empty()){
        curr = tmpPath.front();
        tmpPath.erase(tmpPath.begin());
        if(graph.compare(curr, end) == 0){
            while(!tmpPath.empty()){
                curr = tmpPath.front();
                tmpPath.erase(tmpPath.begin());
                curr->visited = false;
                curr->setColor(GREEN);
                path.push_back(curr);
            }
        }
        if(curr->visited == false){
            curr->visited = true;
            for(auto node : graph.getNeighbors(curr)){
                node->setColor(GRAY);
                tmpPath.push_back(node);
            }
        }
    }*/

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    queue<Vertex*> tmpQ;
    double infinity = numeric_limits<int>::max();

    for(auto node : graph.getNodeSet()){
        node->cost = infinity;
    }

    start->cost = 0;
    tmpQ.push(start);

    while(!tmpQ.empty()){
        Node *curr = tmpQ.front();
        tmpQ.pop();
        curr->setColor(GREEN);
        if(graph.compare(curr, end) == 0){
            while(curr->previous != nullptr){
                path.push_back(curr);
                curr = curr->previous;
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            for(auto node : graph.getNodeSet()){
                node->previous = nullptr;
                node->cost = 0;
            }
            break;

        }
        for(auto neighbour : graph.getNeighbors(curr)){
            if(neighbour->cost == infinity){
                neighbour->cost = curr->cost + 1;
                neighbour->previous = curr;
                neighbour->setColor(YELLOW);
                tmpQ.push(neighbour);
            }
        }
    }
    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    PriorityQueue<Node *> que;
    double infinity = numeric_limits<int>::max();

    for(auto vertex : graph.getVertexSet()){
        if(graph.compare(start, vertex) != 0){
            vertex->cost = infinity;
        }
        que.enqueue(vertex, vertex->cost);
    }

    while(!que.isEmpty()){
        Vertex *u = que.dequeue();
        u->setColor(GREEN);

        if(graph.compare(u, end) == 0){
            while(u->previous != nullptr){
                path.push_back(u);
                u = u->previous;
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            for(auto node : graph.getNodeSet()){
                node->previous = nullptr;
                node->cost = 0;
            }
            break;
        }
        for(auto neighbour : graph.getNeighbors(u)){
            double altDist = u->cost + (graph.getEdge(u, neighbour)->cost);
            if(altDist < neighbour->cost){
                neighbour->setColor(YELLOW);
                neighbour->cost = altDist;
                neighbour->previous = u;
                que.changePriority(neighbour, altDist);
            }
        }
    }
    que.clear();
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    Set<Vertex*> closed;    //Already evaluated
    Set<Vertex*> open;  //Still to be evaluated
    double infinity = numeric_limits<int>::max();

    open.add(start);

    map<Vertex*, double> gScore;    //start->Vertex *v cost
    map<Vertex*, double> fScore; //start->Vertex *v->end cost

    for(auto node : graph.getNodeSet()){
        gScore[node] = infinity;
        fScore[node] = infinity;
    }

    gScore[start] = 0;
    fScore[start] = start->heuristic(end);

    while(!open.isEmpty()){
        break;
    }
    return path;
}

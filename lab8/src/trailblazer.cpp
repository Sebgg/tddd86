// Comment header goes here

#include "costs.h"
#include "trailblazer.h"
#include "pqueue.h"
#include <queue>
#include <stack>
#include <set>
#include <limits>
#include <algorithm>


using namespace std;

bool hasFreeNeighbour(const BasicGraph &graph, Node *curr);
/*
 * An iterative implementation of Depth First Search for path to target node.
 */
vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    stack<Vertex*> nodeStack;
    nodeStack.push(start);

    start->cost = 0;
    while(!nodeStack.empty()){
        Vertex *curr = nodeStack.top();
        nodeStack.pop();
        curr->setColor(GREEN);
        if(graph.compare(curr, end) == 0){
            path.push_back(curr);
            break;
        }
        if(!curr->visited){
            curr->visited = true;
            path.push_back(curr);
            for(auto neighbour : graph.getNeighbors(curr)){
                if(!neighbour->visited){
                    neighbour->cost = 1;
                    neighbour->previous = curr;
                    nodeStack.push(neighbour);
                }
            }
        }
        if(!hasFreeNeighbour(graph, curr)){
            curr->setColor(GRAY);
            nodeStack.push(curr->previous);
            path.pop_back();
        }
    }
    while(!nodeStack.empty()){
        nodeStack.pop();
        // ERRORS ONLY PRESENT WHEN RUNNING DPS ON MAZE 10
// *** Error in `/home/hamer848/Documents/tddd86/build-Trailblazer-Desktop-Debug/Trailblazer': double free or corruption (out): 0x00000000085fc410 ***
/*
 ***
 *** STANFORD C++ LIBRARY
 *** An exception occurred during program execution:
 *** std::bad_alloc
 ***
*/
    }
    for(auto node : graph.getNodeSet()){
        node->previous = nullptr;
        node->visited = false;
        node->cost = 0;
    }
    return path;
}

/*
 * An iterative implmentation of Breadth First Search that finds a path to target node.
 */
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
            graph.resetData();
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

/*
 * Implementation of the Djikstra algorithm as pathfinding.
 */
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
            graph.resetData();
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

/*
 * Implementation of the A* algorithm.
 */
vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    PriorityQueue<Vertex*> open;        //Still to be evaluated
    double infinity = numeric_limits<int>::max();

    map<Vertex*, double> fScore;    //start->Vertex *v->end cost

    for(auto node : graph.getNodeSet()){
        node->cost= infinity;
        fScore[node] = infinity;
        open.enqueue(node, node->cost);
    }

    start->cost = 0;
    fScore[start] = start->heuristic(end);
    open.enqueue(start, start->cost);

    while(!open.isEmpty()){
        Node* curr = open.dequeue();
        curr->setColor(GREEN);
        if(graph.compare(curr, end) == 0){
            while(curr->previous != nullptr){
                path.push_back(curr);
                curr = curr->previous;
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            graph.resetData
            break;
        }
        curr->visited = true;
        for(auto neighbour : graph.getNeighbors(curr)){
            if(!neighbour->visited){
                double altG = curr->cost + curr->heuristic(neighbour);
                if(altG < neighbour->cost){
                    neighbour->setColor(YELLOW);
                    neighbour->previous = curr;
                    neighbour->cost = altG;
                    fScore[neighbour] = altG + neighbour->heuristic(end);
                    open.changePriority(neighbour, fScore[neighbour]);
                }
            }
        }
    }
    return path;
}

bool hasFreeNeighbour(const BasicGraph &graph, Node* curr ) {
    for(auto neighbour : graph.getNeighbors(curr)){
        if(!neighbour->visited){
            return true;
        }
    }
    return false;
}

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <deque>
#include <queue>
#include <math.h>

const long INF = 10000000000000;
typedef std::pair<long, long> point;
typedef std::pair<long, long> longPoint;

class SetNode {
    public:
    long rank;
    long id;
    SetNode* parent;

    SetNode(long id);
};
class DisjolongSet {
    public:
    std::vector<SetNode*> idToNode;

    long find(long x);
    bool setsEqual(long x, long y);
    void unionSet(long x, long y);
};
SetNode::SetNode(long id) {
    this->rank = 0;
    this->id = id;
    this->parent = this;
}
long DisjolongSet::find(long x) {
    if (idToNode[x]->parent != idToNode[x])
        idToNode[x]->parent = idToNode[find(idToNode[x]->parent->id)];

    return idToNode[x]->parent->id;
}
bool DisjolongSet::setsEqual(long x, long y) {
    return find(idToNode[x]->id) == find(idToNode[y]->id);
}
void DisjolongSet::unionSet(long x, long y) {
    SetNode* nodeX = idToNode[find(idToNode[x]->id)];
    SetNode* nodeY = idToNode[find(idToNode[y]->id)];

    if (nodeX->rank > nodeY->rank) {
        nodeY->parent = nodeX;
    }
    else {
        nodeX->parent = nodeY;

        if (nodeX->rank == nodeY->rank) nodeY->rank++;
    }
}

class Vertex {
    public:
    long value;

    // Maps vertex ID to edge weight
    std::vector<std::pair<long, long>> edges;

    Vertex(long _value) {
        this->value = _value;

        edges = std::vector<std::pair<long, long>>();
    }
};

class Graph {
    public:
    std::vector<Vertex*> vertices;

    Graph();
};

Graph::Graph() {
    vertices = std::vector<Vertex*>();
}

struct EdgeComparator {
    bool operator()(const std::pair<long, std::pair<long, long>>& a, const std::pair<long, std::pair<long, long>>& b) const {
        return a.first > b.first;
    }
};

void modifiedMSTKruskal(Graph* graph, std::vector<bool> insecure) {
    DisjolongSet set;

    long size = graph->vertices.size();

    set.idToNode = std::vector<SetNode*>(size);

    //Stores a list of (w, u, v)
    std::priority_queue<std::pair<long, std::pair<long, long>>, std::vector<std::pair<long, std::pair<long, long>>>, EdgeComparator> edges;

    std::vector<std::pair<long, std::pair<long, long>>> MST;

    for (long i = 0; i < size; i++)
        set.idToNode[i] = new SetNode(i);
            
    for (long i = 0; i < size; i++) {
        if (insecure[i]) continue;

        for (long j = 0; j < graph->vertices[i]->edges.size(); j++) {
            std::pair<long, long> currEdge = graph->vertices[i]->edges[j];

            if (insecure[currEdge.first]) continue;

            edges.push({currEdge.second, {i, currEdge.first}});
        }
    }

    //Handle the rest
    while (!edges.empty()) {
        std::pair<long, std::pair<long, long>> currEdge = edges.top();
        edges.pop();

        if (set.find(currEdge.second.first) != set.find(currEdge.second.second)) {
            MST.push_back(currEdge);

            set.unionSet(currEdge.second.first, currEdge.second.second);
        }
    }

    for (long i = 0; i < size; i++) {
        //Only look at insecure nodes
        if (!insecure[i]) continue;

        std::pair<long, long> minEdge;
        long minWeight = INF;

        for (long j = 0; j < graph->vertices[i]->edges.size(); j++) {
            std::pair<long, long> currEdge = graph->vertices[i]->edges[j];

            if (insecure[currEdge.first]) continue;

            if (currEdge.second < minWeight) {
                minWeight = currEdge.second;
                minEdge = currEdge;
            }
        }

        if (minWeight != INF && set.find(i) != set.find(minEdge.first)) {
            MST.push_back({minWeight, {i, minEdge.first}});

            set.unionSet(i, minEdge.first);
        }
    }

    for (long i = 0; i < size; i++) {
        //Only look at insecure nodes
        if (!insecure[i]) continue;

        std::pair<long, long> minEdge;
        long minWeight = INF;

        bool allInsecure = true;
        for (long j = 0; j < graph->vertices[i]->edges.size(); j++) {
            std::pair<long, long> currEdge = graph->vertices[i]->edges[j];

            //If both nodes are insecure
            if (!insecure[currEdge.first]) allInsecure = false;

            if (insecure[currEdge.first] && currEdge.second < minWeight) {
                minWeight = currEdge.second;
                minEdge = currEdge;
            }
        }

        for (long j = 0; j < graph->vertices[minEdge.first]->edges.size(); j++) {
            std::pair<long, long> currEdge = graph->vertices[minEdge.first]->edges[j];

            //If both nodes are insecure
            if (!insecure[currEdge.first]) allInsecure = false;

            if (insecure[currEdge.first] && currEdge.second < minWeight) {
                minWeight = currEdge.second;
                minEdge = currEdge;
            }
        }

        if (allInsecure && minWeight != INF && set.find(i) != set.find(minEdge.first)) {
            MST.push_back({minWeight, {i, minEdge.first}});

            set.unionSet(i, minEdge.first);
        }
    }

    long initFind = set.find(0);
    for (int i = 1; i < graph->vertices.size(); i++) {
        if (set.find(i) != initFind) {
            std::cout << "impossible" << std::endl;
            return;
        }
    }

    long cost = 0;
    for (int i = 0; i < MST.size(); i++)
        cost += MST[i].first;

    std::cout << cost << std::endl;
}

int main() {
    int numBuildings, numConnections, numInsecure;
    std::cin >> numBuildings >> numConnections >> numInsecure;
    
    std::vector<bool> insecure(numBuildings, false);

    for (int i = 0; i < numInsecure; i++) {
        int val;
        std::cin >> val;

        insecure[val - 1] = true;
    }

    Graph* graph = new Graph();

    for (long i = 0; i < numBuildings; i++) {
        graph->vertices.push_back(new Vertex(i));
    }

    for (long i = 0; i < numConnections; i++) {
        long u, v, w;
        std::cin >> u >> v >> w;

        Vertex* vU = graph->vertices[u - 1];
        Vertex* vV = graph->vertices[v - 1];

        vU->edges.push_back(std::pair<long, long>(v - 1, w));
        vV->edges.push_back(std::pair<long, long>(u - 1, w));
    }

    //start the minimum spanning tree algorihm with the insecure edges to make sure they're all connected..?
    modifiedMSTKruskal(graph, insecure);
}
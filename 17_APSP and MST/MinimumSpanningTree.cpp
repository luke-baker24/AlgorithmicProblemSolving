#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <deque>
#include <queue>

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

    // For pathfinding
    long d;
    long pi;

    Vertex(long _value);
};

Vertex::Vertex(long _value) {
    this->value = _value;

    this->pi = -1;
    this->d = 1000000000;
}

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

struct PolongComparator {
    bool operator()(const std::pair<long, long>& a, const std::pair<long, long>& b) const {
        return a.first > b.first || a.first == b.first && a.second > b.second;
    }
};

std::vector<std::pair<long, std::pair<long, long>>> mstKruskal(Graph* graph) {
    DisjolongSet set;

    long size = graph->vertices.size();

    set.idToNode = std::vector<SetNode*>(size);

    //Stores a list of (w, u, v)
    std::priority_queue<std::pair<long, std::pair<long, long>>, std::vector<std::pair<long, std::pair<long, long>>>, EdgeComparator> edges;

    for (long i = 0; i < size; i++) {
        set.idToNode[i] = new SetNode(i);

        for (long j = 0; j < graph->vertices[i]->edges.size(); j++) {
            std::pair<long, long> currEdge = graph->vertices[i]->edges[j];

            edges.push({currEdge.second, {i, currEdge.first}});
        }
    }

    std::vector<std::pair<long, std::pair<long, long>>> MST;

    while (!edges.empty()) {
        std::pair<long, std::pair<long, long>> currEdge = edges.top();
        edges.pop();

        if (set.find(currEdge.second.first) != set.find(currEdge.second.second)) {
            MST.push_back(currEdge);

            set.unionSet(currEdge.second.first, currEdge.second.second);
        }
    }

    long initFind = set.find(0);
    for (long i = 1; i < graph->vertices.size(); i++) {
        if (set.find(i) != initFind) return std::vector<std::pair<long, std::pair<long, long>>>();
    }

    return MST;
}

int main() {
    while (true) {
        long nodes, edges;
        std::cin >> nodes >> edges;

        if (nodes == 0 && edges == 0) break;

        Graph* graph = new Graph();

        for (long i = 0; i < nodes; i++) {
            graph->vertices.push_back(new Vertex(i));
        }

        for (long i = 0; i < edges; i++) {
            long u, v, w;
            std::cin >> u >> v >> w;

            graph->vertices[u]->edges.push_back(std::pair<long, long>(v, w));
            graph->vertices[v]->edges.push_back(std::pair<long, long>(u, w));
        }

        std::vector<std::pair<long, std::pair<long, long>>> MST = mstKruskal(graph);

        long cost = 0;
        for (long i = 0; i < MST.size(); i++) {
            cost += MST[i].first;
        }

        if (MST.size() == 0) {
            std::cout << "Impossible" << std::endl;
        }
        else {
            std::cout << cost << std::endl;

            std::priority_queue<std::pair<long, long>, std::vector<std::pair<long, long>>, PolongComparator> edgeQueue;

            for (long i = 0; i < MST.size(); i++) {
                if (MST[i].second.first < MST[i].second.second)  
                    edgeQueue.push(MST[i].second);
                else
                    edgeQueue.push({MST[i].second.second, MST[i].second.first});
            }

            while (!edgeQueue.empty()) {
                std::pair<long, long> edge = edgeQueue.top();
                edgeQueue.pop();

                std::cout << edge.first << " " << edge.second << std::endl;
            }
        }
    }
}
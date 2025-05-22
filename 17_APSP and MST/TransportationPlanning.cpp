#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <deque>
#include <queue>
#include <math.h>

const double INF = 10000000000000;
typedef std::pair<long, long> point;
typedef std::pair<double, double> doublePoint;

double distance(point inOne, point inTwo) {
    doublePoint one = {inOne.first, inOne.second};
    doublePoint two = {inTwo.first, inTwo.second};

    double val = sqrt((two.first - one.first) * (two.first - one.first) + (two.second - one.second) * (two.second - one.second));
    return val;
}

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
    std::vector<std::pair<long, double>> edges;

    long x, y;

    Vertex(long _value, long _x, long _y) {
        this->value = _value;

        this->x = _x;
        this->y = _y;
    }

    point getPoint() {
        return point(x, y);
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
    bool operator()(const std::pair<double, std::pair<long, long>>& a, const std::pair<double, std::pair<long, long>>& b) const {
        return a.first > b.first;
    }
};

std::vector<std::pair<double, std::pair<long, long>>> mstKruskal(Graph* graph) {
    DisjolongSet set;

    long size = graph->vertices.size();

    set.idToNode = std::vector<SetNode*>(size);

    //Stores a list of (w, u, v)
    std::priority_queue<std::pair<double, std::pair<long, long>>, std::vector<std::pair<double, std::pair<long, long>>>, EdgeComparator> edges;

    for (long i = 0; i < size; i++) {
        set.idToNode[i] = new SetNode(i);

        for (long j = 0; j < graph->vertices[i]->edges.size(); j++) {
            std::pair<long, double> currEdge = graph->vertices[i]->edges[j];

            edges.push({currEdge.second, {i, currEdge.first}});
        }
    }

    std::vector<std::pair<double, std::pair<long, long>>> MST;

    while (!edges.empty()) {
        std::pair<double, std::pair<long, long>> currEdge = edges.top();
        edges.pop();

        if (set.find(currEdge.second.first) != set.find(currEdge.second.second)) {
            MST.push_back(currEdge);

            set.unionSet(currEdge.second.first, currEdge.second.second);
        }
    }

    return MST;
}

std::vector<std::vector<double>> floydWarshall(Graph* graph) {
    std::vector<std::vector<double>> matrix(graph->vertices.size());

    for (int i = 0; i < graph->vertices.size(); i++) {
        for (int j = 0; j < graph->vertices.size(); j++) {
            matrix[i].push_back(INF);
        }
    }

    for (int i = 0; i < graph->vertices.size(); i++) {
        for (int j = 0; j < graph->vertices[i]->edges.size(); j++) {
            std::pair<long, double> edge = graph->vertices[i]->edges[j];

            matrix[i][edge.first] = edge.second;
        }
    }

    for (int k = 0; k < graph->vertices.size(); k++) {
        for (int i = 0; i < graph->vertices.size(); i++) {
            for (int j = 0; j < graph->vertices.size(); j++) {
                matrix[i][j] = std::min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }
    }

    return matrix;
}

double getTotalCost(Graph* graph) {
    std::vector<std::vector<double>> matrix = floydWarshall(graph);

    double cost = 0;

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = i + 1; j < matrix.size(); j++) {
            cost += matrix[i][j];
        }
    }

    return cost;
}

int main() {
    while (true) {
        long nodes;
        std::cin >> nodes;

        if (nodes == 0) break;

        Graph* graph = new Graph();

        for (long i = 0; i < nodes; i++) {
            long x, y;
            std::cin >> x >> y;

            graph->vertices.push_back(new Vertex(i, x, y));
        }

        long edges;
        std::cin >> edges;

        for (long i = 0; i < edges; i++) {
            long u, v;
            std::cin >> u >> v;

            Vertex* vU = graph->vertices[u];
            Vertex* vV = graph->vertices[v];

            double w = distance(vU->getPoint(), vV->getPoint());

            vU->edges.push_back(std::pair<long, double>(v, w));
            vV->edges.push_back(std::pair<long, double>(u, w));
        }

        double baseCost = getTotalCost(graph);

        // std::cout << "Base cost " << baseCost << std::endl;
        
        // we need to find cost as the minimum sum of all distances.

        double minCost = baseCost;
        long minU = -1, minV = -1;
        for (long u = 0; u < nodes; u++) {
            for (long v = u + 1; v < nodes; v++) {
                Vertex* vU = graph->vertices[u];
                Vertex* vV = graph->vertices[v];

                double w = distance(vU->getPoint(), vV->getPoint());

                vU->edges.push_back(std::pair<long, double>(v, w));
                vV->edges.push_back(std::pair<long, double>(u, w));

                double testCost = getTotalCost(graph);

                if (testCost < minCost) {
                    minCost = testCost;

                    minU = u;
                    minV = v;
                }

                vU->edges.pop_back();
                vV->edges.pop_back();
            }
        }

        if (minU == -1 && minV == -1) {
            std::cout << "no addition reduces " << baseCost << std::endl;
        }
        else if (minU < minV) {
            std::cout << "adding " << minU << " " << minV << " reduces " << baseCost << " to " << minCost << std::endl;
        }
        else {
            std::cout << "adding " << minV << " " << minU << " reduces " << baseCost << " to " << minCost << std::endl;
        }
    }
}
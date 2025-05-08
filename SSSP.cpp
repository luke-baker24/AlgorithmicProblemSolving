#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

class Vertex {
    public:
    int value;
    std::unordered_map<Vertex*, int> edges;

    //For pathfinding
    long d;
    Vertex* pi;

    Vertex(int value) {
        this->value = value;
        this->pi = nullptr;
    }
};

class Graph {
    public:
    std::vector<Vertex> vertices;

    Graph() {
        vertices = std::vector<Vertex>();
    }
};

/*std::vector<Vertex> topoSort(Graph graph, Vertex start) {
    std::unordered_map<Vertex, bool> visited;


}*/

//Pseduocode for Single-Source Shortest Path (SSSP) algorithms

//Initialize shortest path estimates and predecessors 
//for directed graph G and source vertex s

// INITIALIZE-SINGLE-SOURCE(G, s)
// 	for each vertex v in G.V
// 		v.d = inf
// 		v.pi = null
// 	s.d = 0

void initializeSingleSource(Graph graph, Vertex* start) {
    for (int i = 0; i < graph.vertices.size(); i++) {
        graph.vertices[i].d = 10000000;
        graph.vertices[i].pi = nullptr;
    }
}


//Relax the edge from u to v,
//updating v's shortest path estimate and predecessor
//if travelling through u gives a shorter path.

// RELAX(u, v)
// 	if v.d > u.d + w(u, v)
// 		v.d = u.d + w(u, v)
// 		v.pi = u

void relax(Vertex* u, Vertex* v) {
    if (v->d > u->d + u->edges.at(v)) {
        v->d = u->d + u->edges.at(v);
        v->pi = u;
    }
}

/*Runs the Bellman-Ford algorithm to compute all SSSP distances
# for directed graph G and source vertex s.
# If there are no negative-weight cycles reachable from s,
# the algorithm returns True and v.d = weight of shortest path from s to v.
# If there is a negative-weight cycle reachable from s,
# the algorithm returns False.
*/

// BELLMAN-FORD(G, s)
// 	INITIALIZE-SINGLE-SOURCE(G, s)
// 	for i = 1 to |G.V|-1			# |V|-1 iterations
// 		for each edge (u, v) in G.E
// 			RELAX(u, v)
// 	for each edge (u, v) in G.E
// 		if v.d > u.d + w(u, v)
// 			return FALSE
// 	return TRUE

bool bellmanFord(Graph g, Vertex* s) {
    initializeSingleSource(g, s);

    for (int i = 0; i < g.vertices.size() - 1; i++) {
        for (int j = 0; j < g.vertices.size(); j++) {
            for (const auto& entry : g.vertices[j].edges) {
                relax(&g.vertices[j], entry.first);
            }
        }
    }

    for (int j = 0; j < g.vertices.size(); j++) {
        for (const auto& entry : g.vertices[j].edges) {
            if (entry.first->d > g.vertices[j].d + entry.second) return false;
        }
    }
    
    return true;
}


//Computes SSSP distances from s to all other vertices in a
//directed acyclic graph.

// DAG-SHORTEST-PATHS(G, s)
// 	topologically sort G.V 
// 	INITIALIZE-SINGLE-SOURCE(G, s)
// 	for each vertex u in topologically sorted order
// 		for each vertex v adjacent to u (looping edges (u, v))
// 			RELAX(u, v)	

// void dagShortestPaths(Graph g, Vertex s) {
//     std::vector<Vertex> sortedGraph;

//     //sortedGraph = topoSort(g, s);

//     for (const auto& u : sortedGraph) {
//         for (const auto& v : u.edges) {
//             relax(u, v.first);
//         }
//     }
// }

/*Runs Dijkstra's algorithms to compute all SSSP distances
# for directed graph G and source vertex s.
# G must not contain any negative-weight edges, but it may
# contain cycles.
*/

// DIJKSTRA(G, s)
// 	INITIALIZE-SINGLE-SOURCE(G, s)
// 	S = empty set
// 	Q = G.V 		# min priority queue containing all vertices
// 	while Q is not empty
// 		u = EXTRACT-MIN(Q)
// 		add u to S 
// 		for each vertex v adjacent to u  (for all edges (u, v))
// 			RELAX(u, v)

void dijkstra(Graph g, Vertex* s) {
    initializeSingleSource(g, s);

    std::unordered_set<Vertex> S;
    
}


/*Prints the shortest path from source vertex s to vertex v in
# directed graph G.
# Assumes a SSSP algorithm has already terminated.
*/

// PRINT-PATH(G, s, v)
// 	if v == s
// 		print s
// 	else if v.pi == null
// 		print "no path from s to v"
// 	else
// 		PRINT-PATH(G, s, v.pi)
// 		print v

void printPath(Graph g, Vertex* s, Vertex* v) {
    if (s == v)  {
        std::cout << s->value << std::endl;
    }
    else if (v->pi == nullptr) {
        std::cout << "Impossible" << std::endl;
    }
    else {
        printPath(g, s, v->pi);
    }
}

int main() {
    while (true) {
        int nodes, edges, queries, s;
        std::cin >> nodes >> edges >> queries >> s;

        //End case
        if (nodes == 0 && edges == 0 && queries == 0 && s == 0) break;

        Graph graph;

        for (int i = 0; i < nodes; i++) {
            graph.vertices.push_back(Vertex(i));
        }

        for (int i = 0; i < edges; i++) {
            int u, v, w;
            std::cin >> u >> v >> w;

            graph.vertices[u].edges.insert({&graph.vertices[v], w});
        }

        //bellmanFord(graph, &graph.vertices[s]);

        for (int i = 0; i < queries; i++) {
            int q;
            std::cin >> q;

            printPath(graph, &graph.vertices[s], &graph.vertices[q]);
        }
    }
}
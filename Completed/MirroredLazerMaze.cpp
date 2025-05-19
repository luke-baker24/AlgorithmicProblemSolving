#include <iostream>
#include <vector>

class Node {
    public:
    int connects[4] = { 0, 0, 0, 0 };
    int visited = 0;

    int minMirrors = 1000000;

    Node() {

    }
};

int customMin(int one, int two) {
    if (one >= 0 && two >= 0) return std::min(one, two);
    else if (two >= 0) return two;
    else if (one >= 0) return one;
    else return std::min(one, two);
}

std::vector<std::vector<Node>> graph;

std::vector<std::pair<int, int>> directions = {
    {0, 1},   // east
    {-1, 0},  // north
    {1, 0},   // south
    {0, -1}   // west
};

int DFS(std::pair<int, int> source, std::pair<int, int> target, int currDir);

int checkDir(std::pair<int, int> source, std::pair<int, int> target, int currDir, int dir) {
    return graph[source.first][source.second].connects[dir] == 1 && 
        graph[source.first + directions[dir].first][source.second + directions[dir].second].visited == 0 ? 
            (currDir == dir ? 0 : 1) + DFS({source.first + directions[dir].first, source.second + directions[dir].second}, target, dir) : 
            -1000000;
}

int DFS(std::pair<int, int> source, std::pair<int, int> target, int currDir) {
    graph[source.first][source.second].visited = 1;
    
    //we found the target, return
    if (source.first == target.first && source.second == target.second)
        return 0;

    int out = checkDir(source, target, currDir, currDir);

    for (int i = 0; i < 4; i++) {
        if (i == currDir || i == (3 - currDir)) continue;

        out = customMin(out, checkDir(source, target, currDir, i));
    }

    return out;
}

int main() {
    int r, c;
    std::cin >> r >> c;

    std::vector<std::vector<char>> input(r, std::vector<char>(c));
    graph.resize(r, std::vector<Node>(c));

    std::pair<int, int> source;
    std::pair<int, int> target;

    for (int i = 0; i < r; i++) {
        std::string next;
        std::cin >> next;

        for (int j = 0; j < c; j++)
            input[i][j] = next[j];
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (input[i][j] != '#') graph[i][j] = Node();

            if (input[i][j] == 'S') source = {i, j};
            else if (input[i][j] == 'T') target = {i, j};
            
            if (input[i][j] == '#') continue;

            if (j < c - 1 && input[i][j + 1] != '#') 
                graph[i][j].connects[0] = 1;
            if (i > 0 && input[i - 1][j] != '#') 
                graph[i][j].connects[1] = 1;
            if (i < r - 1 && input[i + 1][j] != '#') 
                graph[i][j].connects[2] = 1;
            if (j > 0 && input[i][j - 1] != '#') 
                graph[i][j].connects[3] = 1;
        }
    }

    int mirrors = customMin(customMin(DFS(source, target, 0), DFS(source, target, 1)), 
                            customMin(DFS(source, target, 2), DFS(source, target, 3)));

    std::cout << (mirrors < 0 ? -1 : mirrors) << std::endl;
}
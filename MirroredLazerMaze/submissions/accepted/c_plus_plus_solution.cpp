#include <iostream>
#include <vector>
#include <queue>

const std::vector<std::pair<int, int>> directions = {
    {-1, 0},  // north
    {0, 1},   // east
    {1, 0},   // south
    {0, -1}   // west
};

const std::vector<int> slashMirror = { 1, 0, 3, 2 };
const std::vector<int> backMirror = { 3, 2, 1, 0 };

std::vector<std::vector<char>> input;
std::vector<std::vector<std::vector<int>>> minMirrors;

bool inBounds(int r, int c) {
    return r >= 0 && r < input.size() && c >= 0 && c < input[0].size();
}

int BFS(std::pair<int, int> source, std::pair<int, int> target) {
    std::deque<std::vector<int>> Q;

    for (int dir = 0; dir < 4; dir++) {
        minMirrors[source.first][source.second][dir] = 0;
        Q.push_front({source.first, source.second, dir});
    }

    while (!Q.empty()) {
        std::vector<int> curr = Q.front();
        Q.pop_front();

        int currDir = curr[2];
        std::pair<int, int> currPoint = {curr[0], curr[1]};

        if (input[currPoint.first][currPoint.second] == '#')
            continue;

        int cost = minMirrors[currPoint.first][currPoint.second][currDir];

        // We found the target, return
        if (currPoint.first == target.first && currPoint.second == target.second && cost < 100000) {
            return minMirrors[currPoint.first][currPoint.second][currDir];
        }

        int straightC = currPoint.second + directions[currDir].second;
        int straightR = currPoint.first + directions[currDir].first;  

        //Check if we can go straight
        if (inBounds(straightR, straightC) && input[straightR][straightC] != '#') {
            int newCost = minMirrors[straightR][straightC][currDir];

            if (cost < newCost) {
                minMirrors[straightR][straightC][currDir] = cost;

                Q.push_front({straightR, straightC, currDir});
            }
        }

        if (input[currPoint.first][currPoint.second] != '.')
            continue;

        //Check slash mirror
        int slashDir = slashMirror[currDir];

        int slashC = currPoint.second + directions[slashDir].second;
        int slashR = currPoint.first + directions[slashDir].first;

        if (inBounds(slashR, slashC) && input[slashR][slashC] != '#') {
            int newCost = minMirrors[slashR][slashC][slashDir];

            if (cost + 1 < newCost) {
                minMirrors[slashR][slashC][slashDir] = cost + 1;

                Q.push_back({slashR, slashC, slashDir});
            }
        }
                
        //Check backslash mirror
        int backSlashDir = backMirror[currDir];

        int backSlashC = currPoint.second + directions[backSlashDir].second;
        int backSlashR = currPoint.first + directions[backSlashDir].first;
        
        if (inBounds(backSlashR, backSlashC) && input[backSlashR][backSlashC] != '#') {
            int newCost = minMirrors[backSlashR][backSlashC][backSlashDir];

            if (cost + 1 < newCost) {
                minMirrors[backSlashR][backSlashC][backSlashDir] = cost + 1;

                Q.push_back({backSlashR, backSlashC, backSlashDir});
            }
        }
    }

    return -1;
}

int main() {
    int r, c;
    std::cin >> r >> c;

    std::pair<int, int> source;
    std::pair<int, int> target;

    input = std::vector<std::vector<char>>(r, std::vector<char>(c));

    for (int i = 0; i < r; i++) {
        std::string next;
        std::cin >> next;

        for (int j = 0; j < c; j++)
            input[i][j] = next[j];
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (input[i][j] == 'S') source = {i, j};
            else if (input[i][j] == 'T') target = {i, j};
        }
    }

    minMirrors = std::vector<std::vector<std::vector<int>>>(r, std::vector<std::vector<int>>(c, std::vector<int>(4, 100000)));

    std::cout << BFS(source, target) << std::endl;
}
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>

class SetNode {
    public:
    int rank;
    int id;
    SetNode* parent;

    SetNode(int id);
};

class DisjointSet {
    public:
    std::vector<SetNode*> idToNode;

    long find(long x);
    bool setsEqual(long x, long y);
    void unionSet(long x, long y);
};

SetNode::SetNode(int id) {
    this->rank = 0;
    this->id = id;
    this->parent = this;
}

long DisjointSet::find(long x) {
    if (idToNode[x]->parent != idToNode[x])
        idToNode[x]->parent = idToNode[find(idToNode[x]->parent->id)];

    return idToNode[x]->parent->id;
}

bool DisjointSet::setsEqual(long x, long y) {
    return find(idToNode[x]->id) == find(idToNode[y]->id);
}

void DisjointSet::unionSet(long x, long y) {
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

//I'm feeling disjoint-set union-find here.
//Have a hashmap that translates words into integers, which key into a disjoint set.
//Equivalence declararations union all the sets.

//A translation is valid if for every word, the finds are equal

int main() {
    std::string line;

    std::unordered_map<std::string, int> map;
    DisjointSet set;

    bool readingIn = true;

    std::vector<std::vector<int>> lines;

    while (std::getline(std::cin, line)) {
        if (readingIn) {
            if (line == "") {
                readingIn = false;
                continue;
            }

            if (line[0] == '=') {
                std::stringstream stream(line);

                std::string token;

                std::vector<std::string> words;

                while (std::getline(stream, token, ' ')) {
                    if (token == "=") continue; 

                    words.push_back(token);
                }

                if (words.size() == 1) continue;

                for (int i = 1; i < words.size(); i++) {
                    set.unionSet(map[words[i - 1]], map[words[i]]);
                }
            }
            else {
                std::stringstream stream(line);

                std::string token;

                lines.push_back(std::vector<int>());

                while (std::getline(stream, token, ' ')) {
                    //if the key is already in the arr
                    if (map.find(token) == map.end()) {
                        int idx = set.idToNode.size();

                        map[token] = idx;

                        set.idToNode.push_back(new SetNode(idx));

                        lines[lines.size() - 1].push_back(idx);
                    }
                }
            }
        }
        else {
            std::stringstream stream(line);

            std::string token;

            lines.push_back(std::vector<int>());

            while (std::getline(stream, token, ' ')) {
                //if the key is already in the arr
                if (map.find(token) == map.end()) {
                    int idx = set.idToNode.size();

                    map[token] = idx;

                    lines[lines.size() - 1].push_back(idx);
                }
            }
        }
    }
}
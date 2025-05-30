#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

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

std::unordered_map<std::string, int> map;
DisjointSet set;

void putInMap(std::string token) {
    if (map.find(token) == map.end()) {
        int idx = set.idToNode.size();

        map[token] = idx;

        set.idToNode.push_back(new SetNode(idx));
    }
}

int main() {
    //Handling I/O
    std::vector<std::string> sourceLines;
    std::vector<std::string> queryLines;

    int sourceLineCt = 0;

    std::string line;
    
    int firstChunkLines;
    std::cin >> firstChunkLines;
    std::getline(std::cin, line);


    for (int i = 0; i < firstChunkLines; i++) {
        std::getline(std::cin, line);

        if (line[0] != '=') sourceLineCt++;

        sourceLines.push_back(line);
    }

    std::getline(std::cin, line);
    // std::getline(std::cin, line);

    for (int i = 0; i < sourceLineCt; i++) {
        std::getline(std::cin, line);

        queryLines.push_back(line);
    }

    //Actually processing the values
    int sourceIndex = 0;
    
    for (int queryIndex = 0; queryIndex < queryLines.size(); queryIndex++) {  
        //Handle next equivalence lines
        while (sourceLines[sourceIndex][0] == '=') {
            std::stringstream equalStream(sourceLines[sourceIndex]);

            std::vector<std::string> words;

            std::string token;

            //Skip the equals sign
            while (!equalStream.eof()) {
                std::getline(equalStream, token, ' ');

                token.erase(std::remove(token.begin(), token.end(), '\n'), token.end());
                token.erase(std::remove(token.begin(), token.end(), '\r'), token.end());

                putInMap(token);

                words.push_back(token);
            }

            for (int i = 1; i < words.size(); i++) {
                set.unionSet(map[words[i - 1]], map[words[i]]);
            }
            
            sourceIndex++;
        }

        //Handle the source line
        std::stringstream sourceStream(sourceLines[sourceIndex]);
        std::stringstream queryStream(queryLines[queryIndex]);

        bool couldBe = true;
        
        // std::cerr << "Source: " << sourceLines[sourceIndex] << std::endl;
        // std::cerr << "Query: " << queryLines[queryIndex] << std::endl;

        //Get rid of the equals sign
        std::string checkToken;        
        std::string token;
        while (!(queryStream.eof() || sourceStream.eof())) {            
            std::getline(queryStream, checkToken, ' ');
            std::getline(sourceStream, token, ' ');
            
            checkToken.erase(std::remove(checkToken.begin(), checkToken.end(), '\n'), checkToken.end());
            checkToken.erase(std::remove(checkToken.begin(), checkToken.end(), '\r'), checkToken.end());
            
            token.erase(std::remove(token.begin(), token.end(), '\n'), token.end());
            token.erase(std::remove(token.begin(), token.end(), '\r'), token.end());

            //if the key is not in the arr
            putInMap(token);
            putInMap(checkToken);

            // std::cerr << token << " " << checkToken << std::endl;
            // std::cerr << map[token] << " " << map[checkToken] << std::endl;
            
            if (set.find(map[token]) != set.find(map[checkToken]) || 
                queryStream.eof() && !sourceStream.eof() || 
                !queryStream.eof() && sourceStream.eof()) couldBe = false;
        }

        //Check if we're chillin
        if (couldBe) std::cout << "Could be!" << std::endl;
        else std::cout << "Could not be!" << std::endl;

        //Making sure we somehow don't overflow
        sourceIndex++;
    }
}
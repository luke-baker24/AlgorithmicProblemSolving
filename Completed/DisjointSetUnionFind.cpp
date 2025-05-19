#include <iostream>
#include <vector>

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

    SetNode* find(SetNode* x);
    bool setsEqual(int x, int y);
    void unionSet(int x, int y);

    DisjointSet(int size);
};

SetNode::SetNode(int id) {
    this->rank = 0;
    this->id = id;
    this->parent = this;
}

SetNode* DisjointSet::find(SetNode* x) {
    if (x->parent != x)
        x->parent = find(x->parent);

    return x->parent;
}

bool DisjointSet::setsEqual(int x, int y) {
    return find(idToNode[x]) == find(idToNode[y]);
}

void DisjointSet::unionSet(int x, int y) {
    SetNode* nodeX = find(idToNode[x]);
    SetNode* nodeY = find(idToNode[y]);

    if (nodeX->rank > nodeY->rank) {
        nodeY->parent = nodeX;
    }
    else {
        nodeX->parent = nodeY;

        if (nodeX->rank == nodeY->rank) nodeY->rank++;
    }
}

DisjointSet::DisjointSet(int size) {
    idToNode = std::vector<SetNode*>(size);

    for (int i = 0; i < size; i++) {
        idToNode[i] = new SetNode(i);
    }
}

int main() {
    int setSize, testCases;

    std::cin >> setSize >> testCases;

    DisjointSet set = DisjointSet(setSize);
    
    for (int i = 0; i < testCases; i++) {
        char operation;
        std::cin >> operation;

        int val1, val2;
        std::cin >> val1 >> val2;

        if (operation == '?') {
            if (set.setsEqual(val1, val2)) std::cout << "yes" << std::endl;
            else std::cout << "no" << std::endl;
        }
        else {
            set.unionSet(val1, val2);
        }
    }
}
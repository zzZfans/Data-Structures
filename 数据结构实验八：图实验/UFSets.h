//
// Created by Zfans on 2019/11/11.
//

#ifndef GRAPHBYADJACENCYLIST_UFSETS_H
#define GRAPHBYADJACENCYLIST_UFSETS_H

class UFSets {
private:
    int *parent;
    int size;
public:
    explicit UFSets(int size = 1024);

    ~UFSets() {
        delete[] parent;
    }

    UFSets operator=(UFSets &R);

    void Union(int Root1, int Root2);

    int Find(int x);

    void WeightedUnion(int Root1, int Root2);
};

UFSets::UFSets(int size) {
    this->size = size;
    parent = new int[size];
    for (int i = 0; i < size; ++i) {
        parent[i] = -1;
    }
}

int UFSets::Find(int x) {
    while (parent[x] >= 0)
        x = parent[x];
    return x;
}

void UFSets::Union(int Root1, int Root2) {
    parent[Root1] += parent[Root2];
    parent[Root2] = Root1;
}

UFSets UFSets::operator=(UFSets &R) {
    for (int i = 0; i < size; ++i) {
        parent[i] = R.parent[i];
    }
    size = R.size;
}

void UFSets::WeightedUnion(int Root1, int Root2) {
    int r1 = Find(Root1), r2 = Find(Root2), temp;
    if (r1 != r2) {
        temp = parent[r1] + parent[r2];
        if (parent[r2] < parent[r1]) {
            parent[r1] = r2;
            parent[r2] = temp;
        } else {
            parent[r2] = r1;
            parent[r1] = temp;
        }
    }
}

#endif //GRAPHBYADJACENCYLIST_UFSETS_H

#ifndef SOCIALMEDIA_GRAPHOPERATIONS_H
#define SOCIALMEDIA_GRAPHOPERATIONS_H

#include "Graph.h"

struct Pair {
    Node *node;

    int weight;

    Pair(Node *node, int weight);

    bool operator<(const Pair &pair);
};

class GraphOperations {
    Graph *graph;

    bool contains(vector<string> &visited, string name);

    int getWeight(Node* user);

public:
    GraphOperations(Graph *graph);

    Graph *getGraph();

    Node *findUser(string name);

    Node *BFSGeneral(string name);

    Node *BFS(Node *node, string name, vector<string> &visited);

    vector<Pair *> DFSGeneral(Node *node);

    void DFS(Node *from, Friendship *to, vector<Pair *> &paths);

    vector<Friendship *> retrieveMutualFriendsFrom(Node *user);

    Pair *getPair(vector<Pair *> &path, string name);

    void
    addToMutualFriends(Node *node, vector<Friendship *> &currentMutualFriends, vector<Friendship *> &mutualFriends);

    void getFriendliestUsers(vector<Pair *> &suggestions, Node *user);
};


#endif //SOCIALMEDIA_GRAPHOPERATIONS_H

#ifndef SOCIALMEDIA_GRAPH_H
#define SOCIALMEDIA_GRAPH_H

#include <vector>
#include "User.h"
#include "Type.h"

class Node;

class Friendship {
    Node *userFriend;
    Type friendshipType;
public:
    Friendship(Node *user, Type friendship);

    Node *getUserFriend() const;

    Type getFriendshipType() const;

    ~Friendship();
};

struct Pair {
    Node *node;
    int weight;

    Pair(Node *node, int weight);

    bool operator<(const Pair &pair);
};

class Node {
    User *user;
    vector<Friendship *> friendships;

    void copy(const Node &other);

public:
    User *getUser() const;

    void setUser(User *user);

    vector<Friendship *> &getFriendships();

    void setFriendships(const vector<Friendship *> &friendships);

    bool containsFriend(string name);

    Node(User *user);

    Node &operator=(const Node &other);

    friend ostream &operator<<(ostream &oS, const Node &node);

    bool operator<(const Node &node);

    ~Node();
};


class Graph {
    vector<Node *> nodes;

public:
    vector<Node *> &getNodes();

    void setNodes(vector<Node *> nodes);

};

class GraphOperations {
    Graph *graph;

    bool contains(vector<string> &visited, string name);

public:
    GraphOperations(Graph *graph);

    bool userExists(string name);

    Graph *getGraph();

    Node *findUser(string name);

    Node *BFSGeneral(string name);

    Node *BFS(Node *node, string name, vector<string> &visited);

    vector<Pair *> DFSGeneral(Node *node);

    void DFS(Node *from, Friendship *to, vector<Pair *> &paths);

    vector<Friendship *> retrieveMutualFriendsFrom(Node *user);

    bool containsMutual(vector<Friendship *> &friendships, string name);

    Pair *getPair(vector<Pair *> &path, string name);

    void
    addToMutualFriends(Node *node, vector<Friendship *> &currentMutualFriends, vector<Friendship *> &mutualFriends);

    void getFriendliestUsers(vector<Pair *> &vector, Node *user);
};

#endif //SOCIALMEDIA_GRAPH_H

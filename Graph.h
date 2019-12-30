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
};

#endif //SOCIALMEDIA_GRAPH_H

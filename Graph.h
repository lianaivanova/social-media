#ifndef SOCIALMEDIA_GRAPH_H
#define SOCIALMEDIA_GRAPH_H

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

    vector<Friendship *> &getFriendships();

    bool containsFriend(string name);

    Node(User *user);

    Node &operator=(const Node &other);

    bool operator<(const Node &node);

    friend ostream &operator<<(ostream &oS, const Node &node);

    ~Node();
};


class Graph {
    vector<Node *> nodes;

public:
    vector<Node *> &getNodes();

};


int getFriendshipWeight(Friendship *friendship);

#endif //SOCIALMEDIA_GRAPH_H

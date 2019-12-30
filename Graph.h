#ifndef SOCIALMEDIA_GRAPH_H
#define SOCIALMEDIA_GRAPH_H

#include <vector>
#include "User.h"
#include "Type.h"


class Friendship {
    User *userFriend;
    Type friendshipType;
public:
    ~Friendship();
};

class Node {
    User *user;
    vector<Friendship> friendships;
public:
    ~Node();
};


class Graph {
    vector<Node> nodes;
};

#endif //SOCIALMEDIA_GRAPH_H

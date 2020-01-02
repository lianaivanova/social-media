#include "Graph.h"
#include <queue>


Node::Node(User *user) : user(user) {}

Node::~Node() {
    delete user;
}

User *Node::getUser() const {
    return user;
}


vector<Node *> &Graph::getNodes() {
    return nodes;
}

vector<Friendship *> &Node::getFriendships() {
    return friendships;
}

Node &Node::operator=(const Node &other) {
    if (this != &other) {
        delete user;
        copy(other);
    }
    return *this;
}

void Node::copy(const Node &other) {
    this->user = other.user;
    this->friendships = other.friendships;
}

bool Node::containsFriend(string name) {
    for (int i = 0; i < friendships.size(); i++) {
        if (friendships[i]->getUserFriend()->getUser()->getUsername() == name) {
            return true;
        }
    }
    return false;
}

ostream &operator<<(ostream &oS, const Node &node) {
    oS << *node.user;
    for (int i = 0; i < node.friendships.size(); ++i) {
        oS << node.friendships[i]->getUserFriend()->getUser()->getUsername();
        oS << "(" << getFriendshipWeight(node.friendships[i]) << ")";
        if (i < node.friendships.size() - 1) {
            oS << ",";
        }
    }
    oS << ";\n";
}

bool Node::operator<(const Node &node) {
    return friendships.size() < node.friendships.size();
}

Friendship::Friendship(Node *user, Type friendship) : userFriend(user), friendshipType(friendship) {}

Friendship::~Friendship() {
    delete userFriend;
}

Node *Friendship::getUserFriend() const {
    return userFriend;
}

Type Friendship::getFriendshipType() const {
    return friendshipType;
}

int getFriendshipWeight(Friendship *friendship) {
    switch (friendship->getFriendshipType()) {
        case BESTIE:
            return 3;
        case RELATIVE:
            return 2;
        default:
            return 1;
    }
}


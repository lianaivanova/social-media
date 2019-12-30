#include "Graph.h"

Node::~Node() {
    delete user;
}

Friendship::~Friendship(){
    delete userFriend;
}

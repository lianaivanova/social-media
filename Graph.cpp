#include "Graph.h"
#include <queue>

Node::~Node() {
    delete user;
}

Node::Node(User *user) {
    this->user = user;
}

User *Node::getUser() const {
    return user;
}

void Node::setUser(User *user) {
    Node::user = user;
}

vector<Friendship *> &Node::getFriendships() {
    return friendships;
}

void Node::setFriendships(const vector<Friendship *> &friendships) {
    Node::friendships = friendships;
}

Node &Node::operator=(const Node &other) {
    if (this != &other) { // self-assignment check expected
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


Friendship::~Friendship() {
    delete userFriend;
}

Node *Friendship::getUserFriend() const {
    return userFriend;
}

Type Friendship::getFriendshipType() const {
    return friendshipType;
}

Friendship::Friendship(Node *user, Type friendship) {
    this->userFriend = user;
    this->friendshipType = friendship;
}


bool GraphOperations::userExists(string name) {
    return false;
}

//TODO
Node *GraphOperations::findUser(string name) {
    return BFSGeneral(name);
}

vector<Node *> &Graph::getNodes() {
    return nodes;
}

void Graph::setNodes(vector<Node *> nodes) {
    Graph::nodes = nodes;
}

Node *GraphOperations::BFSGeneral(string name) {
    vector<string> visited;
    for (int i = 0; i < graph->getNodes().size(); i++) {
        Node *currentNode = graph->getNodes()[i];
        if (currentNode->getUser()->getUsername() == name) {
            return currentNode;
        }
        if (contains(visited, currentNode->getUser()->getUsername())) {
            continue;
        }
        Node *user = BFS(currentNode, name, visited);
        if (user != nullptr) {
            return user;
        }
    }
    return nullptr;
}

Node *GraphOperations::BFS(Node *node, string name, vector<string> &visited) {

    queue<Node *> queue;
    queue.push(node);

    while (!queue.empty()) {
        Node *current = queue.front();
        queue.pop();
        for (int i = 0; i < current->getFriendships().size(); ++i) {
            Node *friend1 = current->getFriendships()[i]->getUserFriend();
            if (friend1->getUser()->getUsername() == name) {
                return friend1;
            }
            if (!contains(visited, friend1->getUser()->getUsername())) {
                queue.push(friend1);
                visited.push_back(friend1->getUser()->getUsername());
            }
        }
    }
    return nullptr;
}

GraphOperations::GraphOperations(Graph *graph) {
    this->graph = graph;
}

GraphOperations::GraphOperations() {

}

bool GraphOperations::contains(vector<string> &visited, string name) {
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i] == name) {
            return true;
        }
    }
    return false;
}


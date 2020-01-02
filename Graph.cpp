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


bool GraphOperations::contains(vector<string> &visited, string name) {
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i] == name) {
            return true;
        }
    }
    return false;
}

bool GraphOperations::containsMutual(vector<Friendship *> &friendships, string name) {
    for (int i = 0; i < friendships.size(); i++) {
        if (friendships[i]->getUserFriend()->getUser()->getUsername() == name) {
            return true;
        }
    }
    return false;
}

Pair *GraphOperations::getPair(vector<Pair *> &paths, string name) {
    for (int i = 0; i < paths.size(); i++) {
        if (paths[i]->node->getUser()->getUsername() == name) {
            return paths[i];
        }
    }
    return nullptr;
}


Graph *GraphOperations::getGraph() {
    return graph;
}

vector<Pair *> GraphOperations::DFSGeneral(Node *user) {
    vector<Pair *> suggestions;
    vector<Friendship *> mutualFriends = retrieveMutualFriendsFrom(user);
    for (int i = 0; i < mutualFriends.size(); ++i) {
        DFS(user, mutualFriends[i], suggestions);
    }
    if (suggestions.empty()) {
        getFriendliestUsers(suggestions, user);
    }
    return suggestions;
}

void GraphOperations::DFS(Node *from, Friendship *to, vector<Pair *> &paths) {
    Pair *pair = getPair(paths, to->getUserFriend()->getUser()->getUsername());
    if (pair != nullptr) {
        pair->weight += getFriendshipWeight(to);
    } else {
        pair = new Pair(to->getUserFriend(), getFriendshipWeight(to));
        paths.push_back(pair);
    }
}

vector<Friendship *> GraphOperations::retrieveMutualFriendsFrom(Node *user) {
    vector<Friendship *> mutualFriends;
    int size = user->getFriendships().size();
    for (int i = 0; i < size; ++i) {
        vector<Friendship *> currentMutualFriendships = user->getFriendships()[i]->getUserFriend()->getFriendships();
        addToMutualFriends(user, currentMutualFriendships, mutualFriends);
    }
    return mutualFriends;
}

void GraphOperations::addToMutualFriends(Node *node, vector<Friendship *> &currentMutualFriends,
                                         vector<Friendship *> &mutualFriends) {
    for (int i = 0; i < currentMutualFriends.size(); ++i) {
        Friendship *friendship = currentMutualFriends[i];
        string friendName = friendship->getUserFriend()->getUser()->getUsername();
        if (!node->containsFriend(friendName)
            && !node->getUser()->containsBannedUser(friendName)
            && !(friendName == node->getUser()->getUsername())) {
            mutualFriends.push_back(friendship);
        }
    }
}

template<typename T>
void swap(T *a, T *b) {
    T t = *a;
    *a = *b;
    *b = t;
}

template<typename T>
int partition(vector<T> &elements, int low, int high) {
    T pivot = elements[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (elements[j] < pivot) {
            i++;
            swap(&elements[i], &elements[j]);
        }
    }
    swap(&elements[i + 1], &elements[high]);
    return (i + 1);
}

template<typename T>
void quickSort(vector<T> &elements, int low, int high) {
    if (low < high) {
        int pi = partition(elements, low, high);

        quickSort(elements, low, pi - 1);
        quickSort(elements, pi + 1, high);
    }
}

Pair::Pair(Node *node, int weight) {
    this->node = node;
    this->weight = weight;
}

bool Pair::operator<(const Pair &pair) {
    return weight < pair.weight;
}


void GraphOperations::getFriendliestUsers(vector<Pair *> &vector, Node *user) {
    std::vector<Node *> &users = getGraph()->getNodes();
    int size = users.size();
    for (int i = 0; i < size; ++i) {
        string friendName = users[i]->getUser()->getUsername();
        if (friendName != user->getUser()->getUsername() && !user->getUser()->containsBannedUser(friendName)) {
            Pair *userFriend = new Pair(users[i], users[i]->getFriendships().size());
            vector.push_back(userFriend);
        }
    }
    quickSort(vector, 0, vector.size() - 1);

}

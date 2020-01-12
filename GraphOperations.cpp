#include "GraphOperations.h"
#include <queue>
#include "QuickSortImpl.h"
using namespace std;

Node *GraphOperations::findUser(string name) {
    return BFSGeneral(name);
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

GraphOperations::GraphOperations(Graph *graph) : graph(graph) {}


bool GraphOperations::contains(vector<string> &visited, string name) {
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i] == name) {
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

Pair::Pair(Node *node, int weight) : node(node), weight(weight) {}

bool Pair::operator<(const Pair &pair) {
    return weight < pair.weight;
}

int GraphOperations::getWeight(Node* user){
    int weight = 0;
    int size = user->getFriendships().size();
    for (int i = 0; i < size; ++i) {
        weight += getFriendshipWeight(user->getFriendships()[i]);
    }
    return weight;
}

void GraphOperations::getFriendliestUsers(vector<Pair *> &suggestions, Node *user) {
    std::vector<Node*> users = getGraph()->getNodes();
    int size = users.size();
    for (int i = 0; i < size; ++i) {
        string friendName = users[i]->getUser()->getUsername();
        if (friendName != user->getUser()->getUsername() && !user->getUser()->containsBannedUser(friendName)
            && !user->containsFriend(friendName) && !users[i]->getUser()->containsBannedUser(user->getUser()->getUsername())) {
            Pair *userFriend = new Pair(users[i], getWeight(users[i]));
            suggestions.push_back(userFriend);
        }
    }
    quickSort(suggestions, 0, suggestions.size() - 1);
}
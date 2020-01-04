#include <algorithm>
#include "SocialMediaOperations.h"


Status SocialMediaOperations::createUser(string name, string email, int age) {
    Node *foundUser = graphOperations.findUser(name);
    if (foundUser != nullptr) {
        return USER_EXISTS;
    }
    User *user = new User(name, email, age);
    Node *node = new Node(user);
    socialMedia.getNetwork()->getNodes().push_back(node);
    return SUCCESS;
}

Status SocialMediaOperations::deleteUser(string email) {
    int size = socialMedia.getNetwork()->getNodes().size();
    for (int i = 0; i < size; i++) {
        if (socialMedia.getNetwork()->getNodes()[i]->getUser()->getEmail() == email) {
            Node *user = socialMedia.getNetwork()->getNodes()[i];
            for (int i = 0; i < user->getFriendships().size(); ++i) {
                Node *userFriend = user->getFriendships()[i]->getUserFriend();
                delinkUsers(userFriend->getUser()->getUsername(), user->getUser()->getUsername());
            }
            socialMedia.getNetwork()->getNodes().erase(socialMedia.getNetwork()->getNodes().begin() + i);
            return SUCCESS;
        }
    }
    return USER1_NOT_FOUND;
}

Status SocialMediaOperations::findUser(string name, ostream &oS) {
    Node *node = graphOperations.findUser(name);
    if (node == nullptr) {
        return USER1_NOT_FOUND;
    }
    oS << "USER\n----- \n";
    oS << "Name: " << node->getUser()->getUsername() << endl;
    oS << "Age: " << node->getUser()->getAge() << endl;
    oS << "Friends: ";
    vector<Friendship *> &friends = node->getFriendships();
    int size = friends.size();
    if(size == 0){
        oS << "none";
    }
    for (int i = 0; i < size; i++) {
        if (i != 0) {
            oS << ", ";
        }
        oS << friends[i]->getUserFriend()->getUser()->getUsername();
    }
    oS << endl;
    return SUCCESS;
}

Status SocialMediaOperations::linkUsers(string name1, string name2, Type type) {
    Node *user1 = graphOperations.findUser(name1);
    Node *user2 = graphOperations.findUser(name2);
    if (user1 == nullptr) {
        return USER1_NOT_FOUND;
    } else if (user2 == nullptr) {
        return USER2_NOT_FOUND;
    }
    if (user1->getUser()->containsBannedUser(name2)) {
        return USER2_BANNED;
    } else if (user2->getUser()->containsBannedUser(name1)) {
        return USER1_BANNED;
    }
    if (user1->getFriendships().size() < user2->getFriendships().size()) {
        if (user1->containsFriend(user2->getUser()->getUsername())) {
            return USERS_LINKED;
        }
    } else {
        if (user2->containsFriend(user1->getUser()->getUsername())) {
            return USERS_LINKED;
        }
    }
    user1->getFriendships().push_back(new Friendship(user2, type));
    user2->getFriendships().push_back(new Friendship(user1, type));
    return SUCCESS;
}

Status SocialMediaOperations::delinkUsers(string name1, string name2) {
    Node *user1 = graphOperations.findUser(name1);
    Node *user2 = graphOperations.findUser(name2);
    if (user1 == nullptr) {
        return USER1_NOT_FOUND;
    } else if (user2 == nullptr) {
        return USER2_NOT_FOUND;
    }
    if (!user1->containsFriend(name2)) {
        return USERS_DELINKED;
    }
    for (int i = 0; i < user1->getFriendships().size(); ++i) {
        if (user1->getFriendships()[i]->getUserFriend()->getUser()->getUsername() == name2) {
            user1->getFriendships().erase(user1->getFriendships().begin() + i);
        }
    }
    for (int i = 0; i < user2->getFriendships().size(); ++i) {
        if (user2->getFriendships()[i]->getUserFriend()->getUser()->getUsername() == name1) {
            user2->getFriendships().erase(user2->getFriendships().begin() + i);
        }
    }
    return SUCCESS;
}

Status SocialMediaOperations::banUser(string name1, string name2) {
    Node *user1 = graphOperations.findUser(name1);
    Node *user2 = graphOperations.findUser(name2);
    if (user1 == nullptr) {
        return USER1_NOT_FOUND;
    } else if (user2 == nullptr) {
        return USER2_NOT_FOUND;
    } else if (user1->getUser()->containsBannedUser(name2)) {
        return USER_ALREADY_BANNED;
    }
    user1->getUser()->getBannedUsers().push_back(name2);
    delinkUsers(user1->getUser()->getUsername(), name2);
    return SUCCESS;
}

SocialMediaOperations::SocialMediaOperations(SocialMedia &socialMedia, GraphOperations &graphOperations)
        : socialMedia(socialMedia), graphOperations(graphOperations) {}

GraphOperations &SocialMediaOperations::getGraphOperations() {
    return graphOperations;
}

Status SocialMediaOperations::recommendUsers(string name, ostream &oS) {
    Node *user = graphOperations.findUser(name);
    if (user == nullptr) {
        return USER1_NOT_FOUND;
    }
    vector<Pair *> suggestions = graphOperations.DFSGeneral(user);
    if(suggestions.empty()){
        oS << "No users to recommend." << endl;
    }
    for (int i = 0; i < suggestions.size(); ++i) {
        if (i >= 30) {
            return SUCCESS;
        }
        if (i != 0) {
            oS << ", ";
        }
        oS << suggestions[i]->node->getUser()->getUsername() << endl;
    }
    return SUCCESS;
}





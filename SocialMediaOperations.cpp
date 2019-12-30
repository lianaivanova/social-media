#include <algorithm>
#include <stdlib.h>
#include "SocialMediaOperations.h"


Type getType(int typeNum) {
    switch (typeNum) {
        case 1:
            return BESTIE;
        case 2:
            return RELATIVE;
        default:
            return NORMAL;
    }
}

void toLower(string &command) {
    for_each(command.begin(), command.end(), [](char &c) {
        c = ::toupper(c);
    });
}

void SocialMediaOperations::getInput(ostream &oS, istream &iS) {
    string command;
    string name1;
    string name2;
    string email;
    int age;
    int type;
    Status result;
    printCommands(oS);
    do {
        oS << "Enter command and needed information: ";
        iS >> command;
        toLower(command);
        if (command == "CREATE") {
            iS >> name1 >> email >> age;
            result = createUser(name1, email, age);
            if (result != SUCCESS) {
                oS << "FAIL: " << name1 << " already exists." << endl;
            } else {
                oS << "User " << name1 << " created." << endl;
            }
        } else if (command == "DELETE") {
            iS >> email;
            result = deleteUser(email);
            if (result != SUCCESS) {
                oS << "FAIL: " << name1 << " doesn't exist." << endl;
            } else {
                oS << "User " << name1 << " deleted." << endl;
            }
        } else if (command == "LINK") {
            iS >> name1 >> name2 >> type;
            result = linkUsers(name1, name2, getType(type));
            if (result == USER1_NOT_FOUND) {
                oS << "FAIL: " << name1 << " doesn't exist." << endl;
            } else if (result == USER2_NOT_FOUND) {
                oS << "FAIL: " << name2 << " doesn't exist." << endl;
            } else if (result == USERS_LINKED) {
                oS << "FAIL: Users already linked." << endl;
            } else if (result == USER1_BANNED) {
                oS << "FAIL: " << name1 << " banned." << endl;
            } else if (result == USER2_BANNED) {
                oS << "FAIL: " << name2 << " banned." << endl;
            } else {
                oS << "Users linked." << endl;
            }
        } else if (command == "FIND") {
            iS >> name1;
            if (findUser(name1, oS) != SUCCESS) {
                oS << "None" << endl;
            }
        } else if (command == "DELINK") {
            iS >> name1 >> name2;
            result = delinkUsers(name1, name2);
            if (result == USER1_NOT_FOUND) {
                oS << "FAIL: " << name1 << " doesn't exist." << endl;
            } else if (result == USER2_NOT_FOUND) {
                oS << "FAIL: " << name2 << " doesn't exist." << endl;
            } else if (result == USERS_DELINKED) {
                oS << "FAIL: Users not linked." << endl;
            } else {
                oS << "Users delinked." << endl;
            }
        } else if (command == "BAN") {
            iS >> name1 >> name2;
            result = banUser(name1, name2);
            if (result == USER2_BANNED) {
                oS << "FAIL: User already banned." << endl;
            } else {
                oS << "User " << name2 << " banned." << endl;
            }
        }

    } while (command != "EXIT");
}

void SocialMediaOperations::printCommands(ostream &ioS) {
    ioS << "> to create new user: CREATE <name> <e-mail> <age> \n"
           "> to delete existing user: DELETE <e-mail> \n"
           "> to link two users as friends: LINK <user1_name> <user2_name> <type_code>, \n"
           "   Type codes: 1 - bestie, 2 - relative, 3 - normal \n"
           "> to search for user: FIND <name>\n"
           "> to remove friendship of two users: DELINK <user1_name> <user2_name>\n"
           "> to get friend recommendations: RECOMMEND <name>\n";
}

Status SocialMediaOperations::createUser(string name, string email, int age) {
    if (graphOperations.userExists(name)) {
        return USER_EXISTS;
    }
    User *user = new User(name, email, age);
    Node *node = new Node(user);
    socialMedia.getNetwork()->getNodes().push_back(node);
    return SUCCESS;
}

Status SocialMediaOperations::deleteUser(string email) {
    return USERS_DELINKED;
}

Status SocialMediaOperations::findUser(string name, ostream &ioS) {
    Node *node = graphOperations.findUser(name);
    if (node == nullptr) {
        return USER1_NOT_FOUND;
    }
    ioS << "USER:\n----- \n";
    ioS << "Name: " << node->getUser()->getUsername() << endl;
    ioS << "Age: " << node->getUser()->getAge() << endl;
    ioS << "Friends: ";
    vector<Friendship *> &friends = node->getFriendships();
    int size = friends.size();
    for (std::size_t i = 0; i < size; ++i) {
        ioS << friends[i]->getUserFriend()->getUser()->getUsername() << ", ";
    }
    ioS << endl;
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
//    delete user1;
//    delete user2;
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
        return USER2_BANNED;
    }
    user1->getUser()->getBannedUsers().push_back(name2);
    return SUCCESS;
}

SocialMediaOperations::SocialMediaOperations(SocialMedia &socialMedia, GraphOperations &graphOperations) {
    this->socialMedia = socialMedia;
    this->graphOperations = graphOperations;
}


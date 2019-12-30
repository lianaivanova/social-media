#include <algorithm>
#include "SocialMediaOperations.h"

SocialMediaOperations::SocialMediaOperations(SocialMedia &socialMedia) {
    this->socialMedia = socialMedia;
}

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

void SocialMediaOperations::getInput(iostream &ioS) {
    string command;
    string name1;
    string name2;
    string email;
    int age;
    int type;
    Status result;
    do {
        system("CLS");
        printCommands(ioS);
        ioS << "Enter command and needed information: ";
        ioS >> command;
        toLower(command);
        if (command == "CREATE") {
            ioS >> name1 >> email >> age;
            result = createUser(name1, email, age);
            if (result != SUCCESS) {
                ioS << "FAIL: " << name1 << " already exists." << endl;
            } else {
                ioS << "User " << name1 << " created." << endl;
            }
        } else if (command == "DELETE") {
            ioS >> email;
            result = deleteUser(email);
            if (result != SUCCESS) {
                ioS << "FAIL: " << name1 << " doesn't exist." << endl;
            } else {
                ioS << "User " << name1 << " deleted." << endl;
            }
        } else if (command == "LINK") {
            ioS >> name1 >> name2 >> type;
            result = linkUsers(name1, name2, getType(type));
            if (result == USER1_NOT_FOUND) {
                ioS << "FAIL: " << name1 << " doesn't exist." << endl;
            } else if (result == USER2_NOT_FOUND) {
                ioS << "FAIL: " << name2 << " doesn't exist." << endl;
            } else if (result == USERS_LINKED) {
                ioS << "FAIL: Users already linked." << endl;
            } else {
                ioS << "Users linked." << endl;
            }
        } else if (command == "FIND") {
            ioS >> name1;
            if (findUser(name1, ioS) != SUCCESS) {
                ioS << "None" << endl;
            }
        } else if (command == "DELINK") {
            ioS >> name1 >> name2;
            result = delinkUsers(name1, name2);
            if (result == USER1_NOT_FOUND) {
                ioS << "FAIL: " << name1 << " doesn't exist." << endl;
            } else if (result == USER2_NOT_FOUND) {
                ioS << "FAIL: " << name2 << " doesn't exist." << endl;
            } else if (result == USERS_DELINKED) {
                ioS << "FAIL: Users not linked." << endl;
            } else {
                ioS << "Users delinked." << endl;
            }
        }

    } while (command != "EXIT");
}

void SocialMediaOperations::printCommands(iostream &ioS) {
    ioS << "> to create new user: CREATE <name> <e-mail> <age> \n "
           "> to delete existing user: DELETE <e-mail> \n"
           "> to link two users as friends: LINK <user1_name> <user2_name> <type_code>, \n"
           "   Type codes: 1 - bestie, 2 - relative, 3 - normal \n"
           "> to search for user: FIND <name>\n"
           "> to remove friendship of two users: DELINK <user1_name> <user2_name>\n"
           "> to get friend recommendations: RECOMMEND <name>\n";
}

Status SocialMediaOperations::createUser(string name, string email, int age) {
    return USERS_DELINKED;
}

Status SocialMediaOperations::deleteUser(string email) {
    return USERS_DELINKED;
}

Status SocialMediaOperations::findUser(string name, iostream &ioS) {
    return USERS_DELINKED;
}

Status SocialMediaOperations::linkUsers(string name1, string name2, Type type) {
    return USERS_DELINKED;
}

Status SocialMediaOperations::delinkUsers(string name1, string name2) {
    return USERS_DELINKED;
}

Status SocialMediaOperations::banUser(string name1, string name2) {
    return USERS_DELINKED;
}


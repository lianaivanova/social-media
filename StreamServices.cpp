#include "StreamServices.h"
#include <algorithm>
#include <fstream>

StreamServices::StreamServices(SocialMediaOperations &socialMediaOperations1)
        : socialMediaOperations(socialMediaOperations1) {}

Type StreamServices::getType(int typeNum) {
    switch (typeNum) {
        case 3:
            return BESTIE;
        case 2:
            return RELATIVE;
        default:
            return NORMAL;
    }
}

void StreamServices::toLower(string &command) {
    for_each(command.begin(), command.end(), [](char &c) {
        c = ::toupper(c);
    });
}


void StreamServices::printCommands(ostream &oS) {
    oS << "Commands:\n"
          "> create new user: CREATE <name> <e-mail> <age> \n"
          "> delete existing user: DELETE <e-mail> \n"
          "> link two users as friends: LINK <user1_name> <user2_name> <type_code>*, \n"
          "   *Friendship type: 1 - bestie, 2 - relative, 3 - normal \n"
          "> search for user: FIND <name>\n"
          "> remove friendship of two users: DELINK <user1_name> <user2_name>\n"
          "> get friend recommendations: RECOMMEND <name>\n"
          "> load data from file: LOAD <file_name>\n"
          "> save data to file: SAVE <file_name>\n"
          "> legend: HELP\n\n";
}

void StreamServices::getInput(ostream &oS, istream &iS) {
    string command;
    string name1;
    string name2;
    string email;
    string file;
    int age;
    int type;
    Status result;
    oS << "~~~~~~~~~~~~~~~~~~~~~~\nWelcome to GraphBook! \n~~~~~~~~~~~~~~~~~~~~~~\n";
    printCommands(oS);
    do {
        oS << "\nEnter command and information: ";
        iS >> command;
        toLower(command);
        if (command == "CREATE") {
            iS >> name1 >> email >> age;
            result = socialMediaOperations.createUser(name1, email, age);
            if (result != SUCCESS) {
                oS << "FAIL: " << name1 << " already exists." << endl;
            } else {
                oS << "User " << name1 << " created." << endl;
            }
        } else if (command == "DELETE") {
            iS >> email;
            result = socialMediaOperations.deleteUser(email);
            if (result != SUCCESS) {
                oS << "FAIL: User with e-mail " << email << " doesn't exist." << endl;
            } else {
                oS << "User deleted." << endl;
            }
        } else if (command == "LINK") {
            iS >> name1 >> name2 >> type;
            result = socialMediaOperations.linkUsers(name1, name2, getType(type));
            if (result != SUCCESS) {
                validate(result, name1, name2, oS);
            } else {
                oS << "Users linked." << endl;
            }
        } else if (command == "FIND") {
            iS >> name1;
            if (socialMediaOperations.findUser(name1, oS) != SUCCESS) {
                oS << "None" << endl;
            }
        } else if (command == "DELINK") {
            iS >> name1 >> name2;
            result = socialMediaOperations.delinkUsers(name1, name2);
            if (result != SUCCESS) {
                validate(result, name1, name2, oS);
            } else {
                oS << "Users delinked." << endl;
            }
        } else if (command == "BAN") {
            iS >> name1 >> name2;
            result = socialMediaOperations.banUser(name1, name2);
            if (result != SUCCESS) {
                validate(result, name1, name2, oS);
            } else {
                oS << "User " << name2 << " banned." << endl;
            }
        } else if (command == "HELP") {
            printCommands(oS);
        } else if (command == "LOAD") {
            iS >> file;
            loadData(file);
        } else if (command == "RECOMMEND") {
            iS >> name1;
            socialMediaOperations.recommendUsers(name1, oS);
        } else if (command == "SAVE") {
            iS >> file;
            saveData(file);
        }

    } while (command != "EXIT");
}

void StreamServices::validate(Status result, string name1, string name2, ostream &oS) {
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
    } else if (result == USERS_DELINKED) {
        oS << "FAIL: Users not linked." << endl;
    } else if (result == USER_ALREADY_BANNED) {
        oS << "FAIL: User already banned." << endl;
    }
}

void StreamServices::loadData(string fileName) {
    ifstream iFile(fileName);
    if (!iFile) {
        cerr << "File could not be opened.\n";
        return;
    }
    string name;
    string line;
    while (iFile.good()) {
        getline(iFile, name, ';');
        if(name.empty()){
            break;
        }
        User *user = new User(name);
        buildUser(user, iFile);
    }
    iFile.close();
}


void StreamServices::buildUser(User *user, ifstream &iFile) {
    string info;
    string friendName;
    string friends;
    Node *node = socialMediaOperations.getGraphOperations().findUser(user->getUsername());
    if (node == nullptr) {
        node = new Node(user);
        socialMediaOperations.getGraphOperations().getGraph()->getNodes().push_back(node);
    } else {
        user = node->getUser();
    }
    getline(iFile, info, ';');
    user->setEmail(info);
    getline(iFile, info, ';');
    user->setAge(stoi(info));
    info = "";

    getline(iFile, friends, ';');
    for (int i = 0; i < friends.size(); ++i) {
        char letter = friends[i];
        if(letter == ','){
            user->getBannedUsers().push_back(info);
            info = "";
        } else {
            info += letter;
        }
    }
    if(!info.empty()){
        user->getBannedUsers().push_back(info);
        info = "";
    }

    getline(iFile, friends, '\n');
    for (int i = 0; i < friends.size(); i++) {
        char letter = friends[i];
        if(letter == ','){
            createFriend(user, friendName, stoi(info));
            info = "";
            friendName = "";
        } else if(letter == '('){
            friendName = info;
            info = "";
        } else if(letter == ')'){
            continue;
        } else if(letter == ';'){
            createFriend(user, friendName, stoi(info));
            return;
        } else {
            info += letter;
        }
    }
}

void StreamServices::createFriend(User *user, string name, int typeNum) {
    Node *node = socialMediaOperations.getGraphOperations().findUser(name);
    if (node == nullptr) {
        User *userFriend = new User(name);
        node = new Node(userFriend);
        socialMediaOperations.getGraphOperations().getGraph()->getNodes().push_back(node);
    }
    socialMediaOperations.linkUsers(name, user->getUsername(), getType(typeNum));
}

void StreamServices::saveData(string fileName) {
    ofstream oFile(fileName, ofstream::app);
    if (!oFile) {
        cerr << "File could not be opened.\n";
        return;
    }
    int size = socialMediaOperations.getGraphOperations().getGraph()->getNodes().size();
    vector<Node *> users = socialMediaOperations.getGraphOperations().getGraph()->getNodes();
    oFile.seekp(0, ios::end);
    for (int i = 0; i < size; ++i) {
        oFile << *users[i];
    }
    oFile.close();
}

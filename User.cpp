#include <iostream>
#include "User.h"

using namespace std;

User::User(string name, string email, int age) {
    this->username = name;
    this->email = email;
    this->age = age;
}

User::User(string name) {
    this->username = name;
    this->email = "";
    this->age = 0;
}

vector<string> &User::getBannedUsers() {
    return bannedUsers;
}

const string &User::getUsername() const {
    return username;
}

int User::getAge() const {
    return age;
}

bool User::containsBannedUser(string name) {
    for (int i = 0; i < bannedUsers.size(); i++) {
        if (bannedUsers[i] == name) {
            return true;
        }
    }
    return false;
}

const string &User::getEmail() const {
    return email;
}

void User::setEmail(const string &email) {
    User::email = email;
}

void User::setAge(int age) {
    User::age = age;
}


ostream &operator<<(ostream &oS, const User &user) {
    oS << user.username << ";" << user.email << ";" << user.age << ";";
    for (int i = 0; i < user.bannedUsers.size(); ++i) {
        oS << user.bannedUsers[i];
        if (i < user.bannedUsers.size() - 1) {
            oS << ",";
        }
    }
    oS << ";";
}

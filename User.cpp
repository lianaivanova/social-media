#include <iostream>
#include "User.h"
using namespace std;

User::User(string name, string email, int age) {
    this->username = name;
    this->email = email;
    this->age = age;
}

vector<string> &User::getBannedUsers() {
    return bannedUsers;
}

void User::setBannedUsers(const vector<string> &bannedUsers) {
    User::bannedUsers = bannedUsers;
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


#include <iostream>
#include "User.h"
using namespace std;

User::User(string name, string email, int age) {
    this->username = name;
    this->email = email;
    this->age = age;
}

const vector<string> &User::getBannedUsers() const {
    return bannedUsers;
}

void User::setBannedUsers(const vector<string> &bannedUsers) {
    User::bannedUsers = bannedUsers;
}


#ifndef SOCIALMEDIA_USER_H
#define SOCIALMEDIA_USER_H


#include <iostream>
#include <vector>

using namespace std;


class User {
    string username;
    string email;
    int age;
    vector<string> bannedUsers;

public:

    bool containsBannedUser(string name);

    const string &getUsername() const;

    int getAge() const;

    User(string name, string email, int age);

    vector<string> &getBannedUsers();

    void setBannedUsers(const vector<string> &bannedUsers);

};


#endif //SOCIALMEDIA_USER_H

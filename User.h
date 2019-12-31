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
    User(string name);

    User(string name, string email, int age);

    void setEmail(const string &email);

    void setAge(int age);

    const string &getEmail() const;

    const string &getUsername() const;

    int getAge() const;

    vector<string> &getBannedUsers();

    bool containsBannedUser(string name);

    friend ostream &operator<<(ostream &oS, const User &user);

};


#endif //SOCIALMEDIA_USER_H

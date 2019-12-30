#ifndef SOCIALMEDIA_SOCIALMEDIAOPERATIONS_H
#define SOCIALMEDIA_SOCIALMEDIAOPERATIONS_H

#include "SocialMedia.h"
#include "Type.h"

class SocialMediaOperations {
    SocialMedia socialMedia;
    GraphOperations graphOperations;


    void printCommands(ostream &ioS);

    Status createUser(string name, string email, int age);

    Status deleteUser(string email);

    Status findUser(string name, ostream &ioS);

    Status linkUsers(string name1, string name2, Type type);

    Status delinkUsers(string name1, string name2);

    Status banUser(string name1, string name2);

    // void recommendUsers(string name1);


public:
    SocialMediaOperations(SocialMedia &socialMedia, GraphOperations &graphOperations);

    void getInput(ostream &oS, istream &iS);
};


#endif //SOCIALMEDIA_SOCIALMEDIAOPERATIONS_H

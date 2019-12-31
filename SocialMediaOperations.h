#ifndef SOCIALMEDIA_SOCIALMEDIAOPERATIONS_H
#define SOCIALMEDIA_SOCIALMEDIAOPERATIONS_H

#include "SocialMedia.h"
#include "Type.h"

class SocialMediaOperations {
    SocialMedia socialMedia;
    GraphOperations graphOperations;
public:
    SocialMediaOperations(SocialMedia &socialMedia, GraphOperations &graphOperations);

    Status createUser(string name, string email, int age);

    Status deleteUser(string email);

    Status findUser(string name, ostream &oS);

    Status linkUsers(string name1, string name2, Type type);

    Status delinkUsers(string name1, string name2);

    Status banUser(string name1, string name2);

    GraphOperations &getGraphOperations();

    Status recommendUsers(string name1, ostream &oS);
};


#endif //SOCIALMEDIA_SOCIALMEDIAOPERATIONS_H

#ifndef SOCIALMEDIA_STREAMSERVICES_H
#define SOCIALMEDIA_STREAMSERVICES_H

#include "SocialMediaOperations.h"

class StreamServices {
    SocialMediaOperations socialMediaOperations;

    Type getType(int typeNum);

    void toLower(string &command);

    void validate(Status result, string name1, string name2, ostream &oS);

    void printCommands(ostream &oS);

    void buildUser(string line, User *user);

    void createFriend(string name, int typeNum, User *user);

public:
    StreamServices(SocialMediaOperations &socialMediaOperations1);

    void getInput(ostream &oS, istream &iS);

    void loadData(string fileName);

    void saveData(string fileName);

};


#endif //SOCIALMEDIA_STREAMSERVICES_H

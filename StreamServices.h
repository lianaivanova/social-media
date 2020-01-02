#ifndef SOCIALMEDIA_STREAMSERVICES_H
#define SOCIALMEDIA_STREAMSERVICES_H

#include "SocialMediaOperations.h"

class StreamServices {
    SocialMediaOperations socialMediaOperations;

    Type getType(int typeNum);

    void toLower(string &command);

    void validate(Status result, string name1, string name2, ostream &oS);

    void printCommands(ostream &oS);

    void buildUser(User *user, ifstream &iFile);

    void createFriend(User *user, string name, int typeNum);

public:
    StreamServices(SocialMediaOperations &socialMediaOperations1);

    void getInput(ostream &oS, istream &iS);

    void loadData(string fileName);

    void saveData(string fileName);

};


#endif //SOCIALMEDIA_STREAMSERVICES_H

#ifndef SOCIALMEDIA_SOCIALMEDIA_H
#define SOCIALMEDIA_SOCIALMEDIA_H

#include "GraphOperations.h"
#include "User.h"

class SocialMedia {
    Graph *network;

public:
    SocialMedia();

    Graph *getNetwork() const;
};


#endif //SOCIALMEDIA_SOCIALMEDIA_H

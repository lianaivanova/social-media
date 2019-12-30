#ifndef SOCIALMEDIA_SOCIALMEDIA_H
#define SOCIALMEDIA_SOCIALMEDIA_H

#include "Graph.h"
#include "User.h"

class SocialMedia {
    Graph *network;

public:
    SocialMedia();

    Graph *getNetwork() const;

    void setNetwork(Graph *network);
};


#endif //SOCIALMEDIA_SOCIALMEDIA_H

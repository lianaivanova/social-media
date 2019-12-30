#ifndef SOCIALMEDIA_SOCIALMEDIA_H
#define SOCIALMEDIA_SOCIALMEDIA_H

#include "Graph.h"
#include "User.h"

class SocialMedia {
    Graph *friendships;

public:
    SocialMedia();

    Graph *getFriendships() const;

    void setFriendships(Graph *friendships);
};


#endif //SOCIALMEDIA_SOCIALMEDIA_H

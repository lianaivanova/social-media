#include "SocialMedia.h"

SocialMedia::SocialMedia() {}

Graph *SocialMedia::getFriendships() const {
    return friendships;
}

void SocialMedia::setFriendships(Graph *friendships) {
    SocialMedia::friendships = friendships;
}

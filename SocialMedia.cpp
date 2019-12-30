#include "SocialMedia.h"

SocialMedia::SocialMedia() {
    this->network = new Graph();
}

Graph *SocialMedia::getNetwork() const {
    return network;
}


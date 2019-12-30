#include "SocialMedia.h"

SocialMedia::SocialMedia() {
    this->network = new Graph();
}

Graph *SocialMedia::getNetwork() const {
    return network;
}

void SocialMedia::setNetwork(Graph *network) {
    SocialMedia::network = network;
}

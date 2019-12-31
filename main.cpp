#include <iostream>
#include "StreamServices.h"

int main() {
    SocialMedia socialMedia;
    GraphOperations graphOperations(socialMedia.getNetwork());
    SocialMediaOperations socialMediaOperations(socialMedia, graphOperations);
    StreamServices streamServices(socialMediaOperations);
    streamServices.getInput(cout, cin);
    return 0;
}
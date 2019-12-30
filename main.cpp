#include <iostream>
#include <fstream>
#include "SocialMediaOperations.h"
int main() {
    SocialMedia socialMedia;
    GraphOperations graphOperations(socialMedia.getNetwork());
    SocialMediaOperations socialMediaOperations(socialMedia, graphOperations);
    socialMediaOperations.getInput(cout, cin);
    return 0;
}
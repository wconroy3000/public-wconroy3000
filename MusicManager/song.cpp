#include "song.h"
song::song(unsigned int i, std::string a, unsigned int d, std::string t)
{

    title = t;
    artist = a;
    minutes = d/60;
    seconds = d%60;
    id = i;
    time = 0;
    fav = false;
    heapIndex = -1;
}


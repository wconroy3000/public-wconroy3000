#pragma once
#include <string>

//fixes circular dependecy, forward declration
class dllNode;  

class song
{
    public:
        //t>title a>artist d>duration i>id
        //duration is in seconds
        song(unsigned int i, std::string a, unsigned int d, std::string t);
        std::string title;
        std::string artist;
        unsigned int minutes;
	unsigned int seconds;
        unsigned int id;
        unsigned int time;
        bool fav;
        int heapIndex;
        dllNode* myNode = nullptr;

};



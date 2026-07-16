#pragma once
#include "song.h"
#include "dllNode.h"

class songList
{
    public:
        bool insert(song* newSong); //insert newSong sorted by ID
        void remove(song* s);
        void print();
        song* findById(unsigned int id);
        dllNode* head = nullptr;
        dllNode* tail = nullptr;
};
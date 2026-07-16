#pragma once

//fixes circular dependecy, forward declration
class song;

class dllNode
{
    public:
        song* data = nullptr;
        dllNode* prev = nullptr;
        dllNode* next = nullptr;
        dllNode(song* newSong);
};
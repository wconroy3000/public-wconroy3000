#pragma once
#include "song.h"
#include <vector>

class heap {
    private:
        std::vector<song*> list;
        void swapNodes(int a, int b);
        void percUp(int index);
        void percDown(int index);

    public:
        heap();
        void insert(song* s);
        song* getMax();       
        void remove(song* s);
        int size();
};
#include <iostream>
#include "heap.h"

heap::heap() {}

void heap::swapNodes(int a, int b) {
    //swap pointers
    song* temp = list[a];
    list[a] = list[b];
    list[b] = temp;


    list[a]->heapIndex = a;
    list[b]->heapIndex = b;
}

void heap::percUp(int index) {
    bool found = false;
    while (index > 0 && !found) {
        int parent = (index - 1) / 2;
        if (list[index]->time > list[parent]->time) {
            swapNodes(index, parent);
            index = parent;
        }
        else {
            found = true;
        }
    }
}

void heap::percDown(int index) {
    int size = list.size();
    bool found = false;
    while (!found) {
        int left  = 2 * index + 1;
        int right = 2 * index + 2;
        int longest = index;

        //checks the heap for larger children and goes down
        if (left < size && list[left]->time > list[longest]->time) longest = left;
        if (right < size && list[right]->time > list[longest]->time) longest = right;

        //swaps the index with the child node to continue percolating down 
        if (longest != index) {
            swapNodes(index, longest);
            index = longest;
        }
        else {
            found = true;
        }
    }
}

void heap::insert(song* s) {
    list.push_back(s);
    s->heapIndex = list.size() - 1;
    percUp(s->heapIndex);
}

song* heap::getMax() {
    if (list.empty()) return nullptr;
    return list[0];
}

void heap::remove(song* s) {
    if(s -> fav)
    {
        std::cout << "Error: Cannot remove favorited songs" << std::endl;
        return;
    }
    if(s -> heapIndex == -1)
    {
        std::cout << "Song " << s -> title << " does not exist" << std::endl;
        return;
    }
    int index = s->heapIndex;
    int last  = list.size() - 1;

    //swap with last element
    swapNodes(index, last);
    list.pop_back();
    s->heapIndex = -1;

    //nothing left to reheapify since list empty or it was the last element
    if (list.empty() || index == list.size()) return;

    //reheapify at the swapped position
    percUp(index);
    percDown(index);
}

int heap::size() {
    return list.size();
}

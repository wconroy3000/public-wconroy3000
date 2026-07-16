#include <iostream>
#include "songList.h"
#include "dllNode.h"
#include "song.h"

bool songList::insert(song* newSong)
{
    dllNode* node = new dllNode(newSong);
    //Node inside song object to remove through
    node->data->myNode = node;

    if(head == nullptr)
    {
        //place node in empty list
        //If list is empty, set newNode to head and tail
        head = node;
        tail = node;
        node->next = nullptr;
        node->prev = nullptr;
        return true;
    }
    dllNode* curr = head;
    while(curr != nullptr)
    {
        if(curr -> data -> id == node -> data -> id)
        {
            
            delete node;
            return false;
        }
        //search for location to place new node based on id order (smallest to largest)
        if(curr -> data -> id > node -> data -> id)
        {
            if(curr == head)
            {
                //insert node at head
                head -> prev = node;
                node -> next = head;
                node -> prev = nullptr;
                head = node;
                return true;
            }
            curr -> prev -> next = node;
            node -> prev = curr -> prev;
            node -> next = curr;
            curr -> prev = node;
            return true;
        }
        curr = curr -> next;
    }
    //insert node at tail
    tail -> next = node;
    node -> prev = tail;
    node -> next = nullptr;
    tail = node;
    return true;
}

void songList::remove(song* s)
{
    dllNode* node = s->myNode;
    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    }
    else if (node == head) {
        head = node->next;
        head->prev = nullptr;
    }
    else if(node == tail) {
        tail = node->prev; 
        tail->next = nullptr;
    }
    else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    delete node; 
    s->myNode = nullptr;
}


    
void songList::print()
{
    dllNode* curr = head;
    while(curr != nullptr)
    {
        std::cout << curr -> data -> id << " " << curr -> data -> title << " has been listened to for " << curr -> data -> time << " seconds" << std::endl;
        curr = curr -> next;
    }
    return;
}


song* songList::findById(unsigned int id)
{
    dllNode* curr = head;
    while(curr != nullptr)
    {
        if(curr->data->id == id) return curr->data;
        curr = curr->next;
    }
    return nullptr;
}
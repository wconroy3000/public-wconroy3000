#pragma once
#include "bst.h"
#include <string>

class bstListen {
    private:
        bst* root;

    public:
        bstListen();
	
    song* remove(std::string title, bst*& curr);
};

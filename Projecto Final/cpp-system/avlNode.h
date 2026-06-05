#ifndef AVLNODE_H
#define AVLNODE_H

#include "student.h"

class AVLNode {

public:

    Student* student;

    AVLNode* left;
    AVLNode* right;

    int height;

    AVLNode(Student* s) {

        student = s;

        left = nullptr;
        right = nullptr;

        height = 1;
    }
};

#endif
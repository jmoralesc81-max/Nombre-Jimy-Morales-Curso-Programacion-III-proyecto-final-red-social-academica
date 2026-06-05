#ifndef STUDENTNODE_H
#define STUDENTNODE_H

#include "student.h"

class StudentNode {

public:

    Student* student;

    StudentNode* next;

    StudentNode(Student* s) {
        student = s;
        next = nullptr;
    }
};

#endif
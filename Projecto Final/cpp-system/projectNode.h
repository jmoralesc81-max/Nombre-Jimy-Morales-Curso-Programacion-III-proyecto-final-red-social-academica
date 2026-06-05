#ifndef PROJECTNODE_H
#define PROJECTNODE_H

#include "project.h"

class ProjectNode {

public:

    Project data;
    ProjectNode* next;

    ProjectNode(Project project) {
        data = project;
        next = nullptr;
    }
};

#endif
#ifndef PROJECTLIST_H
#define PROJECTLIST_H

#include <iostream>
#include "projectNode.h"

using namespace std;

class ProjectList {

private:
    ProjectNode* head;

public:

    ProjectList() {
        head = nullptr;
    }

    bool addProject(Project project) {
        ProjectNode* temp = head;

        while(temp != nullptr) {
            if(temp->data.project_id == project.project_id) return false;
            temp = temp->next;
        }

        ProjectNode* newNode = new ProjectNode(project);

        if(head == nullptr) {
            head = newNode;
        } else {
            temp = head;
            while(temp->next != nullptr) temp = temp->next;
            temp->next = newNode;
        }

        return true;
    }

    Project* searchProject(int project_id) {
        ProjectNode* temp = head;

        while(temp != nullptr) {
            if(temp->data.project_id == project_id) return &temp->data;
            temp = temp->next;
        }

        return nullptr;
    }

    bool removeProject(int project_id) {
        if(head == nullptr) return false;

        if(head->data.project_id == project_id) {
            ProjectNode* toDelete = head;
            head = head->next;
            delete toDelete;
            return true;
        }

        ProjectNode* current = head;

        while(current->next != nullptr) {
            if(current->next->data.project_id == project_id) {
                ProjectNode* toDelete = current->next;
                current->next = toDelete->next;
                delete toDelete;
                return true;
            }
            current = current->next;
        }

        return false;
    }

    void displayProjects() {
        if(head == nullptr) {
            cout << "No hay proyectos." << endl;
            return;
        }

        ProjectNode* temp = head;

        while(temp != nullptr) {
            cout << "ID: "     << temp->data.project_id      << endl;
            cout << "Titulo: " << temp->data.title            << endl;
            cout << "Desc: "   << temp->data.description      << endl;
            cout << "Anio: "   << temp->data.completion_year  << endl;
            cout << "----------------------" << endl;
            temp = temp->next;
        }
    }

    int getCount() {
        int count = 0;
        ProjectNode* temp = head;
        while(temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }
};

#endif
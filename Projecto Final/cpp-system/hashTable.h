#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include "studentNode.h"

using namespace std;

class HashTable {

private:

    static const int TABLE_SIZE = 20011;

    StudentNode* table[TABLE_SIZE];

    int collisions;
    int elements;

public:

    HashTable() {

        for(int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }

        collisions = 0;
        elements = 0;
    }

    int hashFunction(int student_id) {
        return student_id % TABLE_SIZE;
    }

    void insert(Student* student) {

        int index = hashFunction(student->student_id);

        StudentNode* current = table[index];

        while(current != nullptr) {

            if(current->student->student_id == student->student_id) {

                cout << "Error: ID duplicado." << endl;
                return;
            }

            current = current->next;
        }

        StudentNode* newNode =
            new StudentNode(student);

        if(table[index] == nullptr) {

            table[index] = newNode;

        } else {

            collisions++;

            current = table[index];

            while(current->next != nullptr) {

                current = current->next;
            }

            current->next = newNode;
        }

        elements++;
    }

    Student* search(int student_id) {

        int index =
            hashFunction(student_id);

        StudentNode* current =
            table[index];

        while(current != nullptr) {

            if(current->student->student_id
               == student_id) {

                return current->student;
            }

            current = current->next;
        }

        return nullptr;
    }

    bool remove(int student_id) {

        int index =
            hashFunction(student_id);

        StudentNode* current =
            table[index];

        StudentNode* previous =
            nullptr;

        while(current != nullptr) {

            if(current->student->student_id
               == student_id) {

                if(previous == nullptr) {

                    table[index] =
                        current->next;

                } else {

                    previous->next =
                        current->next;
                }

                delete current;

                elements--;

                return true;
            }

            previous = current;
            current = current->next;
        }

        return false;
    }

    int getCollisions() {

        return collisions;
    }

    int getElements() {

        return elements;
    }

    float getLoadFactor() {

        return (float)elements /
               TABLE_SIZE;
    }

    vector<Student*> getAllStudents() {

        vector<Student*> students;

        for(int i = 0;
            i < TABLE_SIZE;
            i++) {

            StudentNode* current =
                table[i];

            while(current != nullptr) {

                students.push_back(
                    current->student
                );

                current =
                    current->next;
            }
        }

        return students;
    }

};

#endif
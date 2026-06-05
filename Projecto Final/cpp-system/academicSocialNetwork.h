#ifndef ACADEMICSOCIALNETWORK_H
#define ACADEMICSOCIALNETWORK_H

#include <iostream>
#include <vector>
#include <chrono>
#include "hashTable.h"
#include "avlTree.h"
#include "graph.h"
#include "requestQueue.h"
#include "csvLoader.h"

using namespace std;

class AcademicSocialNetwork {

private:

    HashTable hashTable;
    AVLTree rankingTree;
    Graph graph;
    RequestQueue requestQueue;
    double loadTimeMs;

public:

    AcademicSocialNetwork() {
        loadTimeMs = 0;
    }

    void loadStudents(string filename) {
        auto start = chrono::high_resolution_clock::now();

        CSVLoader::loadStudents(filename, hashTable);

        vector<Student*> students = hashTable.getAllStudents();
        for(Student* student : students) {
            rankingTree.insert(student);
        }

        auto end = chrono::high_resolution_clock::now();
        loadTimeMs = chrono::duration<double, milli>(end - start).count();

        cout << "Estudiantes cargados correctamente." << endl;
    }

    void addStudent(Student* student) {
        hashTable.insert(student);
        rankingTree.insert(student);
    }

    void removeStudent(int id) {
        Student* student = hashTable.search(id);

        if(student == nullptr) {
            cout << "Estudiante no encontrado." << endl;
            return;
        }

        hashTable.remove(id);

        vector<Student*> students = hashTable.getAllStudents();
        rankingTree = AVLTree();
        for(Student* s : students) {
            rankingTree.insert(s);
        }

        cout << "Estudiante eliminado correctamente." << endl;
    }

    bool connectStudents(int id1, int id2) {
        return graph.addConnection(id1, id2);
    }

    int getTotalProjects() {
        vector<Student*> students = hashTable.getAllStudents();
        int total = 0;
        for(Student* s : students) {
            total += s->projects.getCount();
        }
        return total;
    }

    void showStats() {
        cout << "\n=== ESTADISTICAS ===" << endl;
        cout << "Estudiantes cargados:  " << hashTable.getElements()          << endl;
        cout << "Conexiones creadas:    " << graph.getTotalConnections()       << endl;
        cout << "Proyectos registrados: " << getTotalProjects()                << endl;
        cout << "Colisiones hash:       " << hashTable.getCollisions()         << endl;
        cout << "Factor de carga:       " << hashTable.getLoadFactor()         << endl;
        cout << "Altura AVL:            " << rankingTree.getHeight()           << endl;
        cout << "Tiempo de carga:       " << loadTimeMs << " ms"               << endl;
    }

    HashTable& getHashTable()       { return hashTable;    }
    AVLTree& getAVLTree()           { return rankingTree;  }
    Graph& getGraph()               { return graph;        }
    RequestQueue& getRequestQueue() { return requestQueue; }
};

#endif
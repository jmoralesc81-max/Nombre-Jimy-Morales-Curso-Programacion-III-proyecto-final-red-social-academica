#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "hashTable.h"
#include "avlTree.h"
#include "graph.h"

using namespace std;

class Benchmark {

private:

    static vector<Student*> generateStudents(int count) {
        vector<Student*> students;
        for(int i = 0; i < count; i++) {
            students.push_back(new Student(
                i + 1,
                "Estudiante " + to_string(i + 1),
                "Ingenieria",
                (i % 10) + 1,
                70.0f + (i % 30),
                i % 1000
            ));
        }
        return students;
    }

public:

    static void run(int records = 10000) {

        cout << "\n=== BENCHMARK C++ (" << records << " registros) ===" << endl;

        vector<Student*> students = generateStudents(records);

        HashTable hashTable;

        auto start = chrono::high_resolution_clock::now();
        for(Student* s : students) hashTable.insert(s);
        auto end = chrono::high_resolution_clock::now();
        double hashInsert = chrono::duration<double, milli>(end - start).count();

        start = chrono::high_resolution_clock::now();
        for(int i = 0; i < records; i++) hashTable.search(i + 1);
        end = chrono::high_resolution_clock::now();
        double hashSearch = chrono::duration<double, milli>(end - start).count();

        cout << "Hash Insert:   " << hashInsert << " ms" << endl;
        cout << "Hash Search:   " << hashSearch << " ms" << endl;

        AVLTree avlTree;

        start = chrono::high_resolution_clock::now();
        for(Student* s : students) avlTree.insert(s);
        end = chrono::high_resolution_clock::now();
        double avlInsert = chrono::duration<double, milli>(end - start).count();

        start = chrono::high_resolution_clock::now();
        avlTree.showRankingSilent();
        end = chrono::high_resolution_clock::now();
        double avlTraversal = chrono::duration<double, milli>(end - start).count();

        cout << "AVL Insert:    " << avlInsert    << " ms" << endl;
        cout << "AVL Traversal: " << avlTraversal << " ms" << endl;

        Graph graph;
        for(int i = 1; i < records; i++) graph.addConnection(i, i + 1);

        start = chrono::high_resolution_clock::now();
        graph.BFSSilent(1);
        end = chrono::high_resolution_clock::now();
        double bfsTime = chrono::duration<double, milli>(end - start).count();

        start = chrono::high_resolution_clock::now();
        graph.DFSSilent(1);
        end = chrono::high_resolution_clock::now();
        double dfsTime = chrono::duration<double, milli>(end - start).count();

        cout << "BFS:           " << bfsTime << " ms" << endl;
        cout << "DFS:           " << dfsTime << " ms" << endl;

        ofstream file("cpp_results.csv");
        file << "language,operation,structure,records,time_ms\n";
        file << "C++,insert,HashTable,"  << records << "," << hashInsert   << "\n";
        file << "C++,search,HashTable,"  << records << "," << hashSearch   << "\n";
        file << "C++,insert,AVL,"        << records << "," << avlInsert    << "\n";
        file << "C++,traversal,AVL,"     << records << "," << avlTraversal << "\n";
        file << "C++,bfs,Graph,"         << records << "," << bfsTime      << "\n";
        file << "C++,dfs,Graph,"         << records << "," << dfsTime      << "\n";
        file.close();

        cout << "\ncpp_results.csv generado correctamente." << endl;

        for(Student* s : students) delete s;
    }
};

#endif
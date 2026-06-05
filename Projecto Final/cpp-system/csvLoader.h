#ifndef CSVLOADER_H
#define CSVLOADER_H

#include <fstream>
#include <sstream>
#include <string>
#include "hashTable.h"

using namespace std;

class CSVLoader {

public:

    static void loadStudents(
        string filename,
        HashTable& hash
    ) {

        ifstream file(filename);

        if(!file.is_open()) {
            cout << "Error al abrir el archivo CSV." << endl;
            return;
        }

        string line;

        getline(file, line);

        while(getline(file, line)) {

            stringstream ss(line);

            string student_id;
            string full_name;
            string career;
            string semester;
            string gpa;
            string skill_score;

            getline(ss, student_id, ',');
            getline(ss, full_name, ',');
            getline(ss, career, ',');
            getline(ss, semester, ',');
            getline(ss, gpa, ',');
            getline(ss, skill_score, ',');

            Student* student = new Student(
                stoi(student_id),
                full_name,
                career,
                stoi(semester),
                stof(gpa),
                stoi(skill_score)
            );

            hash.insert(student);
        }

        file.close();
    }
};

#endif
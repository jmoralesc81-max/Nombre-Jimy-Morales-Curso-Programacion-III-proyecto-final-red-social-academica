#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "projectList.h"

using namespace std;

class Student {

public:

    int student_id;
    string full_name;
    string career;
    int semester;
    float gpa;
    int skill_score;

    ProjectList projects;

    Student() {
        student_id = 0;
        semester = 0;
        gpa = 0;
        skill_score = 0;
    }

    Student(
        int id,
        string name,
        string car,
        int sem,
        float avg,
        int score
    ) {

        student_id = id;
        full_name = name;
        career = car;
        semester = sem;
        gpa = avg;
        skill_score = score;
    }
};

#endif
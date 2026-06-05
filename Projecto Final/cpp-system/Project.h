#ifndef PROJECT_H
#define PROJECT_H

#include <string>

using namespace std;

class Project {
public:
    int project_id;
    string title;
    string description;
    int completion_year;

    Project() {
        project_id = 0;
        completion_year = 0;
    }

    Project(int id, string t, string d, int year) {
        project_id = id;
        title = t;
        description = d;
        completion_year = year;
    }
};

#endif
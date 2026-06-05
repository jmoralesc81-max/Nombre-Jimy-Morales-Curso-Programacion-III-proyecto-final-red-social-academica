#include <iostream>
#include "academicSocialNetwork.h"
#include "benchmark.h"

using namespace std;

int main() {

    AcademicSocialNetwork network;

    int option;

    do {

        cout << "\n===== RED SOCIAL ACADEMICA =====" << endl;
        cout << "1.  Cargar estudiantes desde CSV"        << endl;
        cout << "2.  Registrar estudiante"                << endl;
        cout << "3.  Buscar estudiante por ID"            << endl;
        cout << "4.  Eliminar estudiante"                 << endl;
        cout << "5.  Agregar proyecto a estudiante"       << endl;
        cout << "6.  Mostrar proyectos de estudiante"     << endl;
        cout << "7.  Conectar estudiantes"                << endl;
        cout << "8.  Verificar conexion"                  << endl;
        cout << "9.  Mostrar conexiones de estudiante"    << endl;
        cout << "10. Recorrer red con BFS"                << endl;
        cout << "11. Recorrer red con DFS"                << endl;
        cout << "12. Mostrar ranking academico"           << endl;
        cout << "13. Mostrar estadisticas"                << endl;
        cout << "14. Generar benchmark C++"               << endl;
        cout << "15. Salir"                               << endl;

        cout << "\nOpcion: ";
        cin >> option;

        switch(option) {

            case 1:
                network.loadStudents("estudiantes.csv");
                break;

            case 2: {
                int id, semestre, skill;
                string nombre, carrera;
                float promedio;

                cout << "\nID: ";        cin >> id;
                cin.ignore();
                cout << "Nombre: ";      getline(cin, nombre);
                cout << "Carrera: ";     getline(cin, carrera);
                cout << "Semestre: ";    cin >> semestre;
                cout << "Promedio: ";    cin >> promedio;
                cout << "Skill Score: "; cin >> skill;

                network.addStudent(new Student(id, nombre, carrera, semestre, promedio, skill));
                cout << "Estudiante registrado correctamente." << endl;
                break;
            }

            case 3: {
                int id;
                cout << "\nIngrese ID: "; cin >> id;

                Student* s = network.getHashTable().search(id);

                if(s != nullptr) {
                    cout << "\nNombre: "    << s->full_name   << endl;
                    cout << "Carrera: "     << s->career      << endl;
                    cout << "Semestre: "    << s->semester    << endl;
                    cout << "Promedio: "    << s->gpa         << endl;
                    cout << "Skill Score: " << s->skill_score << endl;
                } else {
                    cout << "Estudiante no encontrado." << endl;
                }
                break;
            }

            case 4: {
                int id;
                cout << "\nIngrese ID a eliminar: "; cin >> id;
                network.removeStudent(id);
                break;
            }

            case 5: {
                int studentId;
                cout << "\nID del estudiante: "; cin >> studentId;

                Student* s = network.getHashTable().search(studentId);
                if(s == nullptr) { cout << "Estudiante no encontrado." << endl; break; }

                int projectId, year;
                string title, description;

                cout << "ID Proyecto: ";  cin >> projectId;
                cin.ignore();
                cout << "Titulo: ";       getline(cin, title);
                cout << "Descripcion: ";  getline(cin, description);
                cout << "Anio: ";         cin >> year;

                if(s->projects.addProject(Project(projectId, title, description, year))) {
                    cout << "Proyecto agregado correctamente." << endl;
                } else {
                    cout << "Proyecto duplicado." << endl;
                }
                break;
            }

            case 6: {
                int studentId;
                cout << "\nID del estudiante: "; cin >> studentId;

                Student* s = network.getHashTable().search(studentId);
                if(s == nullptr) { cout << "Estudiante no encontrado." << endl; break; }

                cout << "\n=== PROYECTOS ===" << endl;
                s->projects.displayProjects();
                break;
            }

            case 7: {
                int id1, id2;
                cout << "\nPrimer ID: "; cin >> id1;
                cout << "Segundo ID: ";  cin >> id2;

                if(network.connectStudents(id1, id2)) {
                    cout << "Conexion creada correctamente." << endl;
                }
                break;
            }

            case 8: {
                int id1, id2;
                cout << "\nPrimer ID: "; cin >> id1;
                cout << "Segundo ID: ";  cin >> id2;

                if(network.getGraph().areConnected(id1, id2)) {
                    cout << "SI estan conectados." << endl;
                } else {
                    cout << "NO estan conectados." << endl;
                }
                break;
            }

            case 9: {
                int id;
                cout << "\nIngrese ID: "; cin >> id;
                network.getGraph().showConnections(id);
                break;
            }

            case 10: {
                int id;
                cout << "\nID inicial: "; cin >> id;
                network.getGraph().BFS(id);
                break;
            }

            case 11: {
                int id;
                cout << "\nID inicial: "; cin >> id;
                network.getGraph().DFS(id);
                break;
            }

            case 12:
                network.getAVLTree().showRanking();
                break;

            case 13:
                network.showStats();
                break;

            case 14:
                Benchmark::run(10000);
                break;

            case 15:
                cout << "Saliendo..." << endl;
                break;

            default:
                cout << "Opcion invalida." << endl;
        }

    } while(option != 15);

    return 0;
}
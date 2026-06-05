#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

using namespace std;

struct AdjNode {
    int student_id;
    AdjNode* next;

    AdjNode(int id) {
        student_id = id;
        next = nullptr;
    }
};

struct AdjMapNode {
    int key;
    AdjNode* neighbors;
    AdjMapNode* next;

    AdjMapNode(int k) {
        key = k;
        neighbors = nullptr;
        next = nullptr;
    }
};

struct QueueNode {
    int value;
    QueueNode* next;

    QueueNode(int v) {
        value = v;
        next = nullptr;
    }
};

struct ManualQueue {
    QueueNode* front;
    QueueNode* rear;

    ManualQueue() {
        front = nullptr;
        rear = nullptr;
    }

    void push(int v) {
        QueueNode* node = new QueueNode(v);
        if(rear == nullptr) {
            front = rear = node;
        } else {
            rear->next = node;
            rear = node;
        }
    }

    int pop() {
        if(front == nullptr) return -1;
        int val = front->value;
        QueueNode* temp = front;
        front = front->next;
        if(front == nullptr) rear = nullptr;
        delete temp;
        return val;
    }

    bool empty() {
        return front == nullptr;
    }
};

struct StackNode {
    int value;
    StackNode* next;

    StackNode(int v) {
        value = v;
        next = nullptr;
    }
};

struct ManualStack {
    StackNode* top;

    ManualStack() {
        top = nullptr;
    }

    void push(int v) {
        StackNode* node = new StackNode(v);
        node->next = top;
        top = node;
    }

    int pop() {
        if(top == nullptr) return -1;
        int val = top->value;
        StackNode* temp = top;
        top = top->next;
        delete temp;
        return val;
    }

    bool empty() {
        return top == nullptr;
    }
};

struct VisitedNode {
    int value;
    VisitedNode* next;

    VisitedNode(int v) {
        value = v;
        next = nullptr;
    }
};

struct VisitedList {
    VisitedNode* head;

    VisitedList() {
        head = nullptr;
    }

    void insert(int v) {
        VisitedNode* node = new VisitedNode(v);
        node->next = head;
        head = node;
    }

    bool contains(int v) {
        VisitedNode* current = head;
        while(current != nullptr) {
            if(current->value == v) return true;
            current = current->next;
        }
        return false;
    }
};

class Graph {

private:

    static const int MAP_SIZE = 20011;
    AdjMapNode* map[MAP_SIZE];
    int totalConnections;

    int hashKey(int id) {
        return id % MAP_SIZE;
    }

    AdjMapNode* getMapNode(int id) {
        int index = hashKey(id);
        AdjMapNode* current = map[index];
        while(current != nullptr) {
            if(current->key == id) return current;
            current = current->next;
        }
        return nullptr;
    }

    AdjMapNode* getOrCreateMapNode(int id) {
        int index = hashKey(id);
        AdjMapNode* current = map[index];
        while(current != nullptr) {
            if(current->key == id) return current;
            current = current->next;
        }
        AdjMapNode* newNode = new AdjMapNode(id);
        newNode->next = map[index];
        map[index] = newNode;
        return newNode;
    }

    void addNeighbor(int from, int to) {
        AdjMapNode* node = getOrCreateMapNode(from);
        AdjNode* neighbor = new AdjNode(to);
        neighbor->next = node->neighbors;
        node->neighbors = neighbor;
    }

    bool hasNeighbor(int from, int to) {
        AdjMapNode* node = getMapNode(from);
        if(node == nullptr) return false;
        AdjNode* current = node->neighbors;
        while(current != nullptr) {
            if(current->student_id == to) return true;
            current = current->next;
        }
        return false;
    }

public:

    Graph() {
        for(int i = 0; i < MAP_SIZE; i++) {
            map[i] = nullptr;
        }
        totalConnections = 0;
    }

    bool addConnection(int student1, int student2) {
        if(student1 == student2) {
            cout << "No se puede conectar un estudiante consigo mismo." << endl;
            return false;
        }

        if(hasNeighbor(student1, student2)) {
            cout << "Conexion duplicada." << endl;
            return false;
        }

        addNeighbor(student1, student2);
        addNeighbor(student2, student1);
        totalConnections++;
        return true;
    }

    void showConnections(int student_id) {
        cout << "\nConexiones de " << student_id << ":" << endl;

        AdjMapNode* node = getMapNode(student_id);

        if(node == nullptr || node->neighbors == nullptr) {
            cout << "No tiene conexiones." << endl;
            return;
        }

        AdjNode* current = node->neighbors;
        while(current != nullptr) {
            cout << current->student_id << endl;
            current = current->next;
        }
    }

    bool areConnected(int student1, int student2) {
        return hasNeighbor(student1, student2);
    }

    int getTotalConnections() {
        return totalConnections;
    }

    void BFS(int start) {
        VisitedList visited;
        ManualQueue q;

        visited.insert(start);
        q.push(start);

        cout << "\n=== BFS ===" << endl;

        while(!q.empty()) {
            int current = q.pop();
            cout << current << " ";

            AdjMapNode* node = getMapNode(current);
            if(node == nullptr) continue;

            AdjNode* neighbor = node->neighbors;
            while(neighbor != nullptr) {
                if(!visited.contains(neighbor->student_id)) {
                    visited.insert(neighbor->student_id);
                    q.push(neighbor->student_id);
                }
                neighbor = neighbor->next;
            }
        }

        cout << endl;
    }

    void DFS(int start) {
        VisitedList visited;
        ManualStack s;

        s.push(start);

        cout << "\n=== DFS ===" << endl;

        while(!s.empty()) {
            int current = s.pop();

            if(visited.contains(current)) continue;

            visited.insert(current);
            cout << current << " ";

            AdjMapNode* node = getMapNode(current);
            if(node == nullptr) continue;

            AdjNode* neighbor = node->neighbors;
            while(neighbor != nullptr) {
                if(!visited.contains(neighbor->student_id)) {
                    s.push(neighbor->student_id);
                }
                neighbor = neighbor->next;
            }
        }

        cout << endl;
    }

    void BFSSilent(int start) {
        VisitedList visited;
        ManualQueue q;
        visited.insert(start);
        q.push(start);
        while(!q.empty()) {
            int current = q.pop();
            AdjMapNode* node = getMapNode(current);
            if(node == nullptr) continue;
            AdjNode* neighbor = node->neighbors;
            while(neighbor != nullptr) {
                if(!visited.contains(neighbor->student_id)) {
                    visited.insert(neighbor->student_id);
                    q.push(neighbor->student_id);
                }
                neighbor = neighbor->next;
            }
        }
    }

    void DFSSilent(int start) {
        VisitedList visited;
        ManualStack s;
        s.push(start);
        while(!s.empty()) {
            int current = s.pop();
            if(visited.contains(current)) continue;
            visited.insert(current);
            AdjMapNode* node = getMapNode(current);
            if(node == nullptr) continue;
            AdjNode* neighbor = node->neighbors;
            while(neighbor != nullptr) {
                if(!visited.contains(neighbor->student_id)) {
                    s.push(neighbor->student_id);
                }
                neighbor = neighbor->next;
            }
        }
    }
};

#endif
#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <iostream>
#include "connectionRequest.h"

using namespace std;

struct RequestNode {
    ConnectionRequest data;
    RequestNode* next;

    RequestNode(ConnectionRequest r) {
        data = r;
        next = nullptr;
    }
};

class RequestQueue {

private:

    RequestNode* front;
    RequestNode* rear;
    int count;

public:

    RequestQueue() {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    void addRequest(int sender, int receiver) {
        ConnectionRequest request(sender, receiver);
        RequestNode* node = new RequestNode(request);

        if(rear == nullptr) {
            front = rear = node;
        } else {
            rear->next = node;
            rear = node;
        }

        count++;
        cout << "Solicitud agregada." << endl;
    }

    void processRequest() {
        if(front == nullptr) {
            cout << "No hay solicitudes pendientes." << endl;
            return;
        }

        ConnectionRequest request = front->data;

        RequestNode* temp = front;
        front = front->next;
        if(front == nullptr) rear = nullptr;
        delete temp;
        count--;

        cout << "Procesando solicitud: "
             << request.sender_id
             << " -> "
             << request.receiver_id
             << endl;
    }

    void showPendingRequests() {
        if(front == nullptr) {
            cout << "No hay solicitudes pendientes." << endl;
            return;
        }

        cout << "\n=== SOLICITUDES PENDIENTES ===" << endl;

        RequestNode* current = front;
        while(current != nullptr) {
            cout << current->data.sender_id
                 << " -> "
                 << current->data.receiver_id
                 << endl;
            current = current->next;
        }
    }

    int getPendingCount() {
        return count;
    }
};

#endif
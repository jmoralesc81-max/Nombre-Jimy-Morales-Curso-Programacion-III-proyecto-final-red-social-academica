#ifndef CONNECTIONREQUEST_H
#define CONNECTIONREQUEST_H

class ConnectionRequest {

public:

    int sender_id;
    int receiver_id;

    ConnectionRequest() {

        sender_id = 0;
        receiver_id = 0;
    }

    ConnectionRequest(
        int sender,
        int receiver
    ) {

        sender_id = sender;
        receiver_id = receiver;
    }
};

#endif
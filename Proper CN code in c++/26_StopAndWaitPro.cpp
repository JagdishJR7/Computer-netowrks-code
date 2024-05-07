#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h> // for sleep()

using namespace std;

const int PACKET_SIZE = 1024;
const int TIMEOUT = 2; // in seconds

// Simulate sending a packet over the network
bool sendPacket(const char* packet) {
    // Simulate packet loss by generating a random number
    // If the random number is less than 0.3 (30% probability), consider the packet lost
    float random = static_cast<float>(rand()) / RAND_MAX;
    if (random < 0.3) {
        cout << "Packet lost!" << endl;
        return false; // Packet lost
    }

    // Simulate network delay
    sleep(1);

    cout << "Packet successfully sent: " << packet << endl;
    return true; // Packet successfully sent
}

// Simulate receiving an acknowledgement (ACK) from the receiver
bool receiveAck() {
    // Simulate network delay
    sleep(1);

    // Simulate ACK loss by generating a random number
    // If the random number is less than 0.3 (30% probability), consider the ACK lost
    float random = static_cast<float>(rand()) / RAND_MAX;
    if (random < 0.3) {
        cout << "ACK lost!" << endl;
        return false; // ACK lost
    }

    cout << "ACK received." << endl;
    return true; // ACK received
}

// Stop-and-Wait protocol implementation
void stopAndWait(const char* data) {
    cout << "Sending data: " << data << endl;

    // Send the packet
    bool packetSent = sendPacket(data);
    if (!packetSent) {
        cout << "Retransmitting data: " << data << endl;
        sendPacket(data); // Retransmit the packet if it's lost
    }

    // Wait for ACK
    bool ackReceived = false;
    while (!ackReceived) {
        ackReceived = receiveAck();
        if (!ackReceived) {
            cout << "Timeout! Retransmitting data: " << data << endl;
            sendPacket(data); // Retransmit the packet if ACK is lost or timeout occurs
        }
    }

    cout << "Data transmission completed successfully." << endl;
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Data to be transmitted
    const char* data = "Hello, world!";

    // Perform data transmission using Stop-and-Wait protocol
    stopAndWait(data);

    return 0;
}

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h> // for sleep()

using namespace std;

const int PACKET_SIZE = 1024;
const int WINDOW_SIZE = 4;
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

// Go-Back-N protocol implementation
void goBackN(const vector<string>& data) {
    int N = data.size();
    int base = 0;
    int nextSeqNum = 0;

    while (base < N) {
        // Send packets within the window
        for (int i = base; i < min(base + WINDOW_SIZE, N); ++i) {
            cout << "Sending data: " << data[i] << endl;
            bool packetSent = sendPacket(data[i].c_str());
            if (!packetSent) {
                cout << "Retransmitting data: " << data[i] << endl;
                sendPacket(data[i].c_str()); // Retransmit the packet if it's lost
            }
        }

        // Wait for ACK for the packets within the window
        for (int i = base; i < min(base + WINDOW_SIZE, N); ++i) {
            bool ackReceived = false;
            while (!ackReceived) {
                ackReceived = receiveAck();
                if (!ackReceived) {
                    cout << "Timeout! Retransmitting data: " << data[i] << endl;
                    sendPacket(data[i].c_str()); // Retransmit the packet if ACK is lost or timeout occurs
                }
            }
        }

        // Move the window
        base += WINDOW_SIZE;
    }

    cout << "Data transmission completed successfully." << endl;
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Data to be transmitted
    vector<string> data = {"Packet 1", "Packet 2", "Packet 3", "Packet 4", "Packet 5"};

    // Perform data transmission using Go-Back-N protocol
    goBackN(data);

    return 0;
}

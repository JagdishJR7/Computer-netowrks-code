#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
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
bool receiveAck(const string& ackPacket, const unordered_set<int>& receivedPackets) {
    // Simulate network delay
    sleep(1);

    // Extract sequence number from ACK packet
    int seqNum = stoi(ackPacket.substr(5));

    // Check if the ACK packet corresponds to a packet that was sent
    if (receivedPackets.find(seqNum) != receivedPackets.end()) {
        cout << "ACK received for packet with sequence number: " << seqNum << endl;
        return true; // ACK received for a valid packet
    }

    cout << "Invalid ACK received!" << endl;
    return false; // Invalid ACK received
}

// Selective Repeat protocol implementation
void selectiveRepeat(const vector<string>& data) {
    int N = data.size();
    int base = 0;
    int nextSeqNum = 0;

    unordered_set<int> receivedPackets;

    while (base < N) {
        // Send packets within the window
        for (int i = base; i < min(base + WINDOW_SIZE, N); ++i) {
            cout << "Sending data: " << data[i] << endl;
            bool packetSent = sendPacket(data[i].c_str());
            if (packetSent) {
                nextSeqNum++;
            }
        }

        // Wait for ACK for the packets within the window
        for (int i = base; i < min(base + WINDOW_SIZE, N); ++i) {
            string ackPacket;
            bool ackReceived = false;
            while (!ackReceived) {
                // Simulate receiving an ACK packet
                cout << "Waiting for ACK for packet with sequence number: " << i << endl;
                ackPacket = "ACK" + to_string(i);
                ackReceived = receiveAck(ackPacket, receivedPackets);
            }
            receivedPackets.insert(i);
        }

        // Move the window
        base = nextSeqNum;
    }

    cout << "Data transmission completed successfully." << endl;
}

int main() {
    // Seed the random number generator
    srand(time(NULL));

    // Data to be transmitted
    vector<string> data = {"Packet 0", "Packet 1", "Packet 2", "Packet 3", "Packet 4", "Packet 5"};

    // Perform data transmission using Selective Repeat protocol
    selectiveRepeat(data);

    return 0;
}

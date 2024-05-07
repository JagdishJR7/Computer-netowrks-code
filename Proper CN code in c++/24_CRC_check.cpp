#include <iostream>
#include <string>

using namespace std;

// Function to perform CRC checksum calculation
string crc(string data, string polynomial) {
    int data_length = data.length();
    int polynomial_length = polynomial.length();

    // Appending zeros to the end of the data
    string padded_data = data;
    for (int i = 0; i < polynomial_length - 1; ++i) {
        padded_data += '0';
    }

    // Performing CRC division
    for (int i = 0; i <= padded_data.length() - polynomial_length;) {
        for (int j = 0; j < polynomial_length; ++j) {
            padded_data[i + j] = padded_data[i + j] == polynomial[j] ? '0' : '1';
        }
        while (i < padded_data.length() && padded_data[i] != '1') {
            ++i;
        }
    }

    // Extracting the CRC code
    string crc_code = padded_data.substr(data_length);

    return crc_code;
}

int main() {
    string data, polynomial;

    cout << "Enter the data: ";
    cin >> data;

    cout << "Enter the polynomial: ";
    cin >> polynomial;

    string crc_code = crc(data, polynomial);

    cout << "CRC code: " << crc_code << endl;

    return 0;
}

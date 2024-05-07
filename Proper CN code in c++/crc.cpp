#include <iostream>
#include <vector>

using namespace std;

// Define the generator polynomial
const vector<int> generator_polynomial = {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1};

// Simulate a noisy channel by flipping a random bit
int simulate_noisy_channel(int bit) {
  if (rand() % 2 == 0) {
    return bit ^ 1;
  } else {
    return bit;
  }
}

// Calculate the CRC checksum
vector<int> calculate_crc_checksum(vector<int> data) {
  // Append the generator polynomial to the data
  data.insert(data.end(), generator_polynomial.begin(), generator_polynomial.end());

  // Perform polynomial division
  vector<int> remainder;
  for (int i = 0; i < data.size(); i++) {
    if (data[i] == 1) {
      for (int j = 0; j < generator_polynomial.size(); j++) {
        data[i + j] ^= generator_polynomial[j];
      }
    }
  }

  // The remainder is the CRC checksum
  remainder.assign(data.begin() + data.size() - generator_polynomial.size(), data.end());
  return remainder;
}

// Check if the CRC checksum is valid
bool check_crc_checksum(vector<int> data, vector<int> crc_checksum) {
  for (int i = 0; i < crc_checksum.size(); i++) {
    if (data[i] != crc_checksum[i]) {
      return false;
    }
  }
  return true;
}

int main() {
  // Generate a random data packet
  vector<int> data = {1, 0, 1, 1, 0, 0, 1, 0};

  // Calculate the CRC checksum
  vector<int> crc_checksum = calculate_crc_checksum(data);

  // Simulate a noisy channel
  for (int i = 0; i < data.size(); i++) {
    data[i] = simulate_noisy_channel(data[i]);
  }

  // Check if the CRC checksum is valid
  bool is_valid = check_crc_checksum(data, crc_checksum);

  if (is_valid) {
    cout << "The data packet is valid." << endl;
  } else {
    cout << "The data packet is corrupted." << endl;
  }

  return 0;
}
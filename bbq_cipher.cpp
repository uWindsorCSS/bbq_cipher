#include <algorithm>
#include <cctype>
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

using namespace std;

vector<char> generateCipher();
vector<char> loadCipherFromFile(ifstream& cipher_file);

int main(int argc, char* argv[]) {
  vector<char> cipher;
  if(argc == 2) {
    ifstream cipher_file(argv[1]);
    if(cipher_file) {
      cipher = loadCipherFromFile(cipher_file);
    } else {
      cout << "Failed to open cipher file." << endl;
      return -1;
    }
  } else {
    cipher = generateCipher();
    /* We could have just printed out the cipher in generateCipher()
     * but that would be a naughty side effect */
    for (unsigned i = 0; i < cipher.size(); ++i) {
      cout << "\r\n" << char('a' + i) << "  ->  " << cipher[i] << endl;
    }
    cout << "\r\n\r\n";
  }
  
  for (string message; getline(cin, message); /* empty */) {
    for (const auto& c : message) {
      cout << (isalpha(c) ? cipher[tolower(c) - 'a'] : c);
    }
    cout << "\r\n\r\n\r\n\r\n\r\n";
  }

  return 0;
}

vector<char> generateCipher() {
  vector<char> cipher('z' - 'a' + 1);
  iota(cipher.begin(), cipher.end(), 'a');

  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  mt19937_64 rand_engine(seed);
  shuffle(cipher.begin(), cipher.end(), rand_engine);

  return cipher;
}

vector<char> loadCipherFromFile(ifstream& cipher_file) {
  vector<char> cipher('z' - 'a' + 1);
  for(string pair; getline(cipher_file, pair); /* empty */) {
    cipher[pair.front() - 'a'] = pair.back();
  }
  return cipher;
}

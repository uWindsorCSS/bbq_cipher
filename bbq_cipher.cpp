#include <algorithm>
#include <cctype>
#include <chrono>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
  vector<char> cipher('z' - 'a' + 1);
  iota(cipher.begin(), cipher.end(), 'a');

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  mt19937_64 rand_engine(seed);
  shuffle(cipher.begin(), cipher.end(), rand_engine);

  for (unsigned i = 0; i < cipher.size(); ++i) {
    cout << '\n' << char('a' + i) << "  ->  " << cipher[i] << endl;
  }

  for (string message; getline(cin, message); /* empty */) {
    for (const auto& c : message) {
      cout << (isalpha(c) ? cipher[tolower(c) - 'a'] : c);
    }
    cout << "\n\n\n\n\n";
  }

  return 0;
}

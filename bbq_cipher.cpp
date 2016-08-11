#include <chrono>
#include <random>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <cctype>

using namespace std;

int main(int argc, char * argv[]) {
        vector<string> messages;
        string m;
        while(getline(cin, m)) {
                messages.push_back(m);
        }
        string letters;
        for(char l = 'a'; l <= 'z'; ++l) {
                letters.push_back(l);
        }

        map<char, char> cipher;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        mt19937_64 rand_engine(seed);
        for(char l = 'a';  l <= 'z' && letters.size(); ++l) {
                uniform_int_distribution<int> dist(0, letters.size() - 1);
                int i = dist(rand_engine);
                cipher[l] = letters[i];
                letters.erase(i, 1);
        }
        for(const auto& c : cipher) {
                cout << '\n' << c.first << "  ->  " << c.second << endl;
        }
        cout << "\n\n\n";
        for(const auto& m : messages) {
                for(const auto& c : m) {
                        if(cipher.count(tolower(c))) {
                                cout << cipher[tolower(c)];
                        } else {
                                cout << c;
                        }
                }
                cout << "\n\n\n\n\n";
        }
        return 0;
}

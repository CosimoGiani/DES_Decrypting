#ifndef DES_DECRYPTING_DECRYPTER_H
#define DES_DECRYPTING_DECRYPTER_H

#include <iostream>
#include <vector>

using namespace std;

class Decrypter {

private:
    vector<string> dictionary;
    string salt;

public:
    Decrypter(string dictionary_path, string salt_char);

    // Decryption methods
    vector<long> sequential_decryption(vector<string> hashes, int num_test);
    vector<long> parallel_decryption(vector<string> hashes, int num_test, int num_threads);

    // Utility methods
    string get_word(int position);
    int get_size();

};

#endif //DES_DECRYPTING_DECRYPTER_H

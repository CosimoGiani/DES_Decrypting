#include "Decrypter.h"
#include "omp.h"
#include <crypt.h>
#include <openssl/des.h>
#include <fstream>
#include <chrono>
#include <cstring>

using namespace std;
using namespace chrono;

Decrypter::Decrypter(string dictionary_path, string salt_char) {

    // Read input file
    ifstream dict;
    string word;
    dict.open(dictionary_path);
    if( dict.fail() )
        exit(1);
    // Create dictionary
    while (getline(dict, word)) {
        dictionary.push_back(word);
    }
    dict.close();

    // Set the salt characters
    salt = salt_char;

}

// SEQUENTIAL DECRYPTION
vector<long> Decrypter::sequential_decryption(vector<string> hashes, int num_test) {

    vector<long> decryption_times;
    long total_decryption_time, mean_decryption_time;
    decryption_times.reserve(hashes.size());
    string encrypted_word;

    // For each hash we want to decrypt
    for (int i = 0; i < hashes.size(); i++) {
        total_decryption_time = 0;
        cout << "Working on hash: " << hashes[i] << endl;
        // Execute the tests 'num_test' times
        for (int j = 0; j < num_test; j++) {
            auto start = steady_clock::now();
            // And check for each encrypted word in the dictionary whether the hash matches or not
            for (int k = 0; k < dictionary.size(); k++) {
                encrypted_word = crypt(dictionary[k].c_str(), salt.c_str());
                if (strcmp(encrypted_word.c_str(), hashes[i].c_str()) == 0) {
                    break;
                }
            }
            // Calculate for each test the decryption time
            auto end = steady_clock::now();
            auto elapsed = duration_cast<nanoseconds>(end - start).count();
            total_decryption_time += elapsed;
        }
        // Calculate the mean decryption time for n tests on one hash
        mean_decryption_time = total_decryption_time / num_test;
        decryption_times.push_back(mean_decryption_time);
    }
    return decryption_times;

}

// PARALLEL DECRYPTION
vector<long> Decrypter::parallel_decryption(vector<string> hashes, int num_test, int num_threads) {

    vector<long> decryption_times;
    long total_decryption_time, mean_decryption_time;
    string hash;
    char* encrypted_word;
    volatile bool found;
    int words_per_thread = static_cast<int>((double)dictionary.size() / (double)num_threads);
    decryption_times.reserve(hashes.size());

    // For each hash we want to decrypt
    for (int i = 0; i < hashes.size(); i++) {
        hash = hashes[i];
        total_decryption_time = 0;
        // Execute the tests 'num_test' times
        for (int j = 0; j < num_test; j++) {
            found = false;
            auto start = steady_clock::now();
#pragma omp parallel num_threads(num_threads) shared(found) private(encrypted_word) firstprivate(words_per_thread, hash)
            {
                // Chunking, encrypting and comparing
                encrypted_word = (char *) malloc(sizeof(string));
                int thread_num = omp_get_thread_num();
                for (int k = words_per_thread * thread_num; k < (thread_num + 1) * words_per_thread; k++) {
                    if (!found && k < dictionary.size()) {
                        DES_fcrypt(dictionary[k].c_str(), salt.c_str(), encrypted_word);
                        if (strcmp(encrypted_word, hash.c_str()) == 0) {
                            found = true;
                            break;
                        }
                    }
                    else{
                        break;
                    }
                }
            }
            // Calculate for each test the decryption time
            auto end = steady_clock::now();
            auto elapsed= duration_cast<nanoseconds>(end - start).count();
            total_decryption_time += elapsed;
        }
        // Calculate the mean decryption time for n tests on one hash
        mean_decryption_time = total_decryption_time / num_test;
        decryption_times.push_back(mean_decryption_time);
    }
    return decryption_times;

}

// Method for returning a word at a given position
string Decrypter::get_word(int position){
    return dictionary[position];
}

// Method for returning the dictionary's size
int Decrypter::get_size() {
    return dictionary.size();
}

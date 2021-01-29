#ifndef DES_DECRYPTING_UTILS_H
#define DES_DECRYPTING_UTILS_H

#include <iostream>
#include <vector>

using namespace std;

class Utils {

public:
    // Encryption method
    vector<string> words_encryption(vector<string> passwords, string salt);

    // Mean time method
    long get_mean_time(vector<long> times);

    // Speedup methods
    void speedup(std::vector<long> parallel_times, std::vector<long> sequential_times, std::vector<string> passwords);
    void mean_speedup(long sequential_mean_time, vector<long> parallel_times, int num_random_words);

};

#endif //DES_DECRYPTING_UTILS_H

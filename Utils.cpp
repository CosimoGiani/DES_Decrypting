#include "Utils.h"
#include <crypt.h>

using namespace std;

// Method for encrypting a given vector of passwords
vector<string> Utils::words_encryption(std::vector<string> passwords, string salt) {
    vector<string> encrypted_words;
    encrypted_words.reserve(passwords.size());
    string hash;
    for (string & password : passwords) {
        hash = crypt(password.c_str(), salt.c_str());
        encrypted_words.push_back(hash);
        cout << "Password '" << password << "' encrypted with hash: " << hash << endl;
    }
    return encrypted_words;
}

// Method to calculate the mean time
long Utils::get_mean_time(std::vector<long> times) {
    long total_time = 0;
    long mean_time = 0;
    for (int i = 0; i < times.size(); i++) {
        total_time += times[i];
    }
    mean_time = total_time / times.size();
    return mean_time;
}

// Method to calculate the speedup
void Utils::speedup(std::vector<long> parallel_times, std::vector<long> sequential_times, std::vector<string> passwords) {
    for (int i=0; i<passwords.size(); i++) {
        cout << "Speedup for " << passwords[i] << ": " << (float)sequential_times[i] / (float)parallel_times[i] << endl;
    }
    cout << "--------------------------------" << endl;
}

// Method to calculate the mean speedup
void Utils::mean_speedup(long sequential_mean_time, std::vector<long> parallel_times, int num_random_words) {
    long mean_time_parallel = get_mean_time(parallel_times);
    cout << "Mean speedup " << num_random_words << " words: " << (float)sequential_mean_time / (float)mean_time_parallel << endl;
    cout << "--------------------------------" << endl;
}


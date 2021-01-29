#include "Decrypter.h"
#include "Utils.h"

using namespace std;

int main() {

    // Set up for tests
    int num_test, num_random_test, num_random_words;
    cout << "How many defined tests do you want to perform? Type '0' if you want to skip this phase --> ";
    cin >> num_test;
    cout << "How many random tests do you want to perform? Type '0' if you want to skip this phase --> ";
    cin >> num_random_test;
    if (num_random_test) {
        cout << "Enter the number of random words you want to use --> ";
        cin >> num_random_words;
    }

    cout << endl;

    // Some declarations
    vector<long> sequential_times, random_sequential_times, parallel_times, random_parallel_times;
    long random_sequential_mean_time;
    vector<string> passwords, hashes;
    vector<string> random_passwords, random_hashes;
    Utils* util = new Utils();

    // Threads
    vector<int> num_threads = {2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50};

    // Decrypter initialization
    string salt = "a9";
    Decrypter* decrypter = new Decrypter("../dictionary/dictionary.txt", salt);

    // SEQUENTIAL DECRYPTION
    cout << "STARTING SEQUENTIAL DECRYPTION..." << endl;
    // Decryption of specific passwords
    if (num_test > 0) {
        passwords = {"lzd9bs07", "roxy1440", "tri3ple6"};
        hashes = util -> words_encryption(passwords, salt);
        cout << "Executing tests for the words specified..." << endl;
        sequential_times = decrypter -> sequential_decryption(hashes, num_test);
    }
    // Decryption of random passwords
    if (num_random_test > 0) {
        int index;
        int size = decrypter -> get_size();
        cout << "Extracting " << num_random_words << " words randomly..." << endl;
        for (int i = 0; i < num_random_words; i++) {
            index = rand() % size;
            random_passwords.push_back(decrypter -> get_word(index));
        }
        random_hashes = util -> words_encryption(random_passwords, salt);
        cout << "Executing tests for random words..." << endl;
        random_sequential_times = decrypter -> sequential_decryption(random_hashes, num_random_test);
        random_sequential_mean_time = util -> get_mean_time(random_sequential_times);
    }

    cout << endl;

    // PARALLEL DECRYPTION
    cout << "STARTING PARALLEL DECRYPTION..." << endl;
    for (int i = 0; i < num_threads.size(); i++) {
        cout << "**** Working with " << num_threads[i] << " threads ****" << endl;
        // Decryption of chosen passwords
        if(num_test > 0) {
            cout << "-------- Defined tests ---------" << endl;
            parallel_times = decrypter -> parallel_decryption(hashes, num_test, num_threads[i]);
            util -> speedup(parallel_times, sequential_times, passwords);
        }
        // Decryption of random passwords
        if (num_random_test > 0) {
            cout << "--------- Random tests ---------" << endl;
            random_parallel_times = decrypter -> parallel_decryption(random_hashes, num_random_test, num_threads[i]);
            util -> mean_speedup(random_sequential_mean_time, random_parallel_times, num_random_words);
        }
    }

    return 0;

}
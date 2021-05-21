#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

#include "../headers/dictionarycreator.h"
#include "../headers/sentencegenerator.h"
#include "../headers/shitposter.h"
#include "../headers/constants.h"
using namespace std;
namespace fs = std::filesystem;

/* Mode codes */
enum mode { NORMAL, SHITPOST };

string get_source_path();
int choose_option();
string clean(string);

int main () {
    string file_path = get_source_path();
    vector<string> dict;
    get_dictionary(dict, file_path);
    int mode = choose_option();
    if (mode == NORMAL) {
        string stop = "n";
        cout << SEPARATOR << "\n\n\n";
        while (stop != "y") {
            cout << clean(get_sentence(dict)) << "\n\n\n";
            cout << SEPARATOR << " exit? (y/n): ";
            cin >> stop;
            cout << "\n\n";
        }
    }
    else
        do_shitpost(dict);
    return 0;
}

/**
 * This method displays all available files in the
 * default directory, asks user to choose one of them,
 * and returns the name of a chosen file
 */
string get_source_path() {
    cout << "Choose the source file:\n" << SEPARATOR << "\nAvailable files:" << endl;
    int iter = 0;
    vector<string> entries;
    try {
        for (const auto & entry : fs::directory_iterator(DEFAULT_PATH)) {
            cout << "[" << iter << "] " << entry.path() << endl;
            entries.push_back(entry.path());
            iter++;
        }
    } catch (const fs::filesystem_error& e) {
        cout << "Your current directory doesn't contain " << DEFAULT_PATH << endl;
        exit(EXIT_FAILURE);
    }
    unsigned int choice_index;
    cout << "Your choice (default is 0): ";
    cin >> choice_index;
    if (choice_index >= entries.size())
        choice_index = 0;
    return entries[choice_index];
}

/**
 * Asks user what mode to use: normal or shitpost 
 * Returns a chosen value
 */
int choose_option() {
    int result;
    cout << SEPARATOR << "\nYour options are:\n"
         << "[" << NORMAL << "] Normal mode\n"
         << "[" << SHITPOST << "] Shitpost mode\n"
         << "Your choice (default is 0): ";
    cin >> result;
    if (result != NORMAL && result != SHITPOST) result = NORMAL;
    return result;
}

/**
 * Takes a string and removes extra spaces
 */
string clean(string str) {
    string result = "";
    result += str[0];
    for (unsigned int i = 1; i < str.length(); i++) {
        if (str[i] == '\t') /* Replacing tabs with spaces */
            str[i] = ' ';
        if (str[i] == ' ' && str[i-1] == ' ')
            continue;
        result += str[i];
    }
    return result;
}

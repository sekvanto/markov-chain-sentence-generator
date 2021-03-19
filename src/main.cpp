#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

#include "../headers/dictionarycreator.h"
#include "../headers/sentencegenerator.h"
//#include "../headers/shitposter.h"
using namespace std;
namespace fs = std::filesystem;

/* Default directory where source text files are placed */
const string DEFAULT_PATH = "assets/";
/* Default separator between strings ;D */
const string SEPARATOR = "--------------------------------------------------\n";
/* Mode codes */
enum mode { NORMAL, SHITPOST };

string getSourcePath();
int chooseOption();
string clean(string);

int main () {
    string filePath = getSourcePath();
    vector<string> dict;
    getDictionary(dict, filePath);
    int mode = chooseOption();
    if (mode == NORMAL)
        cout << SEPARATOR << clean(getSentence(dict)) << endl;
    else
        //doShitPost();
        cout << "TODO" << endl;
    return 0;
}

/**
 * This method displays all available files in the
 * default directory, asks user to choose one of them,
 * and returns the name of a chosen file
 */
string getSourcePath() {
    cout << "Choose the source file:\n" << SEPARATOR << "Available files:" << endl;
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
    int choice_index;
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
int chooseOption() {
    int result;
    cout << SEPARATOR << "Your options are:\n"
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
    for (int i = 1; i < str.length(); i++) {
        if (str[i] == '\t') /* Replacing tabs with spaces */
            str[i] = ' ';
        if (str[i] == ' ' && str[i-1] == ' ')
            continue;
        result += str[i];
    }
    return result;
}

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "../headers/sentencegenerator.h"
#include "../headers/constants.h"

/**
 * Takes a string and crops it
 */
std::string crop(std::string str) {
    int spaces = 0;
    std::string result = "";
    for (unsigned int i = 0; i < str.length(); i++) {
        if (str[i] == ' ')
            spaces++;
        if (spaces == MAX_SHORT_SEN_LEN)
            break;
        result += str[i];
    }
    return result;
}

/**
 * This method generates short sentences and outputs
 * a few at a time. This continues
 * until user chooses to break the loop
 */
void doShitPost(std::vector<std::string> dict) {
    while (true) {
        std::cout << SEPARATOR;
        for(int i = 0; i < SENTENCES_BLOCK; i++) {
            std::cout << crop(getSentence(dict)) << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(PAUSE));
        }
        std::string choice;
        std::cout << SEPARATOR << "Wanna continue more? ;D\ny/n: ";
        std::cin >> choice;
        if (choice != "y") break;
    }
}

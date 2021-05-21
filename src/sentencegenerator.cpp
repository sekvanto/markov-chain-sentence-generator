#include <iostream>
#include <vector>
#include <ctime>
#include "../headers/constants.h"

std::vector<std::string> make_ngrams(std::vector<std::string>);
std::string build_sentence(std::vector<std::string>);
std::string get_last_word(std::string);
int spaces_in(std::string);
std::string choose_and_crop_ngram(std::vector<std::string>);

/**
 * This method takes dictionary, generates ngrams from words
 * and uses them to build a random sentence
 */
std::string get_sentence(std::vector<std::string> dict) {
    if (ORDER < 2) {
        std::cout << "Order must be 2 or more" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (dict.size() <= ORDER)
        return "";
    std::vector<std::string> ngrams = make_ngrams(dict);
    return (build_sentence(ngrams));
}

/**
 * Takes a dictionary and generates ngrams from it
 */
std::vector<std::string> make_ngrams(std::vector<std::string> dict) {
    std::vector<std::string> result;
    for (unsigned int i = 0; i <= dict.size() - ORDER; i++) {
        std::string ngram = dict[i] + " ";
        for (int j = 1; j < ORDER; j++) {
            ngram += dict[i + j]; /* Add next word(-s) to ngram */
            if (j != ORDER - 1) ngram += " "; /* Add a space to ngram if it's gonna have new words */
        }
        result.push_back(ngram);
    }
    return result;
}

/**
 * Takes ngrams, builds a random sentence out of it
 */
std::string build_sentence(std::vector<std::string> ngrams) {
    std::string result = "";
    srand(static_cast<unsigned>(time(0)));
    auto first_piece = rand() % ngrams.size(); /* Generating first N words randomly */
    result = ngrams[first_piece];
    while (spaces_in(result) < MAX_SEN_LEN) {
        std::vector<std::string> good_ngrams;
        for (std::string ngram : ngrams) { /* Finding ngrams, which start with the current last word */
            std::string last_word = get_last_word(result);
            if (ngram.find(last_word) == 0) /* if ngram starts with last_word, it is good */
                good_ngrams.push_back(ngram);
        }
        if (good_ngrams.empty()) { /* If no good ngrams found, adding a dot and return */
            result += ".";
            return result;
        }
        if (result[result.length() - 1] == '.') /* If sentence already ends with a dot, return it */
            return result;
        result += choose_and_crop_ngram(good_ngrams);
    }
    return result + "."; /* Otherwise, return sentence when length reaches limit */
}

/**
 * Takes a string and returns the last word of it
 */
std::string get_last_word(std::string str) {
    std::string word = "";
    auto len = str.length();
    for (auto i = len - 1; str[i] != ' '; i--) { /* Going until we meet a space */
        word = str[i] + word;
    }
    return word;
}

/**
 * Counts the number of spaces in a string and returns it
 */
int spaces_in(std::string str) {
    int counter = 0;
    for (unsigned int i = 0; i < str.length(); i++)
        if (str[i] == ' ') counter++;
    return counter;
}

/**
 * Randomly chooses one of the ngrams, crops the
 * first word from it and returns it
 */
std::string choose_and_crop_ngram(std::vector<std::string> ngrams) {
    srand(static_cast<unsigned>(time(0)));
    auto random_index = rand() % ngrams.size();
    std::string ngram = ngrams[random_index];
    std::string result = "";
    auto first_space = ngram.find(' ');
    auto len = ngram.size();
    for (auto i = len - 1; i >= first_space; i--)
        result = ngram[i] + result;
    return result;
}

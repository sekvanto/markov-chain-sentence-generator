#include <iostream>
#include <vector>
#include <ctime>
#include "../headers/constants.h"

std::vector<std::string> makeNgrams(std::vector<std::string>);
std::string buildSentence(std::vector<std::string>);
std::string getLastWord(std::string);
int spacesIn(std::string);
std::string chooseAndCropNgram(std::vector<std::string>);

/**
 * This method takes dictionary, generates ngrams from words
 * and uses them to build a random sentence
 */
std::string getSentence(std::vector<std::string> dict) {
    if (ORDER < 2) {
        std::cout << "Order must be 2 or more" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (dict.size() <= ORDER)
        return "";
    std::vector<std::string> ngrams = makeNgrams(dict);
    return (buildSentence(ngrams));
}

/**
 * Takes a dictionary and generates ngrams from it
 */
std::vector<std::string> makeNgrams(std::vector<std::string> dict) {
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
std::string buildSentence(std::vector<std::string> ngrams) {
    std::string result = "";
    srand(static_cast<unsigned>(time(0)));
    auto firstPiece = rand() % ngrams.size(); /* Generating first N words randomly */
    result = ngrams[firstPiece];
    while (spacesIn(result) < MAX_SEN_LEN) {
        std::vector<std::string> goodNgrams;
        for (std::string ngram : ngrams) { /* Finding ngrams, which start with the current last word */
            std::string lastWord = getLastWord(result);
            if (ngram.find(lastWord) == 0) /* if ngram starts with lastWord, it is good */
                goodNgrams.push_back(ngram);
        }
        if (goodNgrams.empty()) { /* If no good ngrams found, adding a dot and return */
            result += ".";
            return result;
        }
        if (result[result.length() - 1] == '.') /* If sentence already ends with a dot, return it */
            return result;
        result += chooseAndCropNgram(goodNgrams);
    }
    return result + "."; /* Otherwise, return sentence when length reaches limit */
}

/**
 * Takes a string and returns the last word of it
 */
std::string getLastWord(std::string str) {
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
int spacesIn(std::string str) {
    int counter = 0;
    for (unsigned int i = 0; i < str.length(); i++)
        if (str[i] == ' ') counter++;
    return counter;
}

/**
 * Randomly chooses one of the ngrams, crops the
 * first word from it and returns it
 */
std::string chooseAndCropNgram(std::vector<std::string> ngrams) {
    srand(static_cast<unsigned>(time(0)));
    auto randomIndex = rand() % ngrams.size();
    std::string ngram = ngrams[randomIndex];
    std::string result = "";
    auto firstSpace = ngram.find(' ');
    auto len = ngram.size();
    for (auto i = len - 1; i >= firstSpace; i--)
        result = ngram[i] + result;
    return result;
}

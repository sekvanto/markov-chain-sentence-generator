#include <iostream>
#include <fstream>
#include <vector>

/**
 * Takes a vector dictionary and a line, 
 * then adds words from the line to it
 *
 * @param dict The resulting dictionary
 */
void addWords(std::vector<std::string> &dict,
              std::string line)
{
    std::string word = "";
    for (int i = 0; i < line.length(); i++) {
        /* Time to add a word? */
        if (line[i] == ' ' && word != "") {
            dict.push_back(word);
            word = "";
        }
        /* Otherwise, extending word */
        else word += line[i];
    }
}

/**
 * This method takes a vector dictionary and a
 * filename, reads the file and adds separate words from
 * file to vector.
 *
 * @param dict The resulting dictionary
 */
void getDictionary(std::vector<std::string> &dict,
                   std::string filePath)
{
    std::string line;
    std::ifstream source(filePath);
    if (!source.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        exit(EXIT_FAILURE);
    }
    while (getline (source, line)) {
        addWords(dict, line);
    }
    source.close();
}

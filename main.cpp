/* 
 * File:   main.cpp
 * Author: Julius Higiro
 *
 * Created on November 27, 2016, 12:41 PM
 */

#include <fstream>
#include "DecisionTree.h"

/**
 * See README file on how the decision tree is printed to the console.
 */

int main(int argc, char** argv) {
    if (argc == 2) {
        std::vector<std::string> data;
        std::string inputFile = argv[1];
        std::string line;
        std::ifstream input;
        input.open(inputFile);
        if (input.is_open()) {
            while (!input.eof() && input.peek() != '\n') {
                std::getline(input, line);
                line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
                data.push_back(line);
            }
            DecisionTree tree;
            tree.init(data);
        } else {
            std::cout << "There was an error while opening the file." << std::endl;
        }
        input.close();
    } else {
        std::cerr << "Specify the following parameters: ";
        std::cerr << "< program > < filename (i.e./home/examples/data.txt) >\n";
    }
    return 0;

}


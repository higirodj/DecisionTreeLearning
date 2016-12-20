/* 
 * File:   DecisionTree.h
 * Author: Julius Higiro
 *
 * Created on November 27, 2016, 12:41 PM
 */

#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <utility>
#include <cstdio>

class Node {

public:
    char value;
    Node* left;
    Node* right;
    Node(char v):value(v) {
        left = NULL;
        right = NULL;
    }
};

class DecisionTree {

public:
    
    DecisionTree();
    
    ~DecisionTree();
    
    /**
     * This method calculates the entropy of a random variable.
     */
    double entropy(double probability);
    
    /**
     * This method is used to retrieve the labels of the dataset.
     */
    std::vector<char> classifiers(std::vector<std::string> examples);
    
    /**
     * This method is used to determine whether or not the examples
     * have the same classification.
     */
    bool sameClassification(std::vector<std::string> examples);
    
    /**
     * This method calculates the expected reduction in entropy.
     */
    double infoGain(char attribute, std::vector<std::string> examples);
    
    /**
     * This method determines the best attribute in the dataset. 
     */
    char importance(std::vector<char> attributes,
        std::vector<std::string> examples);
    
    /**
     * This method returns the most common output value.
     */
    char plurality_value(std::vector<std::string> examples);
    
    /**
     * This method starts the recursion.
     */
    void init(const std::vector<std::string> examples);
    
    /**
     * This method adds a node to the tree.
     */
    void add(Node* root, Node* node, int label);
        
    /**
     * This method recursively generates a decision tree using
     * the Decision-Tree-Learning algorithm.
     */
    Node* generateTree(std::vector<std::string> examples,
        std::vector<char> attributes, std::vector<std::string> parent_examples);
        
    /**
     * This method prints the tree.
     */
    void print(Node* tree, int offset);
    
    /**
     * This method prints the dataset. It is used for debugging purposes.
     */
    void printData(std::vector<std::string> &examples);
    
private:
  
};

#endif /* DECISIONTREE_H */


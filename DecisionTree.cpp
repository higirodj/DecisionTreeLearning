#include "DecisionTree.h"

DecisionTree::DecisionTree(){}

DecisionTree::~DecisionTree(){}

double
DecisionTree::entropy(double probability) {
    double p = probability;
    double q = (1 - probability);
    return ( (probability == 0) || (probability == 1) )? 0 :
        -( (p*std::log2(p)) + (q*std::log2(q)) );
}

std::vector<char>
DecisionTree::classifiers(std::vector<std::string> examples) {
    std::vector<char>labels;
    for(int i = 0; i < examples.size(); i++) {
        labels.push_back(examples[i][examples[0].size()-1]);
    }
    return labels;
}

bool
DecisionTree::sameClassification(std::vector<std::string> examples) {
    std::vector<char> labels = classifiers(examples);
    // check if same classification
    return std::all_of(labels.begin()+1, labels.end(),
            [&](char label) {return labels.front() == label;});
}

double
DecisionTree::infoGain(char attribute, std::vector<std::string> examples) {
    std::vector<char> labels = classifiers(examples);
    int onePosCount = 0; int oneNegCount = 0;
    int zeroPosCount = 0; int zeroNegCount = 0;
    int column = int(attribute - 'A');
    int posCount = std::count(labels.begin(), labels.end(), '+');
    int negCount = (labels.size() - posCount);
    // Calculate the probability of the goal attribute
    double probability = posCount/double(posCount+negCount);
    double goal = (probability == 0 || probability == 1)? 0:probability;
    // Count the number of positive and negative labels for the attribute 
    // values.
    for(int i = 0; i < examples.size(); i++) {
        if( (examples[i][column] == '1') && (labels[i] == '+') ){
            onePosCount++;
        }
        if( (examples[i][column] == '1') && (labels[i] == '-') ){
            oneNegCount++;
        }
        if( (examples[i][column] == '0') && (labels[i] == '+') ){
            zeroPosCount++;
        }
        if( (examples[i][column] == '0') && (labels[i] == '-') ){
            zeroNegCount++;
        }
    }
    double probabilityPos1 = onePosCount / double(onePosCount+oneNegCount);
    double probabilityPos0 = zeroPosCount / double(zeroPosCount+zeroNegCount);  
    double probabilityOnes = (onePosCount+oneNegCount) / double(posCount+negCount);
    double probabilityZeros = (zeroPosCount+zeroNegCount) / double(posCount+negCount);
    // Calculate and return the information gain.
    return ( entropy(goal) - (probabilityOnes*entropy(probabilityPos1) +
            probabilityZeros*entropy(probabilityPos0)) );
}

char
DecisionTree::importance(std::vector<char> attributes,
        std::vector<std::string> examples){
    double max = -1.0;
    char attribute;
    for(int i = 0; i < attributes.size(); i++) {
        // Select attribute with greatest info gain
        if(infoGain(attributes[i], examples) > max) {
            max = infoGain(attributes[i], examples);
            attribute = attributes[i]; 
        }
    }
    return attribute;
}

char
DecisionTree::plurality_value(std::vector<std::string> examples) {
    std::vector<char> labels = classifiers(examples);
    int posCount = std::count(labels.begin(), labels.end(), '+');
    int negCount = (labels.size() - posCount);
    return (posCount >= negCount)? '+':'-';
}

void
DecisionTree::init(const std::vector<std::string> examples) {
    std::vector<char> attributes;
    // Generate attributes based on #cols, excluding label
    for(int i = 0; i < examples[0].size()-1;i++) {
        char attribute = 'A' + i;
        attributes.push_back(attribute);
    }
    Node* tree = generateTree(examples, attributes, examples);
    print(tree, 0);
}

void
DecisionTree::add(Node* root, Node* node, int label) {
    if (label == 0) {
        if (root->left != NULL) {
            add(root->left, node, label);
        } else {
            root->left = node;
        }
    } else {
        if (root->right != NULL) {
            add(root->right, node, label);
        } else {
            root->right = node;
        }
    }
}

Node*
DecisionTree::generateTree(std::vector<std::string> examples,
        std::vector<char> attributes, std::vector<std::string> parent_examples) {
    // Decision tree learning algorithm
    if(examples.empty()) {
        return new Node(plurality_value(parent_examples));    
    } else if(sameClassification(examples)) {
        return new Node(examples[0][examples[0].size()-1]);
    } else if(attributes.size() == 0) {
       return new Node(plurality_value(examples));
    } else {
        char attribute = importance(attributes, examples);
        Node* tree = new Node(attribute);
        int column = int(attribute - 'A');        
        attributes.erase(std::remove(attributes.begin(),
                    attributes.end(), attribute), attributes.end());
        for(int i = 0; i < 2; i++) {
            std::vector<std::string> exs;
            for(int j = 0; j < examples.size(); j++) {
                int value = examples[j][column] - '0';
                if(value == i) {
                    exs.push_back(examples[j]);
                } 
            }
        Node* subtree = generateTree(exs, attributes, examples);
        add(tree, subtree, i);
        }
        return tree;
    }
}

void 
DecisionTree::print(Node* tree, int offset) {
 
  if (tree == NULL ) {
    for(int i = 0; i < offset; i++) {
        std::putc('\t',stdout);
    }
    std::puts("@");
  }
  else {
    print(tree->right, offset+1);
     for(int i = 0; i < offset; i++) {
        std::putc('\t', stdout);
    }
    std::cout << tree->value << "\n";
    print(tree->left, offset+1);
  }
    
}

void 
DecisionTree::printData(std::vector<std::string> &examples) {
    for(std::string s : examples) {
        std::cout << s << std::endl;
    }
}

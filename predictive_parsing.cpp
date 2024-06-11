#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <sstream>
#include <unordered_map>

using namespace std;

// Define the parsing table correctly
unordered_map<string, unordered_map<string, vector<string>>> parsingTable = {
    {"E", {{"id", {"T", "E'"}}}},
    {"E'", {{"+", {"+", "T", "E'"}}, {"$", {"~"}}}}, // Empty production is represented by an empty vector
    {"T", {{"id", {"id"}}}}
};

// Tokenize input string
vector<string> tokenize(const string& input) {
    vector<string> tokens;
    stringstream ss(input);
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    tokens.push_back("$"); // End marker
    return tokens;
}

// Parse the token sequence
bool parse(const vector<string>& tokens) {
    stack<string> parseStack;
    parseStack.push("$");
    parseStack.push("E");

    int index = 0;
    while (!parseStack.empty()) {
        string top = parseStack.top();
        string currentToken = tokens[index];

        if (top == currentToken) {
            parseStack.pop();
            index++;
        } else if (parsingTable.find(top) != parsingTable.end()) {
            if (parsingTable[top].find(currentToken) != parsingTable[top].end()) {
                parseStack.pop();
                vector<string> rule = parsingTable[top][currentToken];
                for (auto it = rule.rbegin(); it != rule.rend(); ++it) {
                    if (*it != "") { // "" is often used for epsilon but we just skip pushing anything
                        parseStack.push(*it);
                    }
                }
            } else {
                return false; // No matching rule in parsing table
            }
        } else {
            return false; // Top of stack is a terminal that doesn't match current token
        }
    }
    return index == tokens.size();
}

int main() {
    string input;
    cout << "Enter the string to parse (tokens separated by spaces): ";
    getline(cin, input);

    vector<string> tokens = tokenize(input);
    bool result = parse(tokens);

    if (result) {
        cout << "The input string is successfully parsed!" << endl;
    } else {
        cout << "The input string is rejected by the parser!" << endl;
    }

    return 0;
}
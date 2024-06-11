#include<bits/stdc++.h>
using namespace std;

// Structure to represent a three-address code instruction
struct TAC {
    string op;
    string arg1;
    string arg2;
    string result;
};
// Function to generate new temporary variable names
string newTemp() {
    static int count = 0;
    return "t" + to_string(count++);
}

// Function to generate three-address code for an expression
vector<TAC> generateTAC( string& expression, string& result) {
    vector<TAC> code;
    vector<string> tempStack;
    stringstream ss(expression);
    char token;
    while (ss >> token) {
        if (isdigit(token) || isalpha(token)) {
            tempStack.push_back(string(1, token));
        } else {
            string op2 = tempStack.back();
            tempStack.pop_back();
            string op1 = tempStack.back();
            tempStack.pop_back();
            string temp = newTemp();
            tempStack.push_back(temp);
            code.push_back({string(1, token), op1, op2, temp});
        }
    }
    result = tempStack.back();
    return code;
}
// Function to print the generated three-address code
void printTAC(const vector<TAC>& code) {
    for (const auto& instr : code) {
        cout << instr.result << " = " << instr.arg1 << " " << instr.op << " " << instr.arg2 << endl;
    }
}

int main() {
    string expression;
    cout << "Enter a postfix arithmetic expression (e.g., ab+c*): ";
    cin >> expression;

    string result;
    vector<TAC> code = generateTAC(expression, result);
    
    cout << "\nThree-Address Code:\n";
    printTAC(code);
    
    return 0;
}
#include <iostream>
#include <stack>

using namespace std;
int reg = 0;
struct Node
{
    char data;
    Node *left;
    Node *right;
};
Node *createNode(char data)
{
    Node *newNode = new Node();
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    return newNode;
}
int generateMachineCode(Node *root)
{
    stack<int> machineStack;
    if (root)
    {
        if (root->data >= '0' && root->data <= '9')
        {
            cout << "LOAD R" << reg++ << ", " << root->data << "\n";
            return root->data - '0';
        }
        else
        {
            int leftResult = generateMachineCode(root->left);
            int rightResult = generateMachineCode(root->right);
            switch (root->data)
            {
            case '+':
                cout << "ADD R" << reg - 2 << ", R" << reg - 2 << ", R" << reg - 1 << endl;
                reg--;
                return leftResult + rightResult;
            case '-':
                cout << "SUB R" << reg - 2 << ", R" << reg - 2 << ", R" << reg - 1 << endl;
                reg--;
                return leftResult - rightResult;
            case '*':
                cout << "MUL R" << reg - 2 << ", R" << reg - 2 << ", R" << reg - 1 << endl;
                reg--;
                return leftResult * rightResult;
            case '/':
                cout << "DIV R" << reg - 2 << ", R" << reg - 2 << ", R" << reg - 1 << endl;
                reg--;
                return leftResult / rightResult;
            default:
                return root->data - '0';
            }
        }
    }
    return 0;
}

int main()
{
    // Example AST
    Node *root = createNode('+');
    root->left = createNode('3');
    root->right = createNode('*');
    root->right->left = createNode('4');
    root->right->right = createNode('5');

    // Generate machine code and get result
    int result = generateMachineCode(root);

    // Output result
    cout << "Result: " << result << endl;

    return 0;
}
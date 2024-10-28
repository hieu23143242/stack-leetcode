#include <stack>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

bool isMatch(char openBracket, char closeBracket) {
    return (openBracket == '[' && closeBracket == ']') ||
           (openBracket == '{' && closeBracket == '}') ||
           (openBracket == '(' && closeBracket == ')');
}

bool isOpenBracket(char c) {
    return (c == '(' || c == '[' || c == '{');
}

bool isCloseBracket(char c) {
    return (c == ')' || c == ']' || c == '}');
}

bool isValid(string s) {
    stack<char> stk;
    for (char c : s) {
        if (isOpenBracket(c)) {
            stk.push(c);
        } else {
            if (stk.empty() || !isMatch(stk.top(), c)) return false;
            stk.pop();
        }
    }
    return stk.empty();
}

string simplifyPath(string path) {
    stack<string> stk;
    string ans, dir;
    stringstream ss(path);

    while (getline(ss, dir, '/')) {
        if (dir == "." || dir.empty()) continue;
        if (dir == "..") {
            if (!stk.empty()) stk.pop();
        } else {
            stk.push(dir);
        }
    }

    while (!stk.empty()) {
        ans = "/" + stk.top() + ans;
        stk.pop();
    }

    return ans.empty() ? "/" : ans;
}

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
};

vector<int> inorderTraversal(TreeNode* root) {
    stack<TreeNode*> stk;
    vector<int> ans;
    TreeNode* current = root;

    while (current != nullptr || !stk.empty()) {
        while (current != nullptr) {
            stk.push(current);
            current = current->left;
        }
        current = stk.top();
        stk.pop();
        ans.push_back(current->val);
        current = current->right;
    }
    return ans;
}

struct ListNode {
    int val;
    ListNode* next;
};

void reorderList(ListNode* head) {
    if (!head) return;

    ListNode* slow = head;
    ListNode* fast = head;
    stack<ListNode*> stk;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    while (slow) {
        stk.push(slow);
        slow = slow->next;
    }
    ListNode* current = head;
    while (!stk.empty()) {
        ListNode* top = stk.top();
        stk.pop();

        ListNode* next = current->next;
        current->next = top;
        top->next = next;
        current = next;
    }
    if (current) current->next = nullptr;
}

vector<int> preorderTraversal(TreeNode* root) {
    vector<int> ans;
    if (!root) return ans;

    stack<TreeNode*> stk;
    stk.push(root);

    while (!stk.empty()) {
        TreeNode* top = stk.top();
        stk.pop();
        ans.push_back(top->val);

        if (top->right) stk.push(top->right);
        if (top->left) stk.push(top->left);
    }
    return ans;
}

vector<int> postorderTraversal(TreeNode* root) {
    vector<int> ans;
    if (root == nullptr) return ans;
    stack<TreeNode*> stk1;
    stack<int> stk2;
    stk1.push(root);
    while (!stk1.empty()) {
        TreeNode* top = stk1.top();
        stk1.pop();
        stk2.push(top->val);

        if (top->left != nullptr) stk1.push(top->left);
        if (top->right != nullptr) stk1.push(top->right);
    }
    while (!stk2.empty()) {
        ans.push_back(stk2.top());
        stk2.pop();
    }
    return ans;
}

bool isOperator(string str) {
    if (str == "+" || str == "-" || str == "*" || str == "/") return true;
    return false;
}

int calculator(int num1, int num2, string _operator) {
    if (_operator == "+") return num2 + num1;
    if (_operator == "-") return num2 - num1;
    if (_operator == "*") return num2 * num1;
    return num2 / num1;
}

int evalRPN(vector<string>& tokens) {
    stack<int> stk;
    for (string str: tokens) {
        if (!isOperator(str)) {
            stk.push(stoi(str));
        } else {
            if (stk.size() >= 2) {
                int num1 = stk.top();
                stk.pop();
                int num2 = stk.top();
                stk.pop();
                stk.push(calculator(num1, num2, str));
            }
        }
    }
    return stk.top();
}

class BSTIterator {
private:
    stack<int> stk;
public:
    BSTIterator(TreeNode* root) {
        stack<TreeNode*> stack;
        TreeNode* current = root;
        while (current != nullptr || !stack.empty()) {
            while (current != nullptr) {
                stack.push(current);
                current = current->right;
            }
            TreeNode* top = stack.top();
            stack.pop();
            this->stk.push(top->val);
            current = top->left;
        }
    }
    int next() {
        int res = this->stk.top();
        this->stk.pop();
        return res;
    }

    bool hasNext() {
        return !this->stk.empty();
    }
};

class MinStack {
private:
    stack<int> stk;
    stack<int> mnStk;
public:
    MinStack() {/*do nothing*/}
    void push(int val) {
        this->stk.push(val);
        if (this->mnStk.empty() || this->mnStk.top() >= val) {
            this->mnStk.push(val);
        }
    }
    void pop() {
        if (this->stk.top() == this->mnStk.top()) {
            this->mnStk.pop();
        }
        this->stk.pop();
    }
    int top() {
        return this->stk.top();
    }
    int getMin() {
        return this->mnStk.top();
    }
};

class MyStack {
private:
    queue<int> q1;
    queue<int> q2;
public:
    MyStack() {/*do nothing*/}
    void push(int x) {
        this->q1.push(x);
        while (!this->q2.empty()) {
            this->q1.push(this->q2.front());
            this->q2.pop();
        }
        swap(this->q1, this->q2);
    }
    int pop() {
        int res = this->q2.front();
        this->q2.pop();
        return res;
    }
    int top() {
        return this->q2.front();
    }
    bool empty() {
        return this->q2.empty();
    }
};

int getPriority(string op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}

int calculate(string s) {
    stack<int> numStk;
    stack<string> operatorStk;
    string currentNum = "";
    for (char c: s) {
        if (c == ' ') continue;
        string str = string(1,c);
        if (isOperator(str)) {
            if (currentNum.length() != 0) {
                numStk.push(stoi(currentNum));
                currentNum = "";
            }
            while (!operatorStk.empty() && getPriority(operatorStk.top()) >= getPriority(str)) {
                string opTop = operatorStk.top();
                operatorStk.pop();
                int num1 = numStk.top();
                numStk.pop();
                int num2 = numStk.top();
                numStk.pop();
                numStk.push(calculator(num1, num2, opTop));
            }
            operatorStk.push(str);
        } else {
            currentNum += str;
        }
    }
    if (currentNum.length() != 0) numStk.push(stoi(currentNum));
    while (numStk.size() != 1) {
        int num1 = numStk.top();
        numStk.pop();
        int num2 = numStk.top();
        numStk.pop();
        string op = operatorStk.top();
        operatorStk.pop();
        numStk.push(calculator(num1, num2, op));
    }
    return numStk.top();
}

class MyQueue {
private:
    stack<int> s1;
    stack<int> s2;
public:
    MyQueue() {/*do nothing*/}

    void push(int x) {
        this->s1.push(x);
    }

    int pop() {
        if (!this->s2.empty()) {
            int res = this->s2.top();
            this->s2.pop();
            return res;
        }
        while (!this->s1.empty()) {
            this->s2.push(this->s1.top());
            this->s1.pop();
        }
        return this->pop();
    }

    int peek() {
        if (!this->s2.empty()) return this->s2.top();
        while (!this->s1.empty()) {
            this->s2.push(this->s1.top());
            this->s1.pop();
        }
        return this->peek();
    }

    bool empty() {
        return this->s1.empty() && this->s2.empty();
    }
};

bool isPalindrome(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return true;
    ListNode* slow = head;
    ListNode* fast = head;
    stack<int> stk;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    if (fast != nullptr) slow = slow->next;
    while (slow != nullptr) {
        stk.push(slow->val);
        slow = slow->next;
    }
    ListNode* current = head;
    while (!stk.empty()) {
        int top = stk.top();
        stk.pop();
        if (top != current->val) return false;
        current = current->next;
    }
    return stk.empty();
}

string removeDuplicateLetters(string s) {
    stack<char> stk1;
    stack<char> stk2;
    string ans = "";
    for (char c: s) {
        if (stk2.empty()) {
            stk2.push(c);
        } else {
            while (!stk2.empty() && c > stk2.top()) {
                stk1.push(stk2.top());
                stk2.pop();
            }
            if (stk2.empty() || stk2.top() > c) {
                stk2.push(c);
            }
            while (!stk1.empty()) {
                stk2.push(stk1.top());
                stk1.pop();
            }
        }
    }
    while (!stk2.empty()) {
        ans += stk2.top();
        stk2.pop();
    }
    return ans;
}


int main() {
//    string res = removeDuplicateLetters("cbacdcbc");
    cout<<res;

    return 0;
}


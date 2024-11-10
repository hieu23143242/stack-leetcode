#include <stack>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>

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
    stack<int> num;
    stack<char> op;
    int currentNum = 0;
    for (char c: s) {
        if (c == ' ') continue;
        if (isdigit(c)) {
            currentNum = currentNum * 10 + (c - '0');
        } else {
            if (currentNum != 0) {
                num.push(currentNum);
                currentNum = 0;
            }
            while (!op.empty() && getPriority(op.top()) >= getPriority(c)) {
                char _operator = op.top();
                op.pop();
                int num1 = num.top();
                num.pop();
                int num2 = num.top();
                num.pop();
                num.push(calculator(num2, num1, _operator));
            }
            op.push(c);
        }
    }
    if (currentNum != 0) num.push(currentNum);
    while (!op.empty()) {
        char _operator = op.top();
        op.pop();
        int num1 = num.top();
        num.pop();
        int num2 = num.top();
        num.pop();
        num.push(calculator(num2, num1, _operator));
    }
    return num.top();
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

class NestedIterator {
private:
    stack<NestedInteger> stk1;
    stack<int> stk2;
    void flat(vector<NestedInteger> &nestedList) {
        for (NestedInteger nested: nestedList) {
            stk1.push(nested);
        }
        while (!stk1.empty()) {
            NestedInteger top = stk1.top();
            stk1.pop();
            if (top.isInteger()) {
                stk2.push(top.getInteger());
            } else {
                flat(top.getList());
            }
        }
    }
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        flat(nestedList);
    }
    int next() {
        int result = stk2.top();
        stk2.pop();
        return result;
    }
    bool hasNext() {
        return !stk2.empty();
    }
};

string decodeString(string s) {
  stack<int> num;
  stack<string> str;
  int currentNum = 0;
  string currentStr = "";
  for (char c: s) {
    if (isdigit(c)) {
      currentNum = currentNum * 10 + (c - '0');
    } else {
      if (c == '[') {
        num.push(currentNum);
	currentNum = 0;
	str.push(currentStr);
	currentStr = "";
      } else if (c == ']') {
	int numTop = num.top();
	num.pop();
	string strTop = str.top();
	str.pop();
	for (int i=0; i<numTop; i++) {
	  strTop += currentStr;
	}
	currentStr = strTop;
      } else {
        currentStr += c;
      }
    }
  }
  return currentStr;
}

string removeKdigits(string num, int k) {
	stack<char> s;
	for (char c: num) {
		while (!s.empty() && s.top() > c && k > 0) {
			s.pop();
			k --;
		}
		s.push(c);
	}
	while (k > 0) {
		s.pop();
		k --;
	}
	string ans = "";
	while (!s.empty()) {
		ans += s.top();
		s.pop();
	}
	reverse(ans.begin(), ans.end());
	int idx = 0;
	while (idx < ans.size() && ans[idx] == '0') {
		idx ++;
	}
	ans = ans.substr(idx);
	if (ans == "") return "0";
	return ans;
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	stack<int> stk;
	stack<int> stk1;
	stack<int> stk2;
	ListNode* dummy = new ListNode(0);
	int carry = 0;
	while (l1 != nullptr || l2 != nullptr) {
		if (l1 != nullptr) {
			stk1.push(l1->val);
			l1 = l1->next;
		}
		if (l2 != nullptr) {
			stk2.push(l2->val);
			l2 = l2->next;
		}
	}
	while (!stk1.empty() || !stk2.empty()) {
		int sum = carry;
		if (!stk1.empty()) {
			sum += stk1.top();
			stk1.pop();
		}
		if (!stk2.empty()) {
			sum += stk2.top();
			stk2.pop();
		}
		stk.push(sum % 10);
		carry = sum / 10;
	}
	if (carry != 0) stk.push(carry);
	ListNode* current = dummy;
	while (!stk.empty()) {
		current->next = new ListNode(stk.top());
		stk.pop();
		current = current->next;
	}
	ListNode* ans = dummy->next;
	delete dummy;
	return ans;
}

vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
	unordered_map<int, int> m;
	stack<int> s;
	vector<int> ans;
	for (int num: nums2) {
		while (!s.empty() && s.top() < num) {
			m[s.top()] = n;
			s.pop();
		}
		s.push(num);
	}
	while (!s.empty()) {
		m[s.top()] = -1;
		s.pop();
	}
	for (int num: nums1) {
		ans.push_back(m[num]);
	}
	return ans;
}

vector<int> nextGreaterElements(vector<int>& nums) {
	int size = nums.size();
	vector<int> ans(size, -1);
	stack<int> s;
	for (int i=0; i<size*2; i++) {
		int idx = i % size;
		int num = nums[idx];
		while (!s.empty() && nums[s.top()] < num) {
			ans[s.top()] = num;
			s.pop();
		}
		if (i < size) s.push(i);
	}
	return ans;
}

vector<int> preorder(Node* root) {
	vector<int> ans;
	if (root == nullptr) return ans;
	stack<Node*> s;
	s.push(root);
	while (!s.empty()) {
		Node* top = s.top();
		s.pop();
		ans.push_back(top->val);
		int childrens = top->children.size();
		for (int i=childrens-1; i>= 0; i--) {
			s.push(top->children[i]);
		}
	}
	return ans;
}

vector<int> postorder(Node* root) {
	vector<int> ans;
	if (root == nullptr) return ans;
	stack<Node*> s1;
	stack<Node*> s2;
	s1.push(root);
	while (!s1.empty()) {
		Node* top = s1.top();
		s1.pop();
		s2.push(top);
		for (Node* children: top->children) {
			s1.push(children);
		}
	}
	while (!s2.empty()) {
		ans.push_back(s2.top()->val);
		s2.pop();
	}
	return ans;
}

bool checkValidString(string s) {
	stack<char> open;
	stack<char> star;
	for (int i=0; i<s.length(); i++) {
		char c = s[i];
		if (c == '(') {
			open.push(i);
		} else if (c == '*') {
			star.push(i);
		} else {
			if (!open.empty()) {
				open.pop();
			} else if (!star.empty()) {
				star.pop();
			} else {
				return false;
			}
		}
	}
	while (!open.empty() && !star.empty()) {
		if (open.top() < star.top()) {
			open.pop();
			star.pop();
		} else {
			return false;
		}
	}
	return open.empty();
}

int calPoints(vector<string>& operations) {
    std::stack<int> s;
    int totalPoint = 0;
    for (std::string c: operations) {
        if (c == "C" && !s.empty()) {
            s.pop();
        } else if (c == "D" && !s.empty()) {
            int top = s.top();
            s.push(top * 2);
        } else if (c == "+" && !s.empty()) {
            int top1 = s.top();
            s.pop();
            int top2 = s.top();
            s.push(top1);
            s.push(top2 + top1);
        } else {
            s.push(std::stoi(c));
        }
    }
    while (!s.empty()) {
        totalPoint += s.top();
        s.pop();
    }
    return totalPoint;
}

string util(string str) {
	stack<char> s;
	string ans = "";
	for (char c: str) {
		if (c == '#') {
			if (!s.empty()) s.pop();
		} else {
			s.push(c);
		}
	}
	while (!s.empty()) {
		ans += s.top();
		s.pop();
	}
	return ans;
}

bool backspaceCompare(string s, string t) {
	return util(s) == util(t);
}

TreeNode* increasingBST(TreeNode* root) {
    TreeNode* res = new TreeNode(0);
    TreeNode* resCurrent = res;
    std::stack<TreeNode*> s;
    TreeNode* current = root;
    while (!s.empty() || current != nullptr) {
        while (current != nullptr) {
            s.push(current);
            current = current->left;
        }
        TreeNode* top = s.top();
        s.pop();
        resCurrent->right = new TreeNode(top->val);
        resCurrent = resCurrent->right;
        current = top->right;
    }
    return res->right;
}

int main() {
    unordered_map<int, int> myMap;

    return 0;
}

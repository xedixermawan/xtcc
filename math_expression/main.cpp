
// edi.e
// compile-link && run: g++ main.cpp -o main.out -std=c++11 && ./main.out
//

#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <stack>

using namespace std;

#define NUM_OPS 5

static char OP[NUM_OPS] = {
	'^',
	'x',
	'/',
	'+',
	'-'
};

struct Oprtr {
	Oprtr(char c, int val) {
		oprtr = c;
		value = val;
	}
	char oprtr;
	int value;
};

static Oprtr OPRTR[NUM_OPS] = {
	Oprtr('^',2),
	Oprtr('x',1),
	Oprtr('/',1),
	Oprtr('+',0),
	Oprtr('-',0)
};

bool isNumber(char c) {
	return (c > 47 && c < 58);
}

bool isOperator(char c) {
	for (int i = 0; i < NUM_OPS; i++) {
		if (c == OP[i]) {
			return true;
		}
	}
	return false;
}

int getPrecedence(char c) {
	for (int i = 0; i<NUM_OPS; i++) {
		if (c == OPRTR[i].oprtr) {
			return OPRTR[i].value;
		}
	}
	return -1;
}

bool isNeedPop(char topOp, char op2) {
	return (getPrecedence(topOp) >= getPrecedence(op2));
}

void toNumber(vector<string>& out, char cArray[], int& len) {
	if (len>0) {
		ostringstream oss;
		for (int i = 0; i<len; i++) {
			oss << cArray[i];
		}
		string s = oss.str();
		out.push_back(s);
		len = 0;
	}
}

string toString(char c) {
	ostringstream oss;
	oss << c;
	return oss.str();
}

void transfer(vector<string>& outvector, stack<char>& opStack, char c) {
	outvector.push_back(toString(c));
	opStack.pop();
}

void process(const string& in, stack<char>& opStack, vector<string>& outvector) {
	int len = (int)in.length();
	char number_candidate[64];
	int i = 0, nc = 0;
	while (i < len) {
		char c = in[i];
		if (isNumber(c) || c == '.') {
			number_candidate[nc++] = c;
		}
		else if (isOperator(c)) {
			toNumber(outvector, number_candidate, nc);
			while (!opStack.empty()) {
				char topOp = opStack.top();
				if (isNeedPop(topOp, c)) {
					transfer(outvector, opStack, topOp);
				}
				else {
					break;
				}
			}
			opStack.push(c);
		}
		else if (c == '(') {
			toNumber(outvector, number_candidate, nc);
			opStack.push(c);
		}
		else if (c == ')') {
			toNumber(outvector, number_candidate, nc);
			while (!opStack.empty() && opStack.top() != '(') {
				transfer(outvector, opStack, opStack.top());
			}
			if (!opStack.empty()) {
				opStack.pop();
			}
		}
		else {
			toNumber(outvector, number_candidate, nc);
		}
		i++;
	}
	toNumber(outvector, number_candidate, nc);
	while (!opStack.empty()) {
		transfer(outvector, opStack, opStack.top());
	}
}

void printVector(vector<string> qVal) {
	for (const string& v : qVal) {
		cout << v.c_str() << " ";
	}
}

int main(int argc, char** argv)
{
	cout << "Input your math expression" << endl;
	char in[256];
	while (true) {
		cout << "\nExpression>>";
		cin.getline(in, 256);
		if (strcmp(in, "q") == 0) {
			cout << "exit.." << endl;
			return 0;
		}
		stack<char> operation;
		vector<string> out;
		process(in, operation, out);
		printVector(out);
	}
	return 0;
}

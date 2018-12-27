using namespace std;

struct StackNode
{
	string name;
	StackNode *next;

};

class DynIntStack
{
private:
	StackNode *top;

public:
	DynIntStack(void);
	void push(string &);
	void pop(string &);
	bool isEmpty(void);
	~DynIntStack();
};

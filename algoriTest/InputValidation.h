#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>
#include <list>
#include <math.h>
#include <string>
#include <regex>
#define NOT_VALID -1
#define CHECK_WHICH_ALGO "[1-4]{1}"
#define CHECK_AMOUNT_OF_NODES "[0-9]+"
//"^\\d{1,5}\\s{1}\\d{1,5}$"

using namespace std;

class InputValidation
{
public:
	int CheckWhichAlgorithm(string input);
	int CheckAmountOfNodes(string input);
	int CheckNodeAndEdges(string input);
	int GetEdge(string input);
	int GetNode(string input);

private:
	void createCheckEdges(int amountOfNodes);
	bool inNodeRange(int number);
	int countLeadingZeros(string number);
	regex m_AmountOfNodesLength;
	string m_Node;
	string m_Edge;
	int m_MaxNodeNumber;
};
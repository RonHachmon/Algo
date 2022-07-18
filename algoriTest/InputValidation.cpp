#include "InputValidation.h"

int InputValidation::CheckWhichAlgorithm(string input)
{
	smatch match;

	if (regex_match(input, match, regex(CHECK_WHICH_ALGO)))
	{
		return stoi(match.str());
	}

	return NOT_VALID;

}
int InputValidation::CheckAmountOfNodes(string input)
{
	smatch match;
	int leadingZeros;

	if (regex_match(input, match, regex(CHECK_AMOUNT_OF_NODES)))
	{
		leadingZeros = countLeadingZeros(match.str());
		createCheckEdges(match.str().size() - leadingZeros);
		m_MaxNodeNumber = stoi(match.str());

		if (m_MaxNodeNumber != 0)
		{
			return m_MaxNodeNumber;
		}
	}

	return NOT_VALID;

}
int InputValidation::countLeadingZeros(string number)
{
	int count = 0;

	for (int i = 0; i < number.size(); i++)
	{
		if (number[i] == 0)
		{
			count++;
		}
		else
		{
			break;
		}
	}

	return count;
}
void InputValidation::createCheckEdges(int amountOfNodesLength)
{
	m_Node = "^\\d{1," + to_string(amountOfNodesLength) + "}";
	m_Edge = "\\d{1," + to_string(amountOfNodesLength) + "}\\s*$";
	string temp = m_Node + "\\s{1}" + m_Edge;
	m_AmountOfNodesLength = regex(temp);
}
int InputValidation::CheckNodeAndEdges(string input)
{
	smatch match;
	if (regex_match(input, match, m_AmountOfNodesLength))
	{
		string test = match.str();
		return 1;
	}

	return NOT_VALID;

}
int InputValidation::GetEdge(string input)
{
	smatch match;
	int temp;

	if (regex_search(input, match, regex(m_Edge)))
	{
		temp = stoi(match.str());

		if (inNodeRange(temp))
		{
			return temp;
		}
	}

	return NOT_VALID;

}
int InputValidation::GetNode(string input)
{
	smatch match;
	int temp;

	if (regex_search(input, match, regex(m_Node)))
	{
		temp = stoi(match.str());
		if (inNodeRange(temp))
		{
			return temp;
		}
	}

	return NOT_VALID;

}
bool InputValidation::inNodeRange(int number)
{
	return (number != 0 && number <= m_MaxNodeNumber);
}



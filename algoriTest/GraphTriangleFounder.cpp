#include "GraphTriangleFounder.h"

GraphTriangleFounder::GraphTriangleFounder(vector<list<int>>* i_NeighbersList)
{
	m_NumberOfVertexes = i_NeighbersList->size();
	m_NeighbersList = i_NeighbersList;
	m_DegreeOfVerexesVector = vector<int>(m_NumberOfVertexes, 0);
	countEdgesAndCalculateHighDegreeValue();
	m_NeighbersMatrix = vector<vector<int>>(m_NumberOfVertexes, vector<int>(m_NumberOfVertexes, 0));
	m_LenghSizeTwoPathMatrix = vector<vector<int>>(m_NumberOfVertexes, vector<int>(m_NumberOfVertexes, 0));
	m_LenghSizeThreePathMatrix = vector<vector<int>>(m_NumberOfVertexes, vector<int>(m_NumberOfVertexes, 0));
	calculateNewNeighbersMatrixAndPathsMatrixes();
}

GraphTriangleFounder::~GraphTriangleFounder()
{

}

void GraphTriangleFounder::countEdgesAndCalculateHighDegreeValue()
{
	int numberOfEdges = 0;
	for (int i = 0; i < m_NumberOfVertexes; i++)
	{
		for (int x : (*m_NeighbersList)[i])
		{
			m_DegreeOfVerexesVector[i]++;
			m_DegreeOfVerexesVector[x - 1]++;
			numberOfEdges++;
		}
	}

	m_HighDegreeValue = pow(numberOfEdges, 0.5);
}

void GraphTriangleFounder::convertListOfNeighborsToMatrix(bool i_NeedToValidateHighDegree)
{

	for (int i = 0; i < m_NumberOfVertexes; i++)
	{
		if (i_NeedToValidateHighDegree && isVertexLowDegree(i))
		{
			continue;
		}

		for (int x : (*m_NeighbersList)[i])
		{
			if (!i_NeedToValidateHighDegree || !isVertexLowDegree(x - 1))
			{
				m_NeighbersMatrix[i][x - 1] = 1;
			}
		}
	}
}

vector<int>* GraphTriangleFounder::findTriangleAlgo2()
{
	vector<int>* result = nullptr;

	int firstVertex = findThreeWayPathVertex();
	int secondVertex, thiredVertex;

	if (firstVertex != NOT_FOUND)
	{
		result = new vector<int>(3);
		thiredVertex = findThirdVertex(firstVertex);
		secondVertex = findSecondVertex(firstVertex, thiredVertex);

		(*result)[0] = firstVertex;
		(*result)[1] = secondVertex;
		(*result)[2] = thiredVertex;
	}

	return result;
}

int GraphTriangleFounder::findThreeWayPathVertex()
{
	int startPoint = NOT_FOUND;
	for (int i = 0; i < m_NumberOfVertexes && startPoint == NOT_FOUND; i++)
	{
		if (m_LenghSizeThreePathMatrix[i][i] != 0)
		{
			startPoint = i;
		}
	}

	return startPoint;
}

int GraphTriangleFounder::findThirdVertex(int i_SourceVertex)
{
	int thirdVertex;
	int valueInMatrix;
	for (thirdVertex = 0; thirdVertex < m_NumberOfVertexes; thirdVertex++)
	{
		valueInMatrix = m_LenghSizeTwoPathMatrix[i_SourceVertex][thirdVertex];

		if (valueInMatrix > 0 && m_NeighbersMatrix[thirdVertex][i_SourceVertex] == EDGE_EXISTS)
		{
			return thirdVertex;
		}
	}
}

int GraphTriangleFounder::findSecondVertex(int i_SourceVertex, int i_ThiredVertex)
{
	int secondVertex;

	for (secondVertex = 0; secondVertex < m_NumberOfVertexes; secondVertex++)
	{
		if (m_NeighbersMatrix[i_SourceVertex][secondVertex] == EDGE_EXISTS && m_NeighbersMatrix[secondVertex][i_ThiredVertex] == EDGE_EXISTS)
		{
			return secondVertex;
		}
	}

}

vector<int>* GraphTriangleFounder::findTriangleAlgo1(bool i_NeedToValidateDegree)
{
	vector<int>* triangle = nullptr;
	int closingCircle = NOT_FOUND;
	bool neighberIsLowerIndexThenSource;

	for (int originVertex = 0; originVertex < m_NumberOfVertexes; originVertex++)
	{
		if (i_NeedToValidateDegree && !isVertexLowDegree(originVertex))
		{
			continue;
		}

		for (int originNeigh : (*m_NeighbersList)[originVertex])
		{
			neighberIsLowerIndexThenSource = originNeigh - 1 < originVertex;

			if (neighberIsLowerIndexThenSource && (!i_NeedToValidateDegree || (i_NeedToValidateDegree && isVertexLowDegree(originNeigh - 1))))
			{
				continue;
			}

			closingCircle = findClosingCircle(originVertex + 1, originNeigh - 1, triangle, i_NeedToValidateDegree);

			if (closingCircle != NOT_FOUND)
			{
				triangle = new vector<int>(3);
				(*triangle)[0] = originVertex;
				(*triangle)[1] = originNeigh - 1;
				(*triangle)[2] = closingCircle - 1;

				return triangle;
			}

		}
	}
	return triangle;
}

int GraphTriangleFounder::findClosingCircle(int OriginToFind, int OriginNeigh, vector<int>* triangle, bool i_NeedToValidateDegree)
{
	for (int ThirdNeigh : (*m_NeighbersList)[OriginNeigh]) {

		if (ThirdNeigh != OriginToFind)
		{
			if (m_NeighbersMatrix[ThirdNeigh - 1][OriginToFind - 1] == 1)
			{
				return ThirdNeigh;
			}
		}
	}
	return NOT_FOUND;
}

bool GraphTriangleFounder::isVertexLowDegree(int i_Vertex)
{
	bool res = false;

	if (m_DegreeOfVerexesVector[i_Vertex] < m_HighDegreeValue)
	{
		res = true;
	}

	return res;
}

void GraphTriangleFounder::calculateNewNeighbersMatrixAndPathsMatrixes(bool i_NeedTobuildHighDegreeMatrix)
{
	m_NeighbersMatrix = vector<vector<int>>(m_NumberOfVertexes, vector<int>(m_NumberOfVertexes, 0));
	convertListOfNeighborsToMatrix(i_NeedTobuildHighDegreeMatrix);
	multiplySameSizeMatrix(&m_NeighbersMatrix, &m_NeighbersMatrix, &m_LenghSizeTwoPathMatrix);
	multiplySameSizeMatrix(&m_NeighbersMatrix, &m_LenghSizeTwoPathMatrix, &m_LenghSizeThreePathMatrix);
}

void GraphTriangleFounder::multiplySameSizeMatrix(vector<vector<int>>* source_matrixA, vector<vector<int>>* source_matrixB, vector<vector<int>>* target_matrix)
{
	int sizeOfMatrix = (*source_matrixA).size();

	for (int i = 0; i < sizeOfMatrix; i++)
	{
		for (int j = 0; j < sizeOfMatrix; j++)
		{
			for (int k = 0; k < sizeOfMatrix; k++)
				(*target_matrix)[i][j] += (*source_matrixA)[i][k] * (*source_matrixB)[k][j];
		}
	}
}
vector<int>* GraphTriangleFounder::findTriangleAlgo3()
{
	vector<int>* result = findTriangleAlgo1(true);

	if (result == nullptr)
	{
		calculateNewNeighbersMatrixAndPathsMatrixes(true);
		result = this->findTriangleAlgo2();
		calculateNewNeighbersMatrixAndPathsMatrixes();
	}

	return result;
}


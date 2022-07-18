#ifndef _TRIANGLE_FOUNDER_
#define _TRIANGLE_FOUNDER_

#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>
#include <list>
#include <math.h>

using namespace std;

#define NOT_FOUND -1
#define EDGE_EXISTS 1


class GraphTriangleFounder
{

public:
	GraphTriangleFounder(vector<list<int>>* i_NeighbersList);
	~GraphTriangleFounder();
	vector<int>* findTriangleAlgo2();
	vector<int>* findTriangleAlgo1(bool needToValidateDegree = false);
	vector<int>* findTriangleAlgo3();


private:
	double m_HighDegreeValue;
	int m_NumberOfVertexes;
	vector<int> m_DegreeOfVerexesVector;
	vector<vector<int>> m_NeighbersMatrix;
	vector<vector<int>> m_LenghSizeTwoPathMatrix;
	vector<vector<int>> m_LenghSizeThreePathMatrix;
	vector<list<int>>* m_NeighbersList;

	void countEdgesAndCalculateHighDegreeValue();
	void convertListOfNeighborsToMatrix(bool i_NeedToValidateHighDegree = false);
	int findThreeWayPathVertex();
	int findThirdVertex(int sourceVertex);
	int findSecondVertex(int sourceVertex, int thiredVertex);
	int findClosingCircle(int VerticeTofind, int listIndex, vector<int>* triangle, bool i_NeedToValidateDegree);
	bool isVertexLowDegree(int vertex);
	void calculateNewNeighbersMatrixAndPathsMatrixes(bool i_NeedTobuildHighDegreeMatrix = false);
	void multiplySameSizeMatrix(vector<vector<int>>* source_matrixA, vector<vector<int>>* source_matrixB, vector<vector<int>>* target_matrix);

};

#endif // !_TRIANGLE_FOUNDER_
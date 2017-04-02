#include <iostream>
#include <fstream>
#include <string>

#define READ_DATA_FROM_FILE 1

using namespace std;

class Vector3D
{
	

public:
	int x, y, z;
	Vector3D(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3D()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	void Add(int *vertexes)
	{
		x = vertexes[0];
		y = vertexes[1];
		z = vertexes[2];
	}
};
class Edge
{	

public:
	int firstVertex, secondVertex;
	Edge(int firstVertex, int secondVertex)
	{
		this->firstVertex = firstVertex;
		this->secondVertex = secondVertex;
	}

	Edge()
	{
		this->firstVertex = 0;
		this->secondVertex = 0;
	}

	void Add(int *indexes)
	{
		firstVertex = indexes[0];
		secondVertex = indexes[1];

	}
};


int ConvertOneNumberStringToInt(string line)
{
	int tempNumber = 0;
	for (int i = 0; i < line.length(); i++)
	{
		tempNumber *= 10;
		switch (line[i])
		{
		case '1':
			tempNumber += 1;
			break;
		case '2':
			tempNumber += 2;
			break;
		case '3':
			tempNumber += 3;
			break;
		case '4':
			tempNumber += 4;
			break;
		case '5':
			tempNumber += 5;
			break;
		case '6':
			tempNumber += 6;
			break;
		case '7':
			tempNumber += 7;
			break;
		case '8':
			tempNumber += 8;
			break;
		case '9':
			tempNumber += 9;
			break;
		default:
			break;
		}
	}

	return tempNumber;
}
int * ConvertNumbersStringToInt(string line, int size)
{
	int tempNumber = 0;
	int *tempNumbers =new int[size];
	int tempNumberIndex = 0;

	for (int i = 0; i < line.length(); i++)
	{

		switch (line[i])
		{
		case ' ':
			tempNumbers[tempNumberIndex] = tempNumber;
			tempNumber = 0;
			tempNumberIndex++;
			break;
		case '0':
			tempNumber *= 10;
			break;
		case '1':
			tempNumber *= 10;
			tempNumber += 1;
			break;
		case '2':
			tempNumber *= 10;
			tempNumber += 2;
			break;
		case '3':
			tempNumber *= 10;
			tempNumber += 3;
			break;
		case '4':
			tempNumber *= 10;
			tempNumber += 4;
			break;
		case '5':
			tempNumber *= 10;
			tempNumber += 5;
			break;
		case '6':
			tempNumber *= 10;
			tempNumber += 6;
			break;
		case '7':
			tempNumber *= 10;
			tempNumber += 7;
			break;
		case '8':
			tempNumber *= 10;
			tempNumber += 8;
			break;
		case '9':
			tempNumber *= 10;
			tempNumber += 9;
			break;
		default:
			break;
		}
	}
	tempNumbers[tempNumberIndex] = tempNumber;
	return tempNumbers;
}
int compare(const void * a, const void * b)
{
	return (*(double*)a - *(double*)b);
}

class Object3D
{
	Vector3D *listofVertex;
	Edge *listOfEdge;
	int numberOfVertex = 0;
	int numberOfEdge = 0;
	int numberOfSide = 0;
	int currentListOfVertexIndex = 0;
	int currentListOfEdgeIndex = 0;
	
public:
	double *edgeLengths;
	int GetNumberOfVertex()	{ return numberOfVertex; }
	int GetNumberOfEdge() { return numberOfEdge; }
	int GetNumberOfSide() { return numberOfSide; }
	void AddVertexToList(int *vertexes)
	{
		if (currentListOfVertexIndex < numberOfVertex)
		{
			listofVertex[currentListOfVertexIndex].Add(vertexes);
			currentListOfVertexIndex++;
		}
	}

	void AddEdgeToList(int *edges)
	{
		if (currentListOfEdgeIndex < numberOfEdge)
		{
			listOfEdge[currentListOfEdgeIndex].Add(edges);
			currentListOfEdgeIndex++;
		}
	}
	void ReadDatasFromFile(ifstream &infile)
	{
		string line = "";
		
		
		//csucsok száma
		getline(infile, line);
		numberOfVertex = ConvertOneNumberStringToInt(line);
		listofVertex = new Vector3D[numberOfVertex];

		//csucsok beolvasása
		for (int i = 0; i < numberOfVertex; i++)
		{
			getline(infile, line);
			AddVertexToList(ConvertNumbersStringToInt(line, 3));
		}

		//elek szama
		getline(infile, line);
		numberOfEdge = ConvertOneNumberStringToInt(line);
		listOfEdge = new Edge[numberOfEdge];

		//elek beolvasása
		for (int i = 0; i < numberOfEdge; i++)
		{
			getline(infile, line);
			AddEdgeToList(ConvertNumbersStringToInt(line, 2));
		}
		//oldalak szama
		getline(infile, line);
		numberOfSide = ConvertOneNumberStringToInt(line);
		
		//oldalak kamu beolvasas
		while (!line.empty())
			getline(infile, line);


	}

	void CalculateEdgeLength()
	{
		edgeLengths = new double[numberOfEdge];
		double deltaX = 0, deltaY = 0, deltaZ = 0;
		for (int i = 0; i < numberOfEdge; i++)
		{
			deltaX = (double)(listofVertex[(listOfEdge[i].firstVertex - 1)].x - listofVertex[(listOfEdge[i].secondVertex - 1)].x);
			deltaY = (double)(listofVertex[(listOfEdge[i].firstVertex - 1)].y - listofVertex[(listOfEdge[i].secondVertex - 1)].y);
			deltaZ = (double)(listofVertex[(listOfEdge[i].firstVertex - 1)].z - listofVertex[(listOfEdge[i].secondVertex - 1)].z);

			edgeLengths[i] = sqrt((pow(deltaX, 2) + pow(deltaY, 2) + pow(deltaZ, 2)));
		}

		qsort(edgeLengths, numberOfEdge, sizeof(double), compare);

	}
};

class Isomorph
{
	Object3D first;
	Object3D second;

public:
	Isomorph()
	{
		ifstream infile;
		infile.open("g:\\Kerti\\Projects\\ItechChallenge\\Egybevago\\Egybevago\\Egybevago\\test3.txt");
		first.ReadDatasFromFile(infile);
		second.ReadDatasFromFile(infile);
		infile.close();
	}

	bool IsTheEdgesSame()
	{
		first.CalculateEdgeLength();
		second.CalculateEdgeLength();

		for(int i=0; i< first.GetNumberOfEdge();i++)
		{ 
			if (first.edgeLengths[i] != second.edgeLengths[i])
				return false;
		}

		return true;

	}

	bool IsItIsomorph()
	{
		if (first.GetNumberOfVertex() == second.GetNumberOfVertex())
		{
			if (first.GetNumberOfEdge() == second.GetNumberOfEdge())
			{
				if (first.GetNumberOfSide() == second.GetNumberOfSide())
				{
					if (IsTheEdgesSame())
					{
						return true;
					}
					return false;
				}
				return false;
			}
			return false;
		}
		return false;
	}
};

void main()
{
	Isomorph isomorph;
	isomorph.IsItIsomorph()? cout <<"TRUE" : cout <<"FALSE";
}
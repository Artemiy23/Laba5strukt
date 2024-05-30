#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <iomanip>
#include <random>
#include <time.h>
#include <list>
#include <queue>

class Graph
{
private:
	class Node
	{
	public:
		int key;
		std::vector<size_t> outNodesIndex;

		Node(int key)
		{
			this->key = key;
		}
	};

	std::vector<Node*> nodes;

	size_t maxLength(std::vector<Node*> arr)
	{
		size_t maxLength = 0;
		for (Node* elem : arr)
		{
			size_t length = std::to_string(elem->key).length();
			if (maxLength < length) maxLength = length;
		}
		return maxLength;
	}

public:
	void addNode(int key)
	{
		Node* node = new Node(key);
		nodes.push_back(node);
	}

	void addEdge(size_t from, size_t to)
	{
		for (size_t i = 0; i < nodes[from]->outNodesIndex.size(); i++)
		{
			if (nodes[from]->outNodesIndex[i] == to) return;
		}
		nodes[from]->outNodesIndex.push_back(to);
		std::sort(nodes[from]->outNodesIndex.begin(), nodes[from]->outNodesIndex.end());
	}

	void print()
	{
		for (size_t i = 0; i < maxLength(nodes) + 2; i++) std::cout << " ";
		for (size_t i = 0; i < nodes.size(); i++) std::cout << i << " ";
		std::cout << std::endl;
		for (size_t i = 0; i < nodes.size(); i++)
		{
			std::cout << i << ". ";
			size_t j = 0, k = 0;
			while (k < nodes.size())
			{
				if (!nodes[i]->outNodesIndex.empty() && j < nodes[i]->outNodesIndex.size())
				{
					if (nodes[i]->outNodesIndex[j] == k)
					{
						std::cout << 1 << " ";
						j++;
					}
					else std::cout << 0 << " ";
				}
				else std::cout << 0 << " ";
				k++;
			}
			std::cout << std::endl;
		}
	}

	std::vector<size_t> bypass(size_t index)
	{
		std::vector<bool> visits(nodes.size(), false);
		std::vector<size_t> indexes;
		std::queue<size_t> queue;
		queue.push(index);
		while (!queue.empty())
		{
			index = queue.front();
			queue.pop();
			if (visits[index] == true) continue;
			indexes.push_back(index);
			visits[index] = true;
			for (size_t i = 0; i < nodes[index]->outNodesIndex.size(); i++)
			{
				if (visits[nodes[index]->outNodesIndex[i]] == false)
				{
					queue.push(nodes[index]->outNodesIndex[i]);
				}
			}
		}
		return indexes;
	}

	std::vector<size_t> findBase(std::vector<size_t>& base, std::vector<std::vector<size_t>>& baseNodes)
	{
		bool f = false;
		std::vector<size_t> indexes;
		for (size_t i = 0; i < nodes.size(); i++) indexes.push_back(i);
		for (size_t i = 0; i < nodes.size(); i++)
		{
			for (size_t j = 0; j < nodes.size(); j++)
			{
				for (size_t k = 0; k < nodes[j]->outNodesIndex.size(); k++)
				{
					if (nodes[j]->outNodesIndex[k] == i && j != i)
					{
						f = true;
						break;
					}
				}
				if (f) break;
			}
			if (f == false) base.push_back(i);
			else f = false;
		}
		for (size_t i = 0; i < base.size(); i++)
		{
			baseNodes.push_back(bypass(base[i]));
			std::sort(baseNodes[i].begin(), baseNodes[i].end());
		}
		for (size_t i = 0; i < baseNodes.size(); i++)
		{
			for (size_t j = 0; j < baseNodes[i].size(); j++)
			{
				for (size_t k = 0; k < indexes.size(); k++)
				{
					if (baseNodes[i][j] == indexes[k])
					{
						indexes[k] = -1;
					}
				}
			}
		}
		f = false;
		for (size_t i = 0; i < indexes.size(); i++)
		{
			if (indexes[i] != -1)
			{
				f = true;
				break;
			}
		}
		if (f) base.clear();
		return base;
	}
};

int main()
{
	srand(time(0));
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	std::vector<std::vector<size_t>> baseNodes;
	std::vector<size_t> base;
	Graph* graph = new Graph;
	int in;
	size_t from, to;

	for (size_t i = 0; i < 8; i++)
	{
		//std::cin >> in;
		graph->addNode(rand() % (9 - 0 + 1) + 0);
	}

	graph->print();

	for (size_t i = 0; i < 15; i++)
	{
		/*std::cin >> from;
		std::cin >> to;*/
		graph->addEdge(rand() % 8, rand() % 8);
	}
	std::cout << std::endl;
	graph->print();
	graph->findBase(base, baseNodes);
	std::cout << u8"База графа:" << std::endl;
	for (size_t i = 0; i < base.size(); i++)
	{
		std::cout << base[i] << "-> ";
		for (size_t nodes : baseNodes[i])
		{
			std::cout << nodes << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}
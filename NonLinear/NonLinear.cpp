#include "NonLinear.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstring>  

char* NonLinear::dup(const char* s)
{
    size_t len = std::strlen(s);
    char* out = new char[len + 1];
    std::memcpy(out, s, len + 1);
    return out;
}

Node::Node(const char* name, int s)
    : playerName(nullptr), score(s), left(nullptr), right(nullptr)
{
    playerName = NonLinear::dup(name);
}

Node::~Node()
{
    delete[] playerName;
    playerName = nullptr;
}

NonLinear::NonLinear() : root(nullptr) {}

NonLinear::~NonLinear()
{
    destroy(root);
    root = nullptr;
}

void NonLinear::destroy(Node* node)
{
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

Node* NonLinear::findMin(Node* node)
{
    while (node && node->left) node = node->left;
    return node;
}

void NonLinear::insert(const char* name, int score)
{
    root = insert(root, name, score);
}

Node* NonLinear::insert(Node* node, const char* name, int score)
{
    if (!node) return new Node(name, score);

    int cmp = std::strcmp(name, node->playerName);
    if (cmp < 0) node->left = insert(node->left, name, score);
    else if (cmp > 0) node->right = insert(node->right, name, score);
    else node->score = score;

    return node;
}

void NonLinear::deleteNode(const char* name)
{
    root = deleteNode(root, name);
}

Node* NonLinear::deleteNode(Node* node, const char* name)
{
    if (!node) return nullptr;

    int cmp = std::strcmp(name, node->playerName);
    if (cmp < 0) node->left = deleteNode(node->left, name);
    else if (cmp > 0) node->right = deleteNode(node->right, name);
    else
    {
        if (!node->left)
        {
            Node* r = node->right;
            delete node;
            return r;
        }
        if (!node->right)
        {
            Node* l = node->left;
            delete node;
            return l;
        }

        Node* succ = findMin(node->right);

        delete[] node->playerName;
        node->playerName = dup(succ->playerName);
        node->score = succ->score;

        node->right = deleteNode(node->right, succ->playerName);
    }
    return node;
}

void NonLinear::find(const char* name)
{
    Node* r = find(root, name);
    if (r) std::cout << r->playerName << ": " << r->score << "\n";
    else std::cout << "Player not found: " << name << "\n";
}

Node* NonLinear::find(Node* node, const char* name)
{
    if (!node) return nullptr;

    int cmp = std::strcmp(name, node->playerName);
    if (cmp == 0) return node;
    if (cmp < 0) return find(node->left, name);
    return find(node->right, name);
}

void NonLinear::collect(Node* node, std::vector<Node*>& nodes)
{
    if (!node) return;
    collect(node->left, nodes);
    nodes.push_back(node);
    collect(node->right, nodes);
}

void NonLinear::top(int k)
{
    std::vector<Node*> nodes;
    collect(root, nodes);

    std::sort(nodes.begin(), nodes.end(),
        [](Node* a, Node* b) { return a->score > b->score; });

    for (int i = 0; i < k && i < (int)nodes.size(); ++i)
        std::cout << nodes[i]->playerName << ": " << nodes[i]->score << "\n";
}

void NonLinear::loadCSV(const char* filename)
{
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string nameStr, scoreStr;

        std::getline(ss, nameStr, ',');
        std::getline(ss, scoreStr);

        int score = std::stoi(scoreStr);

        // string을 "파싱 용"으로만 쓰고, 트리 내부는 char*로 저장.
        insert(nameStr.c_str(), score);
    }
}
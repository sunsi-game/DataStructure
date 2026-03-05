#pragma once
#include <vector>

// 이진 탐색 트리 기반.
// 요구사항.
// 노드 데이터 : playerName, score.
// insert[name][score] -> 이름 및 점수를 묶어 저장.
// delete[name] -> 이름으로 검색 후 삭제.
// find[name] -> 이름으로 검색 후 출력.
// top [k] -> 점수 높은 순 k명 출력.
// 텍스트 기반 데이터(csv 권장)를 생성한 후, 텍스트 데이터를 파싱해서 동작하도록 구현.

struct Node
{
    char* playerName;
    int score;
    Node* left;
    Node* right;

    Node(const char* name, int s);
    ~Node();
};

class NonLinear
{
public:
    NonLinear();
    ~NonLinear();

    static char* dup(const char* s);

    void insert(const char* name, int score);
    void deleteNode(const char* name);
    void find(const char* name);
    void top(int k);
    void loadCSV(const char* filename);

private:
    Node* root;

    Node* insert(Node* node, const char* name, int score);
    Node* deleteNode(Node* node, const char* name);
    Node* find(Node* node, const char* name);
    Node* findMin(Node* node);

    void collect(Node* node, std::vector<Node*>& nodes);
    void destroy(Node* node);

};


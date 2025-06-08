// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class PMTree {
public:
    struct Node {
        char value;
        std::vector<std::unique_ptr<Node>> children;
        
        Node(char val) : value(val) {}
    };

    PMTree(const std::vector<char>& elements);
    ~PMTree() = default;

    std::vector<std::vector<char>> getAllPerms() const;
    std::vector<char> getPerm1(int num) const;
    std::vector<char> getPerm2(int num) const;

private:
    std::unique_ptr<Node> root;
    int totalPermutations;

    void buildTree(Node* parent, const std::vector<char>& elements);
    void getAllPermsHelper(const Node* node, std::vector<char>& current, std::vector<std::vector<char>>& result) const;
    void getPerm1Helper(const Node* node, int& num, std::vector<char>& result) const;
    void getPerm2Helper(const Node* node, int& num, std::vector<char>& result) const;
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_

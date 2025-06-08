// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <algorithm>
#include <stdexcept>
#include  "tree.h"

PMTree::PMTree(const std::vector<char>& elements) {
    if (elements.empty()) {
        throw std::invalid_argument("Input elements cannot be empty");
    }

    root = std::make_unique<Node>('\0');
    buildTree(root.get(), elements);

    totalPermutations = 1;
    for (int i = 2; i <= elements.size(); ++i) {
        totalPermutations *= i;
    }
}

void PMTree::buildTree(Node* parent, const std::vector<char>& elements) {
    for (char elem : elements) {
        parent->children.emplace_back(std::make_unique<Node>(elem));
    }

    for (auto& child : parent->children) {
        std::vector<char> remaining;
        for (char elem : elements) {
            if (elem != child->value) {
                remaining.push_back(elem);
            }
        }
        if (!remaining.empty()) {
            buildTree(child.get(), remaining);
        }
    }
}

std::vector<std::vector<char>> PMTree::getAllPerms() const {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    getAllPermsHelper(root.get(), current, result);
    return result;
}

void PMTree::getAllPermsHelper(const Node* node, std::vector<char>& current, std::vector<std::vector<char>>& result) const {
    if (node->children.empty()) {
        result.push_back(current);
        return;
    }

    for (const auto& child : node->children) {
        current.push_back(child->value);
        getAllPermsHelper(child.get(), current, result);
        current.pop_back();
    }
}

std::vector<char> PMTree::getPerm1(int num) const {
    if (num < 1 || num > totalPermutations) {
        throw std::out_of_range("Permutation number out of range");
    }

    std::vector<char> result;
    int currentNum = 0;
    getPerm1Helper(root.get(), currentNum, num, result);
    return result;
}

void PMTree::getPerm1Helper(const Node* node, int& currentNum, int targetNum, std::vector<char>& result) const {
    if (node->children.empty()) {
        currentNum++;
        return;
    }

    for (const auto& child : node->children) {
        result.push_back(child->value);
        getPerm1Helper(child.get(), currentNum, targetNum, result);
        if (currentNum == targetNum) {
            return;
        }
        result.pop_back();
    }
}

std::vector<char> PMTree::getPerm2(int num) const {
    if (num < 1 || num > totalPermutations) {
        throw std::out_of_range("Permutation number out of range");
    }

    std::vector<char> result;
    int remaining = num - 1;
    const Node* current = root.get();

    while (!current->children.empty()) {
        int branchSize = factorial(current->children.size() - 1);
        int childIndex = remaining / branchSize;
        remaining %= branchSize;

        const auto& child = current->children[childIndex];
        result.push_back(child->value);
        current = child.get();
    }

    return result;
}

int PMTree::factorial(int n) const {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    return tree.getAllPerms();
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    return tree.getPerm1(num);
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    return tree.getPerm2(num);
}

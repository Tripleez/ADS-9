// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include "tree.h"

void printPermutation(const std::vector<char>& perm) {
    for (char c : perm) std::cout << c;
    std::cout << std::endl;
}

void runExperiment(int max_n) {
    std::cout << "Вычислительный эксперимент:\n";
    std::cout << "n\tgetAllPerms (ms)\tgetPerm1 (ns)\tgetPerm2 (ns)\n";
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int n = 1; n <= max_n; ++n) {
        std::vector<char> alphabet(n);
        for (int i = 0; i < n; ++i) alphabet[i] = 'a' + i;
        PMTree tree(alphabet);
        std::uniform_int_distribution<> dist(1, tree.getAllPerms().size());
        int random_perm_num = dist(gen);
        auto start = std::chrono::high_resolution_clock::now();
        auto all_perms = tree.getAllPerms();
        auto end = std::chrono::high_resolution_clock::now();
        auto all_perms_time = std::chrono::duration_cast<
            std::chrono::milliseconds>(end - start).count();
        start = std::chrono::high_resolution_clock::now();
        auto perm1 = tree.getPerm1(random_perm_num);
        end = std::chrono::high_resolution_clock::now();
        auto perm1_time = std::chrono::duration_cast<
            std::chrono::nanoseconds>(end - start).count();
        start = std::chrono::high_resolution_clock::now();
        auto perm2 = tree.getPerm2(random_perm_num);
        end = std::chrono::high_resolution_clock::now();
        auto perm2_time = std::chrono::duration_cast<
            std::chrono::nanoseconds>(end - start).count();
        std::cout << n << "\t" << all_perms_time << "\t\t\t"
                 << perm1_time << "\t\t" << perm2_time << "\n";
    }
}

int main() {
    std::cout << "Пример работы с деревом перестановок:\n";
    std::vector<char> small_alphabet = {'1', '2', '3'};
    PMTree small_tree(small_alphabet);
    std::cout << "Все перестановки для {1,2,3}:\n";
    auto all_perms = small_tree.getAllPerms();
    for (const auto& perm : all_perms) printPermutation(perm);
    std::cout << "\nПерестановка #2 (getPerm1): ";
    printPermutation(small_tree.getPerm1(2));
    std::cout << "Перестановка #5 (getPerm2): ";
    printPermutation(small_tree.getPerm2(5));
    std::cout << "\nЗапуск вычислительного эксперимента...\n";
    runExperiment(8);
    return 0;
}

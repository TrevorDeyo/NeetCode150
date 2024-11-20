// 2 Valid Anagram.cpp : This file contains the 'main' function

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

// Function to generate anagram and non-anagram pairs
std::vector<std::pair<std::string, std::string>> generateTestPairs(size_t numPairs, int minLength, int maxLength) {
    std::vector<std::pair<std::string, std::string>> pairs;
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<> lengthDist(5, 10);
}

int main()
{
    size_t numPairs = 10; // Generate X anagram and X non-anagram pairs
    int minLength = 5;
    int maxLength = 10;

    auto testPairs = generateTestPairs(numPairs, minLength, maxLength);

    // Print generated pairs
    for (const auto& pair : testPairs) {
        std::cout << "String 1: " << pair.first << ", String 2: " << pair.second << '\n';
    }
}
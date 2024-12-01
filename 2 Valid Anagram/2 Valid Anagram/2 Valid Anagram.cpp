// 2 Valid Anagram.cpp : This file contains the 'main' function

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <utility>
#include <map>
#include <unordered_map>
#include <chrono>

// Function to generate strings
std::string generateRandomString(int wordLength, std::mt19937 rng)
{
    std::string word = "";
    std::uniform_int_distribution<int> dist('a', 'z');
    for (int lengthStep = 0; lengthStep < wordLength; lengthStep++) {
        word += static_cast<char>(dist(rng));
    }
    return word;
}

// Function to generate anagram and non-anagram pairs
std::vector<std::pair<std::string, std::string>> generateTestPairs(size_t numPairs, int wordMinLength, int wordMaxLength)
{    
    std::vector<std::pair<std::string, std::string>> pairs;
    
    std::mt19937 rng(std::random_device{}());

    for (int pairStep = 0; pairStep < numPairs; pairStep++) {
        std::uniform_int_distribution<> lengthDist(wordMinLength, wordMaxLength);
        std::uniform_int_distribution<> isAnagram(0, 1);

        std::pair<std::string, std::string> testPair;

        int wordLength = lengthDist(rng);

        testPair.first = generateRandomString(wordLength, rng);

        int anagram = isAnagram(rng);

        if (anagram == 1) {
            std::string secWord = testPair.first;
            std::shuffle(secWord.begin(), secWord.end(), rng);
            testPair.second = secWord;
        }
        else {
            testPair.second = generateRandomString(wordLength, rng);
        }
        pairs.push_back(testPair);
    }
    return pairs;
}

// my anagram solution
bool isAnagramMySolution(std::pair<std::string, std::string> testPair)
{
    // quick length check
    if (testPair.first.length() != testPair.second.length()) {
        return false;
    }

    std::map<char, int> charCount;
    for (char c : testPair.first) {
        charCount[c]++;
    }
    for (char c : testPair.second) {
        charCount[c]--;
    }
    for (const auto& pair : charCount) {
        if (pair.second != 0) {
            return false;
        }
    }
    return true;
}

bool isAnagramSorting(std::pair<std::string, std::string> testPair)
{
    if (testPair.first.length() != testPair.second.length()) {
        return false;
    }

    std::sort(testPair.first.begin(), testPair.second.end());
    std::sort(testPair.first.begin(), testPair.second.end());
    return testPair.first == testPair.second;
}

bool isAnagramHashTable(std::pair<std::string, std::string> testPair) {
    if (testPair.first.length() != testPair.second.length()) {
        return false;
    }

    std::unordered_map<char, int> countS;
    std::unordered_map<char, int> countT;
    for (int i = 0; i < testPair.first.length(); i++) {
        countS[testPair.first[i]]++;
        countT[testPair.second[i]]++;
    }
    return countS == countT;
}

bool isAnagramHashTableOptimal(std::pair<std::string, std::string> testPair) {
    if (testPair.first.length() != testPair.second.length()) {
        return false;
    }

    std::vector<int> count(26, 0);
    for (int i = 0; i < testPair.first.length(); i++) {
        count[testPair.first[i] - 'a']++;
        count[testPair.second[i] - 'a']--;
    }

    for (int val : count) {
        if (val != 0) {
            return false;
        }
    }
    return true;
}

void speedTest(std::vector<std::pair<std::string, std::string>> testPairs, bool (*algo)(std::pair<std::string, std::string>)) {
    // Start Clock
    auto start = std::chrono::high_resolution_clock::now();
    // Count the engrams
    size_t numAnagrams = 0;
    for (const auto& pair : testPairs) {
        if (algo(pair)) {
            numAnagrams += 1;
    }

    // Stop Clock
    auto stop = std::chrono::high_resolution_clock::now();
    // Print Clock
    std::cout << (stop - start) << "ms?" << "\n"
}

int main()
{
    size_t numPairs = 100000; // Generate X anagram and X non-anagram pairs
    int wordMinLength = 5;
    int wordMaxLength = 10;

    auto testPairs = generateTestPairs(numPairs, wordMinLength, wordMaxLength);
    speedTest(testPairs, isAnagramMySolution);
    speedTest(testPairs, isAnagramSorting);
    speedTest(testPairs, isAnagramHashTable);
    speedTest(testPairs, isAnagramHashTableOptimal);
    return 0;
}
// 2 Valid Anagram.cpp : This file contains the 'main' function

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <utility>
#include <map>

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


int main()
{
    size_t numPairs = 100000; // Generate X anagram and X non-anagram pairs
    int wordMinLength = 5;
    int wordMaxLength = 10;

    auto testPairs = generateTestPairs(numPairs, wordMinLength, wordMaxLength);
    
    // Print generated pairs
    size_t numAnagrams = 0;
    for (const auto& pair : testPairs) {
        if (isAnagramMySolution(pair)) {
            //std::cout << "String 1: " << pair.first << ", String 2: " << pair.second << " Anagram?: Yes" << '\n';
            numAnagrams++;
        }
        else {
            //std::cout << "String 1: " << pair.first << ", String 2: " << pair.second << " Anagram?: No" << '\n';
        }
    }
    std::cout << "there are " << numAnagrams << '\n';
}
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <utility>
#include <unordered_map>
#include <chrono>

// Function to generate a random string of a given length
std::string generateRandomString(int wordLength, std::mt19937& rng)
{
    std::string word = "";
    std::uniform_int_distribution<int> dist('a', 'z'); // Random character range: 'a' to 'z'
    for (int lengthStep = 0; lengthStep < wordLength; lengthStep++) {
        word += static_cast<char>(dist(rng)); // Append a random character
    }
    return word;
}

// Function to generate pairs of strings for testing
// Each pair will either be anagrams or non-anagrams
std::vector<std::pair<std::string, std::string>> generateTestPairs(size_t numPairs, int wordMinLength, int wordMaxLength)
{
    std::vector<std::pair<std::string, std::string>> pairs; // Vector to store the pairs
    std::mt19937 rng(std::random_device{}()); // Random number generator

    for (int pairStep = 0; pairStep < numPairs; pairStep++) {
        std::uniform_int_distribution<> lengthDist(wordMinLength, wordMaxLength); // Random length for strings
        std::uniform_int_distribution<> isAnagram(0, 1); // Randomly decide if the pair is an anagram

        std::pair<std::string, std::string> testPair; // Pair to store two strings
        int wordLength = lengthDist(rng); // Generate random length

        testPair.first = generateRandomString(wordLength, rng); // Generate the first string

        int anagram = isAnagram(rng); // Randomly determine if the pair should be an anagram

        if (anagram == 1) {
            // If the pair is an anagram, shuffle the first string to create the second
            std::string secWord = testPair.first;
            std::shuffle(secWord.begin(), secWord.end(), rng);
            testPair.second = secWord;
        }
        else {
            // If not an anagram, generate a completely new random string
            testPair.second = generateRandomString(wordLength, rng);
        }
        pairs.push_back(testPair); // Add the pair to the vector
    }
    return pairs;
}

// Custom anagram-checking solution using character counts
bool isAnagramMySolution(const std::pair<std::string, std::string>& testPair)
{
    // Quick length check
    if (testPair.first.length() != testPair.second.length()) {
        return false;
    }

    std::unordered_map<char, int> charCount;
    // Count characters in the first string
    for (char c : testPair.first) {
        charCount[c]++;
    }
    // Subtract character counts for the second string
    for (char c : testPair.second) {
        charCount[c]--;
    }
    // Verify that all character counts are zero
    for (const auto& pair : charCount) {
        if (pair.second != 0) {
            return false;
        }
    }
    return true;
}

// Anagram-checking solution using sorting
bool isAnagramSorting(const std::pair<std::string, std::string>& testPair)
{
    // Quick length check
    if (testPair.first.length() != testPair.second.length()) {
        return false;
    }

    // Create local copies of the strings
    std::string first = testPair.first;
    std::string second = testPair.second;

    // Sort both strings
    std::sort(first.begin(), first.end());
    std::sort(second.begin(), second.end());

    // Check if the sorted strings are equal
    return first == second;
}

// Anagram-checking solution using two hash tables
bool isAnagramHashTable(const std::pair<std::string, std::string>& testPair) {
    // Quick length check
    if (testPair.first.length() != testPair.second.length()) {
        return false;
    }

    // Create two hash tables to count characters
    std::unordered_map<char, int> countS;
    std::unordered_map<char, int> countT;

    // Count characters for both strings
    for (int i = 0; i < testPair.first.length(); i++) {
        countS[testPair.first[i]]++;
        countT[testPair.second[i]]++;
    }

    // Compare the two hash tables
    return countS == countT;
}

// Optimized anagram-checking solution using a single hash table
bool isAnagramHashTableOptimal(const std::pair<std::string, std::string>& testPair) {
    // Quick length check
    if (testPair.first.length() != testPair.second.length()) {
        return false;
    }

    // Use a vector for counting characters (only 26 for lowercase letters)
    std::vector<int> count(26, 0);

    // Increment counts for the first string and decrement for the second
    for (int i = 0; i < testPair.first.length(); i++) {
        count[testPair.first[i] - 'a']++;
        count[testPair.second[i] - 'a']--;
    }

    // Verify that all counts are zero
    for (int val : count) {
        if (val != 0) {
            return false;
        }
    }
    return true;
}

// Function to test the speed of a given anagram-checking algorithm
void speedTest(const std::vector<std::pair<std::string, std::string>>& testPairs,
    bool (*algo)(const std::pair<std::string, std::string>&),
    const std::string& algoName) {
    // Print the algorithm name
    std::cout << "Testing algorithm: " << algoName << "\n";

    // Start the clock
    auto start = std::chrono::high_resolution_clock::now();

    // Count the number of anagrams
    size_t numAnagrams = 0;
    for (const auto& pair : testPairs) {
        if (algo(pair)) numAnagrams++;
    }

    // Stop the clock
    auto stop = std::chrono::high_resolution_clock::now();

    // Calculate and print the duration and number of anagrams
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Duration: " << duration.count() << " ms\n";
    std::cout << "Number of anagrams: " << numAnagrams << "\n";
}

// Main function
int main()
{
    size_t numPairs = 1000000; // Number of pairs to generate
    int wordMinLength = 5;    // Minimum word length
    int wordMaxLength = 10;   // Maximum word length

    // Generate test pairs
    auto testPairs = generateTestPairs(numPairs, wordMinLength, wordMaxLength);

    // Run speed tests for each algorithm
    speedTest(testPairs, isAnagramMySolution, "My Solution");
    speedTest(testPairs, isAnagramSorting, "Sorting-Based Solution");
    speedTest(testPairs, isAnagramHashTable, "Hash Table Solution");
    speedTest(testPairs, isAnagramHashTableOptimal, "Hash Table Optimal Solution");

    return 0;
}

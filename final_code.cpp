#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>

using namespace std;

// Read file and return contents as a string
string readFile(string filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error: Could not open " << filename << endl;
        exit(1);
    }

    string content, word;
    while (file >> word) {  
        content += word + " ";
    }
    file.close();

    if (!content.empty() && content.back() == ' ')
        content.pop_back();

    return content;
}

// Convert text into a set of words
unordered_set<string> getWords(string text) {
    unordered_set<string> words;
    stringstream ss(text);
    string word;
    while (ss >> word) {
        words.insert(word); // Store each word
    }
    return words;
}

// Compute word similarity percentage
double computeSimilarity(string text, string pattern) {
    unordered_set<string> textWords = getWords(text);
    unordered_set<string> patternWords = getWords(pattern);

    int commonWords = 0;
    for (const string &word : patternWords) {
        if (textWords.find(word) != textWords.end()) {
            commonWords++; // Count matching words
        }
    }

    int totalWords = patternWords.size();
    return (double(commonWords) / totalWords) * 100;
}

// Display plagiarism results
void displayResults(string text, string pattern) {
    double similarity = computeSimilarity(text, pattern);

    cout << "Plagiarism Similarity Score: " << similarity << "%\n";

    if (similarity > 0) {
        cout << "Partial plagiarism detected!\n";
    } else {
        cout << "No plagiarism detected.\n";
    }
}

int main() {
    string mainText, pattern;

    cout << "Enter main document filename: ";
    string mainFile;
    cin >> mainFile;
    mainText = readFile(mainFile);

    cout << "Enter pattern document filename: ";
    string patternFile;
    cin >> patternFile;
    pattern = readFile(patternFile);

    displayResults(mainText, pattern);
    return 0;
}

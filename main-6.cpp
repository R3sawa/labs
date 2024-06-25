#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

int main() {
    ifstream inputFile("/Users/kirilldrapeza/Documents/study/labb5/labb5/input.txt");
    ofstream outputFile("/Users/kirilldrapeza/Documents/study/labb5/output.txt");

    if (!inputFile.is_open()) {
        cerr << "Unable to open input file." << endl;
        return 1;
    }

    if (!outputFile.is_open()) {
        cerr << "Unable to open output file." << endl;
        return 1;
    }

    regex withBrackets("\\{[ 0-9a-fA-F]{}-[//da-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}\\}");
    //regex withoutBrackets("[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}");
    regex withoutBrackets("[0-9a-fA-F]{8}-([0-9a-fA-F]{4}-){3}[0-9a-fA-F]{12}");
    string line;
    while (getline(inputFile, line)) {
        if (regex_match(line, withBrackets) || regex_match(line, withoutBrackets)) {
            outputFile << line << " - Valid" << endl;
        } else {
            outputFile << line << " - Invalid" << endl;
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}

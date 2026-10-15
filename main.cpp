#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

string makeLowercase(string text) {
    for (size_t i = 0; i < text.length(); i++) {
        text[i] = tolower(static_cast<unsigned char>(text[i]));
    }
    return text;
}

bool containsPhrase(string email, string phrase) {
    return email.find(phrase) != string::npos;
}

string readEmail() {
    string email = "";
    string line;

    cout << "Paste your email below. Type END on its own line when finished:\n";
    while (getline(cin, line)) {
        if (line == "END") {
            break;
        }
        email += line + "\n";
    }
    return email;
}

string readFile() {
    string fileName;
    string line;
    string email = "";

    cout << "Enter the file name: ";
    getline(cin, fileName);
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cout << "Could not open the file.\n";
        return "";
    }

    while (getline(inputFile, line)) {
        email += line + "\n";
    }
    inputFile.close();
    return email;
}

void checkEmail(string email) {
    email = makeLowercase(email);
    int score = 0;
    vector<string> warnings;

    // Each category adds points only once.
    if (containsPhrase(email, "urgent") || containsPhrase(email, "act now") ||
        containsPhrase(email, "account suspended") || containsPhrase(email, "immediately")) {
        score += 20;
        warnings.push_back("Urgent or threatening language (+20)");
    }

    if (containsPhrase(email, "verify your account") ||
        containsPhrase(email, "confirm your identity") ||
        containsPhrase(email, "provide your password") ||
        containsPhrase(email, "update your payment")) {
        score += 30;
        warnings.push_back("Request to verify an account or give information (+30)");
    }

    if (containsPhrase(email, "you won") || containsPhrase(email, "claim your prize") ||
        containsPhrase(email, "free money")) {
        score += 15;
        warnings.push_back("Prize or reward language (+15)");
    }

    if (containsPhrase(email, "http://")) {
        score += 15;
        warnings.push_back("Email includes an HTTP link (+15)");
    }

    if (containsPhrase(email, "http://") || containsPhrase(email, "https://")) {
        // A simple check for unusual-looking URL text.
        if (containsPhrase(email, "@")) {
            score += 10;
            warnings.push_back("Email contains a link and an @ symbol (+10)");
        }
    }

    if (score > 100) {
        score = 100;
    }

    cout << "\n----- Email Analysis -----\n";
    if (warnings.empty()) {
        cout << "No warning signs matched the program's rules.\n";
    } else {
        for (size_t i = 0; i < warnings.size(); i++) {
            cout << "- " << warnings[i] << "\n";
        }
    }

    cout << "Risk score: " << score << "/100\n";
    if (score >= 60) {
        cout << "Risk level: HIGH\n";
    } else if (score >= 30) {
        cout << "Risk level: MEDIUM\n";
    } else {
        cout << "Risk level: LOW\n";
    }
    cout << "This is only a basic warning tool, not proof an email is safe or unsafe.\n";
}

int main() {
    string email;
    string answer;

    cout << "Phishing Email Detector\n";
    cout << "1. Paste an email\n";
    cout << "2. Open an email from a text file\n";
    cout << "Choose an option (1 or 2): ";
    getline(cin, answer);

    if (answer == "1") {
        email = readEmail();
    } else if (answer == "2") {
        email = readFile();
    } else {
        cout << "Invalid option.\n";
        return 0;
    }

    if (email.empty()) {
        cout << "No email was entered.\n";
        return 0;
    }
    checkEmail(email);
    return 0;
}

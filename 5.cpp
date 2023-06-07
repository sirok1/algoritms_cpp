//задание 1
#include <iostream>
#include <string>

std::string encryptCaesar(const std::string& text, int key) {
    std::string encryptedText;

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char encryptedChar = (c - base + key) % 26 + base;
            encryptedText += encryptedChar;
        } else {
            encryptedText += c;
        }
    }

    return encryptedText;
}

int main() {
    std::string text;
    int key;

    std::cout << "Enter the text for encryption: ";
    std::getline(std::cin, text);

    std::cout << "Enter the encryption key (an integer number): ";
    std::cin >> key;

    std::string encryptedText = encryptCaesar(text, key);

    std::cout << "Encrypted text: " << encryptedText << std::endl;

    return 0;
}
//Задание 3
#include <iostream>
#include <string>
#include <unordered_map>

std::string encryptSubstitution(const std::string& text, const std::unordered_map<char, char>& substitutionTable) {
    std::string encryptedText;

    for (char c : text) {
        char encryptedChar = c;

        auto it = substitutionTable.find(std::tolower(c));
        if (it != substitutionTable.end()) {
            encryptedChar = std::islower(c) ? it->second : std::toupper(it->second);
        }

        encryptedText += encryptedChar;
    }

    return encryptedText;
}

int main() {
    std::string text;
    std::unordered_map<char, char> substitutionTable = {
            {'a', 'G'}, {'b', 'O'}, {'c', 'Y'}, {'d', 'D'}, {'e', 'S'}, {'f', 'I'}, {'g', 'P'}, {'h', 'E'},
            {'i', 'L'}, {'j', 'U'}, {'k', 'A'}, {'l', 'V'}, {'m', 'C'}, {'n', 'R'}, {'o', 'J'}, {'p', 'W'},
            {'q', 'X'}, {'r', 'Z'}, {'s', 'N'}, {'t', 'H'}, {'u', 'B'}, {'v', 'Q'}, {'w', 'F'}, {'x', 'T'},
            {'y', 'M'}, {'z', 'K'}
    };

    std::cout << "Enter the text for encryption: ";
    std::getline(std::cin, text);

    std::string encryptedText = encryptSubstitution(text, substitutionTable);

    std::cout << "Encrypted text: " << encryptedText << std::endl;

    return 0;
}
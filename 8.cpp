//1
//#include <iostream>
//
//int extendedEuclideanAlgorithm(int a, int b, int& x, int& y) {
//    if (a == 0) {
//        x = 0;
//        y = 1;
//        return b;
//    }
//
//    int x1, y1;
//    int gcd = extendedEuclideanAlgorithm(b % a, a, x1, y1);
//
//    x = y1 - (b / a) * x1;
//    y = x1;
//
//    return gcd;
//}
//
//int main() {
//    int a, b;
//    std::cout << "Enter two numbers: ";
//    std::cin >> a >> b;
//
//    int x, y;
//    int gcd = extendedEuclideanAlgorithm(a, b, x, y);
//
//    std::cout << "GCD(" << a << ", " << b << ") = " << gcd << std::endl;
//    std::cout << "Linear coefficients: x = " << x << ", y = " << y << std::endl;
//
//    return 0;
//}

//2
#include <iostream>
#include <cmath>
#include <random>
#include <vector>

// Функция для проверки простоты числа
bool isPrime(int number) {
    if (number < 2)
        return false;

    for (int i = 2; i <= sqrt(number); ++i) {
        if (number % i == 0)
            return false;
    }

    return true;
}

// Функция для генерации случайного простого числа
int generatePrime() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(2, 100);

    int number = dis(gen);
    while (!isPrime(number)) {
        number = dis(gen);
    }

    return number;
}

// Функция для преобразования строки в числовое значение
std::vector<int> stringToNumbers(const std::string& str) {
    std::vector<int> result;

    for (char ch : str) {
        result.push_back(static_cast<int>(ch));
    }

    return result;
}

// Функция для преобразования числовых значений в строку
std::string numbersToString(const std::vector<int>& numbers) {
    std::string result;

    for (int num : numbers) {
        result += static_cast<char>(num);
    }

    return result;
}

// Функция для вычисления наибольшего общего делителя (НОД)
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Функция для генерации открытого и секретного ключей
void generateKeys(int& publicKey, int& privateKey, int& modulus) {
    int p = generatePrime();
    int q = generatePrime();

    int phi = (p - 1) * (q - 1);
    modulus = p * q;

    publicKey = 2;
    while (publicKey < phi) {
        if (gcd(publicKey, phi) == 1)
            break;
        else
            publicKey++;
    }

    int k = 1;
    while (true) {
        k = k + phi;
        if (k % publicKey == 0) {
            privateKey = k / publicKey;
            break;
        }
    }
}

// Функция для шифрования сообщения
std::vector<int> encrypt(const std::vector<int>& message, int publicKey, int modulus) {
    std::vector<int> encryptedMessage;

    for (int num : message) {
        int encryptedNum = 1;

        for (int i = 0; i < publicKey; ++i) {
            encryptedNum = (encryptedNum * num) % modulus;
        }

        encryptedMessage.push_back(encryptedNum);
    }

    return encryptedMessage;
}

// Функция для расшифровки сообщения
std::vector<int> decrypt(const std::vector<int>& encryptedMessage, int privateKey, int modulus) {
    std::vector<int> decryptedMessage;

    for (int num : encryptedMessage) {
        int decryptedNum = 1;

        for (int i = 0; i < privateKey; ++i) {
            decryptedNum = (decryptedNum * num) % modulus;
        }

        decryptedMessage.push_back(decryptedNum);
    }

    return decryptedMessage;
}

int main() {
    int publicKey, privateKey, modulus;

    generateKeys(publicKey, privateKey, modulus);

    std::string message;
    std::cout << "Enter a message to encrypt: ";
    std::getline(std::cin >> std::ws, message);

    std::vector<int> numericMessage = stringToNumbers(message);
    std::vector<int> encryptedMessage = encrypt(numericMessage, publicKey, modulus);
    std::cout << "Encrypted message: ";
    for (int num : encryptedMessage) {
        std::cout << num << " ";
    }
    std::cout << std::endl;


    std::vector<int> decryptedMessage = decrypt(encryptedMessage, privateKey, modulus);
    std::string decryptedText = numbersToString(decryptedMessage);
    std::cout << "Decrypted message: " << decryptedText << std::endl;

    return 0;
}
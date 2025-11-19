#include <iostream>
#include <string>
#include <cctype>

// Simple Rotor class - mimics the rotating wheels in Enigma machine
class Rotor {
private:
    int position; // current position of the rotor
    int offset;   // how much to shift characters

public:
    // Constructor - sets up the rotor with an initial offset
    Rotor(int initialOffset) {
        offset = initialOffset;
        position = 0;
    }

    // Encrypt a single character
    char encrypt(char c) {
        // Only encrypt letters, leave other characters alone
        if (isalpha(c)) {
            bool isUpper = isupper(c);
            c = toupper(c); // work with uppercase

            // Shift the character
            c = c - 'A'; // convert to 0-25
            c = (c + offset + position) % 26; // apply rotor offset and position
            c = c + 'A'; // convert back to letter

            // Return in original case
            if (!isUpper) {
                c = tolower(c);
            }
        }
        return c;
    }

    // Rotate the rotor (happens after each character)
    void rotate() {
        position = (position + 1) % 26;
    }

    // Reset rotor to starting position
    void reset() {
        position = 0;
    }

    // Get current position
    int getPosition() {
        return position;
    }
};

// Simple Enigma Machine class
class EnigmaMachine {
private:
    Rotor rotor1;
    Rotor rotor2;
    Rotor rotor3;

public:
    // Constructor - initialize with three rotors
    EnigmaMachine(int offset1, int offset2, int offset3)
        : rotor1(offset1), rotor2(offset2), rotor3(offset3) {
    }

    // Encrypt/decrypt a message
    std::string process(std::string message) {
        std::string result = "";

        // Process each character
        for (int i = 0; i < message.length(); i++) {
            char c = message[i];

            // Pass through all three rotors
            c = rotor1.encrypt(c);
            c = rotor2.encrypt(c);
            c = rotor3.encrypt(c);

            result += c;

            // Rotate rotors (rotor1 rotates every time)
            rotor1.rotate();

            // Rotor2 rotates when rotor1 completes a full rotation
            if (rotor1.getPosition() == 0) {
                rotor2.rotate();
            }

            // Rotor3 rotates when rotor2 completes a full rotation
            if (rotor2.getPosition() == 0 && rotor1.getPosition() == 0) {
                rotor3.rotate();
            }
        }

        // Reset rotors for next use
        rotor1.reset();
        rotor2.reset();
        rotor3.reset();

        return result;
    }
};

int main() {
    std::cout << "==================================" << std::endl;
    std::cout << "  Simple Enigma Encryption Tool  " << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << std::endl;

    // Get rotor settings from user
    int offset1, offset2, offset3;

    std::cout << "Enter rotor 1 offset (0-25): ";
    std::cin >> offset1;
    std::cout << "Enter rotor 2 offset (0-25): ";
    std::cin >> offset2;
    std::cout << "Enter rotor 3 offset (0-25): ";
    std::cin >> offset3;

    // Clear the input buffer
    std::cin.ignore();

    // Create the enigma machine
    EnigmaMachine enigma(offset1, offset2, offset3);

    std::cout << std::endl;
    std::cout << "Enigma machine ready!" << std::endl;
    std::cout << "Note: Encryption is reversible - encrypt the encrypted message to get original back!" << std::endl;
    std::cout << std::endl;

    // Main loop
    while (true) {
        std::cout << "Enter message to encrypt (or 'quit' to exit): ";
        std::string message;
        std::getline(std::cin, message);

        // Check if user wants to quit
        if (message == "quit" || message == "exit") {
            std::cout << "Goodbye!" << std::endl;
            break;
        }

        // Encrypt the message
        std::string encrypted = enigma.process(message);

        std::cout << "Encrypted: " << encrypted << std::endl;
        std::cout << std::endl;
    }

    return 0;
}

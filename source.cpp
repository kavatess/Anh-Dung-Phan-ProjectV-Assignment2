#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Struct to store student name details
struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;
};

int main() {
    std::vector<STUDENT_DATA> students;
    std::ifstream inputFile("StudentData.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open StudentData.txt" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string lastName;
        std::string firstName;

        if (std::getline(ss, lastName, ',') && std::getline(ss, firstName)) {
            // Trim leading whitespace if present after the comma
            if (!firstName.empty() && firstName[0] == ' ') {
                firstName.erase(0, 1);
            }

            STUDENT_DATA student;
            student.firstName = firstName;
            student.lastName = lastName;

            students.push_back(student);
        }
    }

    inputFile.close();

    // Print student information only if compiled in debug mode
#if defined(_DEBUG) || !defined(NDEBUG)
    for (const auto& student : students) {
        std::cout << student.firstName << " " << student.lastName << std::endl;
    }
#endif

    return 0;
}
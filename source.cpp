#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Struct to store student data
struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;
#ifdef PRE_RELEASE
    std::string email;
#endif
};

int main() {
#ifdef PRE_RELEASE
    std::cout << "Application is running Pre-Release source code." << std::endl;
    std::string filename = "StudentData_Emails.txt";
#else
    std::cout << "Application is running Standard source code." << std::endl;
    std::string filename = "StudentData.txt";
#endif

    std::vector<STUDENT_DATA> students;
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open " << filename << std::endl;
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

#ifdef PRE_RELEASE
        std::string email;
        if (std::getline(ss, lastName, ',') &&
            std::getline(ss, firstName, ',') &&
            std::getline(ss, email)) {

            if (!firstName.empty() && firstName[0] == ' ') {
                firstName.erase(0, 1);
            }

            STUDENT_DATA student;
            student.lastName = lastName;
            student.firstName = firstName;
            student.email = email;

            students.push_back(student);
        }
#else
        // Standard parsing for StudentData.txt (LastName, FirstName)
        if (std::getline(ss, lastName, ',') && std::getline(ss, firstName)) {
            if (!firstName.empty() && firstName[0] == ' ') {
                firstName.erase(0, 1);
            }

            STUDENT_DATA student;
            student.lastName = lastName;
            student.firstName = firstName;

            students.push_back(student);
        }
#endif
    }

    inputFile.close();

    // Print student details only when compiled in Debug mode
#if defined(_DEBUG)
    for (const auto& student : students) {
        std::cout << student.firstName << " " << student.lastName;
#ifdef PRE_RELEASE
        std::cout << " | " << student.email;
#endif
        std::cout << std::endl;
    }
#endif

    return 0;
}
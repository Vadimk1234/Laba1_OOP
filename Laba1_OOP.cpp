#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>


struct StudentBinary {
    int id;
    char name[50];
    int age;
    double gpa;
};


struct StudentText {
    int id;
    std::string name;
    int age;
    double gpa;
};

void writeAndReadTextFormat(const std::vector<StudentText>& students, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing (text)!" << std::endl;
        return;
    }

    for (const auto& s : students) {
        outFile << s.id << " " << s.name << " " << s.age << " " << s.gpa << "\n";
    }
    outFile.close();
    std::cout << "[Text mode] Data successfully written to file: " << filename << std::endl;


    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Error opening file for reading!" << std::endl;
        return;
    }

    std::cout << "\n--- Data read from a text file ---" << std::endl;
    StudentText temp;
    while (inFile >> temp.id >> temp.name >> temp.age >> temp.gpa) {
        std::cout << "ID: " << std::setw(2) << temp.id
            << " Name: " << std::setw(10) << temp.name
            << " Age: " << temp.age
            << " Average mark: " << temp.gpa << std::endl;
    }
    inFile.close();
}

// 2. Спосіб: Запис та читання бінарної структури
void writeAndReadBinaryFormat(const std::vector<StudentBinary>& students, const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing (binary)!" << std::endl;
        return;
    }
    outFile.write(reinterpret_cast<const char*>(students.data()), students.size() * sizeof(StudentBinary));
    outFile.close();
    std::cout << "\n[Binary mode (structures)] Data successfully written to file: " << filename << std::endl;

    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Error opening file for reading !" << std::endl;
        return;
    }

    std::vector<StudentBinary> readStudents(students.size());
    inFile.read(reinterpret_cast<char*>(readStudents.data()), readStudents.size() * sizeof(StudentBinary));
    inFile.close();
    for (const auto& s : readStudents) {
        std::cout << "ID: " << std::setw(2) << s.id
            << " Name: " << std::setw(10) << s.name
            << " Age: " << s.age
            << " Average mark: " << s.gpa << std::endl;
    }
}

int main() {    

        std::vector<StudentText> textStudents = {
        {1, "Oleh", 18, 4.5},
        {2, "Anna", 19, 4.8},
        {3, "Ivan", 18, 3.9},
        {4, "Maryna", 20, 4.2},
        {5, "Denys", 19, 3.7},
        {6, "Olha", 18, 4.9},
        {7, "Pavlo", 21, 3.5},
        {8, "Iryna", 19, 4.0},
        {9, "Maksym", 18, 4.6},
        {10, "Yulia", 20, 4.1}
    };

    std::vector<StudentBinary> binaryStudents = {
        {1, "Oleh", 18, 4.5},
        {2, "Anna", 19, 4.8},
        {3, "Ivan", 18, 3.9},
        {4, "Maryna", 20, 4.2},
        {5, "Denys", 19, 3.7},
        {6, "Olha", 18, 4.9},
        {7, "Pavlo", 21, 3.5},
        {8, "Iryna", 19, 4.0},
        {9, "Maksym", 18, 4.6},
        {10, "Yulia", 20, 4.1}
    };

    // Виклики функцій для обох способів
    writeAndReadTextFormat(textStudents, "students.txt");
    writeAndReadBinaryFormat(binaryStudents, "students.bin");

    return 0;
}
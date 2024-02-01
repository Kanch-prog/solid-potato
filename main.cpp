#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Student {
    std::string name;
    double subject1Marks;  
    double subject2Marks;  
    double subject3Marks;  
    double totalMarks;
    int classNumber;
    int rank;
};

// Function to save student data to a CSV file
void saveStudentDataToCSV(const std::string& filename, const std::vector<Student>& students) {
    std::ofstream outputFile(filename);
    if (outputFile.is_open()) {
        for (const Student& student : students) {
            outputFile << student.name << ',' << student.subject1Marks << ',' << student.subject2Marks << ',' << student.subject3Marks << '\n';
        }
        outputFile.close();
        std::cout << "Data written to " << filename << std::endl;
    } else {
        std::cerr << "Error opening the file for writing." << std::endl;
    }
}

// Function to calculate total marks for a student
void calculateTotalMarks(std::vector<Student>& students) {
    for (Student& student : students) {
        student.totalMarks = student.subject1Marks + student.subject2Marks + student.subject3Marks;
    }
}

// Function to compare students for sorting by total marks
bool compareStudents(const Student& a, const Student& b) {
    return a.totalMarks > b.totalMarks;
}

// Function to calculate ranks for students
void calculateRanks(std::vector<Student>& students) {
    std::sort(students.begin(), students.end(), compareStudents);
    for (int i = 0; i < students.size(); ++i) {
        students[i].rank = i + 1;
    }
}

// Function to print results to console and write to file
void printAndWriteResults(const std::vector<Student>& students, const std::string& streamType) {
    std::ofstream outputFile(streamType + "_rank_results.txt");
    if (outputFile.is_open()) {
        std::cout << streamType << " Stream Results:" << std::endl;
        for (const Student& student : students) {
            std::cout << "Name: " << student.name << "\tTotal Marks: " << std::fixed << std::setprecision(2) << student.totalMarks
                      << "\tClass: " << student.classNumber << "\tRank: " << student.rank << std::endl;

            outputFile << "Name: " << student.name << "\tTotal Marks: " << student.totalMarks
                       << "\tClass: " << student.classNumber << "\tRank: " << student.rank << std::endl;
        }
        outputFile.close();
        std::cout << "Results written to " << streamType << "_rank_results.txt" << std::endl;
    } else {
        std::cerr << "Error opening the file for writing." << std::endl;
    }
}

int main() {
    // Example data for math and bio students
    std::vector<Student> bioStudents = {
        {"Kamal", 80, 85, 90},
        {"Nimal", 75, 90, 85},
        {"Wimal", 88, 92, 78}
    };

    std::vector<Student> mathStudents = {
        {"Kamala", 85, 88, 92},
        {"Nimala", 90, 82, 95},
        {"Susila", 78, 95, 89}
    };

    // Calculate total marks and ranks for bio students
    calculateTotalMarks(bioStudents);
    calculateRanks(bioStudents);
    
    // Calculate total marks and ranks for math students
    calculateTotalMarks(mathStudents);
    calculateRanks(mathStudents);

    // Print and write results for bio students
    printAndWriteResults(bioStudents, "Bioscience");

    // Print and write results for math students
    printAndWriteResults(mathStudents, "Math");

    // Save student data to CSV files
    saveStudentDataToCSV("bio_data_output.csv", bioStudents);
    saveStudentDataToCSV("math_data_output.csv", mathStudents);

    return 0;
}

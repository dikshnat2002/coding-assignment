#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <fstream>
#include <sstream>

// Global data structure to store processed data
std::vector<std::string> processedData;

// Mutex for synchronization
std::mutex dataMutex;

// Function to process data from a source file
void processDataFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Simulate data processing by appending "Processed: " to each line
        std::string processedLine = "Processed: " + line;

        // Synchronize access to the shared data structure
        std::lock_guard<std::mutex> lock(dataMutex);
        processedData.push_back(processedLine);
    }

    file.close();
}

int main() {
    // List of input files
    std::vector<std::string> inputFiles = {"input1.txt", "input2.txt"};

    // Container for thread objects
    std::vector<std::thread> threads;

    // Create and start threads
    for (const auto& file : inputFiles) {
        threads.emplace_back(processDataFromFile, file);
    }

    // Join threads to wait for their completion
    for (auto& thread : threads) {
        thread.join();
    }

    // Output processed data
    for (const auto& data : processedData) {
        std::cout << data << std::endl;
    }

    return 0;
}

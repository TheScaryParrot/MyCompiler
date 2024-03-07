#pragma once

#include <string>
#include <fstream>

class InputFile {
public:
    InputFile(std::string filename);
    ~InputFile();

    /// @brief Reads the next character from the file. And advances the file pointer.
    std::string ReadNext();

    /// @brief Peeks the next character from the file. Doesnt advance the file pointer.
    std::string PeekNext();

    bool IsEndOfFile();
    bool IsGood();

private:
    std::ifstream file;
};

InputFile::InputFile(std::string filename) {
    file.open(filename);
}

InputFile::~InputFile() {
    file.close();
}

std::string InputFile::ReadNext() {
    return std::string(1, file.get());
}

std::string InputFile::PeekNext() {
    return std::string(1, file.peek());
}

bool InputFile::IsEndOfFile() {
    return file.eof();
}

bool InputFile::IsGood() {
    return file.good();
}
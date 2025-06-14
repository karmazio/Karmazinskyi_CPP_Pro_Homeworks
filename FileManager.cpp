#define _CRT_SECURE_NO_WARNINGS

#include "FileManager.hpp"
#include <stdexcept>

FileManager::FileManager(const std::string& filename, std::string mode) {
    file = std::fopen(filename.c_str(), mode.c_str());
    if (!file) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
}

FileManager::~FileManager() {
    if (file) {
        std::fclose(file);
    }
}

void FileManager::write(const std::string& text) {
    if (std::fputs(text.c_str(), file) == EOF) {
        throw std::runtime_error("Failed to write to file");
    }
}
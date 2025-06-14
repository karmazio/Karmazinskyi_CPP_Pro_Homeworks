#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <string>
#include <cstdio>

class FileManager {
private:
    std::FILE* file;

public:
    FileManager(const std::string& filename, std::string mode = "a");
    ~FileManager();

    void write(const std::string& text);


    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;
};

#endif 
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class SimpleOneOS {
public:
    SimpleOneOS() {
        std::cout << "Welcome to SimpleOneOS! Type 'help' to see available commands.\n";
    }

    void createFile(const std::string& filename) {
        std::ofstream file(filename);
        if (file) {
            std::cout << "File '" << filename << "' created successfully.\n";
        } else {
            std::cout << "Failed to create file '" << filename << "'.\n";
        }
    }

    void createDirectory(const std::string& dirname) {
        if (fs::create_directories(dirname)) {
            std::cout << "Directory '" << dirname << "' created successfully.\n";
        } else {
            std::cout << "Failed to create directory '" << dirname << "' or it already exists.\n";
        }
    }

    void listContents(const std::string& path = ".") {
        for (const auto& entry : fs::directory_iterator(path)) {
            std::cout << entry.path().filename().string() << std::endl;
        }
    }

    void deleteFile(const std::string& filename) {
        if (fs::remove(filename)) {
            std::cout << "File '" << filename << "' deleted successfully.\n";
        } else {
            std::cout << "File '" << filename << "' not found.\n";
        }
    }

    void deleteDirectory(const std::string& dirname) {
        if (fs::remove_all(dirname) > 0) {
            std::cout << "Directory '" << dirname << "' deleted successfully.\n";
        } else {
            std::cout << "Directory '" << dirname << "' not found.\n";
        }
    }

    void renameFile(const std::string& oldName, const std::string& newName) {
        try {
            fs::rename(oldName, newName);
            std::cout << "'" << oldName << "' renamed to '" << newName << "'.\n";
        } catch (const fs::filesystem_error& e) {
            std::cout << "Error renaming: " << e.what() << std::endl;
        }
    }

    void run() {
        std::string command;
        while (true) {
            std::cout << "SimpleOneOS> ";
            std::getline(std::cin, command);
            std::istringstream iss(command);
            std::string cmd;
            iss >> cmd;

            if (cmd == "exit") {
                std::cout << "Exiting SimpleOneOS. Goodbye!\n";
                break;
            } else if (cmd == "help") {
                showHelp();
            } else if (cmd == "createfile") {
                std::string filename;
                iss >> filename;
                if (!filename.empty()) {
                    createFile(filename);
                } else {
                    std::cout << "Usage: createfile <filename>\n";
                }
            } else if (cmd == "createdir") {
                std::string dirname;
                iss >> dirname;
                if (!dirname.empty()) {
                    createDirectory(dirname);
                } else {
                    std::cout << "Usage: createdir <dirname>\n";
                }
            } else if (cmd == "list") {
                std::string path;
                iss >> path;
                if (!path.empty()) {
                    listContents(path);
                } else {
                    listContents();
                }
            } else if (cmd == "deletefile") {
                std::string filename;
                iss >> filename;
                if (!filename.empty()) {
                    deleteFile(filename);
                } else {
                    std::cout << "Usage: deletefile <filename>\n";
                }
            } else if (cmd == "deletedir") {
                std::string dirname;
                iss >> dirname;
                if (!dirname.empty()) {
                    deleteDirectory(dirname);
                } else {
                    std::cout << "Usage: deletedir <dirname>\n";
                }
            } else if (cmd == "rename") {
                std::string oldName, newName;
                iss >> oldName >> newName;
                if (!oldName.empty() && !newName.empty()) {
                    renameFile(oldName, newName);
                } else {
                    std::cout << "Usage: rename <oldname> <newname>\n";
                }
            } else {
                std::cout << "Unknown command: " << cmd << "\n";
            }
        }
    }

private:
    void showHelp() {
        std::cout << "Available commands:\n"
                  << "createfile <filename>   - Create a new empty file\n"
                  << "createdir <dirname>     - Create a new directory\n"
                  << "list [path]             - List files and directories\n"
                  << "deletefile <filename>   - Delete a file\n"
                  << "deletedir <dirname>     - Delete a directory and its contents\n"
                  << "rename <oldname> <newname> - Rename a file or directory\n"
                  << "exit                    - Exit the OS\n";
    }
};

int main() {
    SimpleOneOS os_shell;
    os_shell.run();
    return 0;
}

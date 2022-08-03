//
// Created by Quinton Schwagle on 8/2/22.
//

#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <sys/stat.h>

std::string MakeRelativeToCurrentDirectory(const std::string& directory) {
    std::stringstream out;
    out << "./";
    out << directory;
    return out.str();
}

std::string AppendFileNameToDirectory(const std::string& directory, const std::string file_name) {
    std::stringstream out;
    out << directory;
    out << "/";
    out << file_name;
    return out.str();
}

const mode_t USER_READ_WRITE_EXECUTE = 0700;

int main(int argc, char** argv)
{
    std::cout << "C++ Project scaffolding" << std::endl;

    if(argc < 2) {
        std::cout << "Please provide a project name. the project name must be lowercase and may contain underscores" << std::endl;
        return 0;
    }

    std::string project_name(argv[1]);

    for(auto c: project_name) {
        if(c != '_' && !( isalpha(c) && islower(c))) {
            std::cout <<"Project names should be lower case seperated by an underscore" << std::endl;
            return 0;
        }
    }

    std::cout << "attempting to generate structure" << std::endl;

    auto relative_project_directory = MakeRelativeToCurrentDirectory(project_name);

    struct stat st = {0};

    if(stat(relative_project_directory.c_str(), &st) == -1) {
        // create the project directory
        mkdir(relative_project_directory.c_str(), USER_READ_WRITE_EXECUTE);

        // create the "src" directory inside the project directory
        std::string src_directory = AppendFileNameToDirectory(relative_project_directory, "src");
        mkdir(src_directory.c_str(), USER_READ_WRITE_EXECUTE);


        // create the "include" directory inside the project directory
        std::string include_directory = AppendFileNameToDirectory(relative_project_directory, "include");
        mkdir(include_directory.c_str(), USER_READ_WRITE_EXECUTE);

        // create "include/project_directory" directory inside the project directory
        std::string include_directory_project = AppendFileNameToDirectory(include_directory, project_name);
        mkdir(include_directory_project.c_str(), USER_READ_WRITE_EXECUTE);

        // create "tests" inside the project directory
        std::string tests_directory = AppendFileNameToDirectory(relative_project_directory,"tests");
        mkdir(tests_directory.c_str(), USER_READ_WRITE_EXECUTE);

        // Create the cmake file
        std::string cmake_file_path = AppendFileNameToDirectory(relative_project_directory, "CMakeLists.txt");
        std::fstream cmake_file;
        cmake_file.open(cmake_file_path, std::fstream::out);
        cmake_file << "";
        cmake_file.close();
        std::cout << "Complete" << std::endl;
    } else {
        std::cout << "project directory already exists. Aborting!!!" << std::endl;
        return 0;
    }
}

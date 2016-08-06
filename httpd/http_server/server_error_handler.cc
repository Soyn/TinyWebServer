/*****************************************************
* @Author: Soyn
* @Brief: My server's error handle implementation
* @CratedTime: 30/10/15
* @RefactorTime: Soyn at 30/4/16
******************************************************/



#include "server_error_handler.hpp"

const double ErrorHandler::version_ = 1.1 ;

std::map<std::string, std::string>SupportFileType = {
    { "gif", "image/gif"},
    { "jpg", "image/jpg"},
    { "jpeg", "image/jpeg"},
    { "png", "image/png"},
    { "ico", "image/ico"},
    { "zip", "image/zip"},
    { "gz", "image/gz"},
    { "tar", "image/tar"},
    { "htm", "text/html"},
    { "html", "text/html"}
};

//
// @Brief: Check the request is valid or not.
void ErrorHandler::CheckRequestSupportedOrNot()
{

    std::cout << "\t\t\t\033[7m YWeb( Version "<< version_ << ")\033[m" << std::endl;
    if((argument_counts_ != 3 ||
        !strcmp(arguments_values_[1], "-?"))){
        std::cout << "====================================================\
===================" << std::endl;
        std::cout << "\tHint: Port-Number Top-Directory\t\t" <<
        "\n\n\tYWeb is a small and very safe mini web server\n\t" <<
         "YWeb only servers out file /web pages with extensions named below\n\t"
         << "and only from the named directory or its sub-directory.\n\t" <<
         "There is no fancy features\n\n\t" <<
         "Example: ./YWeb 8181 /home/Ywebdir\n\n\tOnly Supports: \n\n\t";

         for(auto iter = SupportFileType.begin(); iter !=
            SupportFileType.end(); ++iter){
            std::cout << iter->first << " ";
         }

        std::cout << "\n";
        std::cout << "\n\tNot Supported: URLs including\"...\",Java, "
        << "Javascript, CGI\n\n\tNot Support directories: / /etc, /bin, /lib,"
        << "/tmp, /usr, /dev, /sbin\n\n\tNo warranty given or implied\n" << std::endl;
        std::cout << "====================================================\
===================" << std::endl;
        exit(0);
    }


}

//
// @Brief: Check the request's directory is valid or not.
void ErrorHandler::CheckRequestDirectoryValidOrNot()
{
    std::vector<std::string> not_supported_directories{
        "/", "/etc", "/bin", "/lib", "/tmp", "usr", "/dev", "/sbin",
        "/etc/", "/bin/", "/lib/", "/tmp/", "/usr/", "/dev/", "/sbin/"
    };
    std::cout << arguments_values_[2] << std::endl;
    for(const auto directory : not_supported_directories){
        if(directory.compare(arguments_values_[2]) == 0){
            std::cout << "ERROR: Bad top directory ==> " <<
            arguments_values_[2] << std::endl;
            exit(3);
        }

    }
}

//
// @Brief: Check the change directory action is valid or not
void ErrorHandler::CheckChangeDirectoryValidOrNot()
{
    if(chdir(arguments_values_[2]) == -1){
        std::cout << "ERROR: Can Not Chanhe The Directory ==> " <<
        arguments_values_[2] << std::endl;
        exit(4);
    }
}

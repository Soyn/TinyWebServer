/*************************************************************************
    > File Name: HttpServer.cpp
    > Author: Soyn
    > @Brief: the simple http server
    > Created time: 1/11/15.
 ************************************************************************/

#include <iostream>
#include "HttpServer.h"


using std :: string;

HttpServer :: HttpServer(int argc, char **argv)
{
    this -> argc = argc;
    this -> argv = argv;
}

void Error :: NotSupportErrot()
{
    if(argc < 3 || argc > 3 || !strcmp(argv[1],"-?")){
        std :: cout <<"hint: nweb Port-Number Top-Directory\t\t" << VERSION << "\n\n\tnweb is a small and very safe mini web server\n\tnweb only servers out file /web pages with extensions named below\n\tand only from the named directory or its sub-directories.\n\tThere is no fancy features = safe and secure.\n\n\tExample:newb 8181/home/nwebdir&\n\n\tOnly Supports:" << std :: endl;
    for(size_t i = 0; Extensions[i].ext != "0"; ++i)
        std :: cout << Extensions[i].ext;

        std :: cout << "\n\tNot Supported: URLs including\"..\",Java, Javascript, CGI\n \tNot Supported: directories //etc /bin/lib/tmp/usr/dev/sbin\n" << std :: endl;
        exit(0);
    }
}
void Error :: DirectoryError()
{
    if( !strncmp(argv[2],"/",2) || !strncmp(argv[2],"/etc",5) || !strncmp(argv[2],"/bin",5) || !strncmp(argv[2],"/lib",5) || !strncmp(argv[2], "/tmp",5) || !strncmp(argv[2],"/usr",5) || !strncmp(argv[2],"/dev",5) || !strncmp(argv[2], "/sbin",6)){
        std :: cout << "Error:Bad top directory" << argv[2] << std :: endl;
        exit(3);
    }
}
void Error :: ChangeDirectoryError()
{
    if(chdir(argv[2]) == -1){
        std :: cout << "ERROR can't Change to the directory " << argv[2] << std :: endl;
        exit(4);
    }
}
void HttpServer :: Logger(const int &type,string s1, string s2,int& socket_fd)
{
     int fd;
     string bufferlog;
     std :: ostringstream stringStream;


    switch(type){
        case ERROR:
                    stringStream << "ERROR: " << s1 << " " << s2 << " Errno = " << errno << " exiting " << "pid = " << getpid();
                    bufferlog = stringStream.str();
                    break;
        case FORBIDDEN:
        //<summary>int write(int s ,char* buf,int len)</summary>
        //<return>if it successeeds, the fuction returns the number of bytes.</return>
                    (void)write(socket_fd,Packets[403].c_str(),Packets[403].size());
                    stringStream <<  "FOBIDDEN: " + s1 + ":" + s2;
                    break;
        case NOTFOUND:
                    (void)write(socket_fd,Packets[404].c_str(),Packets[404].size());break;
                    stringStream << "NOT FOUND: " + s1 + ":" + s2;
                    break;
        case LOG:
                    stringStream << "INFO: " + s1 + ":" +s2;break;
    }
    //fill the bufferlog
    bufferlog = stringStream.str();

    if( (fd = open("nweb.log",O_CREAT | O_WRONLY | O_APPEND,0644)) >= 0){
        (void)write(fd,bufferlog.c_str(),bufferlog.size());
        (void)write(fd,"\n",1);
        (void)close(fd);
    }

    if(type == ERROR || type == NOTFOUND ||type == FORBIDDEN)
        exit(3);
}

void HttpServer :: Web(int fd, int hit)
{
    int j,file_fd, bufferlen;
    long i, ret, len;
    const char *fstr;
    static string  buffer;

    //*{ following is to convert the string to c-style string.

     char *copyBuffer = new char[buffer.length()+1];
     strcpy(copyBuffer,buffer.c_str());

    //*}

    // <summary> read from a file descriptor.</summary>
    // <name> ssize read(int fd, void *buf, size_t count)</name>
    // <para name = "fd"> file descriptor</para name>
    // <para name = "buf"> the buffer</para name>
    // <para name = "count"> count bytes from file descriptor.</para name>
    ret = read(fd, copyBuffer, BUFFSIZE);

    if( ret == 0 || ret == -1){ /*read failure stop now*/
        string tmp1 = "failed to read brower request";
        string tmp2 = "";
        Logger(FORBIDDEN, tmp1,tmp2,fd);
    }

    if( ret > 0 && ret < BUFFSIZE) /*return code is valid chars*/
        buffer[ret] = 0;
    else
        buffer[0] = 0;
    for( i = 0; i < ret; ++i){
        if( buffer[i] == '\r' || buffer[i] == '\n')
            buffer[i] = '*';
    }

    Logger(LOG,(string) "request", buffer, hit);

    if( buffer.compare(0,strlen("GET"),"GET") && buffer.compare(0,strlen("get"),"get")){
        Logger(FORBIDDEN, "Only simple GET operation supported", buffer, fd);
    }

    for( i = 4; i < BUFFSIZE; ++i){
        if(!buffer[i]){
            buffer[i] = 0;
            break;
        }
    }
    /*check for illegal parent directory use...*/
    for( j = 0; j < i - 1; ++j)
        if( buffer[j] == '.' && buffer[j + 1] == '.'){
            Logger(FORBIDDEN, "Parent directory(...) path names not supported", buffer, fd);
        }


    if( !(buffer.compare(0,strlen("GET /\0"),"GET /\0")) ||!(buffer.compare(0,strlen("get /\0"), "get /\0" ))){

        /* convert no filename to index file*/
       string IndexBuffer("GET/index.html");
       char tempBuffer[IndexBuffer.length()];
       (void) IndexBuffer.copy(tempBuffer,strlen("GET/index.html"),0);
       buffer = tempBuffer;

    }

    /* work out the file type and check we support it*/
    bufferlen = buffer.size();
    fstr = (char*)0;
    for( i = 0; Extensions[i].ext != "0"; ++i){
        len = Extensions[i].ext.length();

        string tempBuffer(&buffer[bufferlen - len]);
        if( !tempBuffer.compare(0,Extensions[i].ext.length(),Extensions[i].ext)){
            fstr = Extensions[i].filetype.c_str();
            break;
        }
    }

    if( fstr == 0)
        Logger(NOTFOUND, "file extension type not supported", buffer,fd);

    if( (file_fd = open(&buffer[5], O_RDONLY)) == -1){ /*open the file for reading*/
        Logger(NOTFOUND, "failed to open file", &buffer[5],fd);
    }

    Logger(LOG, "SEND", &buffer[5],hit);
    /*lseek to the file end to find the length*/
    len = (long)lseek(file_fd, (off_t)0, SEEK_END);
    /*lseek back to the file start ready for reading*/
    (void)lseek(file_fd, (off_t)0, SEEK_SET);

    std ::ostringstream stringStream;
    stringStream << "HTTP/1.1\t200\tOK\nServer:nweb/" << VERSION <<".0\nContent-Length: " << len << "\nConnection: close\nContent-Type:" << *fstr << "\n\n";
    Logger(LOG,"Header", buffer,hit);
    (void)write(fd, buffer.c_str(), buffer.size());



    while( (ret = read( file_fd, copyBuffer, BUFFSIZE)) > 0 ){
        (void)write(fd, buffer.c_str(), ret);
    }

    /*allow socket to drain before signaling the socket is closed*/
    sleep(1);
    close(fd);
    exit(1);

}
void HttpServer :: InsertPacket()
{
    Packets[403] = " 403 Forbidden\nConnect-Length: 185\nConnection:close\nContent-Type:\ttext/html\n\n<html><head>\n<title>403 Forbidden</title>\n</head><body>\n<h1>Forbidden</h1>\nThe requested URL, file type or operation is not allowed on  this simple static file webserver.\n</body></html>";
    Packets[404] = "HTTP/1.1 404 Not Found\nContent-Length: 136\nConnection:close\nConnext-Type:\ttet/html\n\n<html><head>\n<title>404\tNot Found</title>\n</head><body>\n<h1>Not Found</h1>\nThe requested URL was not found on this server.\n</body></html>\n";
}


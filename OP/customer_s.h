//
// Created by ヒヤシンス on 2023/11/13.
//

#ifndef OP_CUSTOMER_S_H
#define OP_CUSTOMER_S_H

#include<iostream>
#include<map>
#include<filesystem>
#include<ostream>
#include<fstream>
#include<string>
#include<sstream>

#include"customer.h"

//#include"customer.cpp"

using namespace std;

class customer_s {
public:
    //初始化
    bool init();

    //根据id查找用户
    bool find(const string &id);

    //添加用户
    bool add(customer cur);

    //保存用户信息
    bool save();

    //返回id对应的密码
    string get_password(const string &id);

    //获取用户
    customer &get_cus(const string &id);

    //打印用户信息
    void print();

    //删除用户信息
    bool cus_delete(const string &id);

    //修改账户名
    bool change_id(const string &id, const string &new_id);

private:
    //存放顾客信息
    map<string, customer> m;
};

#endif //OP_CUSTOMER_S_H

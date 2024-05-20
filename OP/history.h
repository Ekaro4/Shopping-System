//
// Created by ヒヤシンス on 2023/12/11.
//

#ifndef OP_HISTORY_H
#define OP_HISTORY_H

#include<vector>
#include<map>
#include<ctime>
#include<fstream>
#include<sstream>
#include <iostream>
#include <iomanip>
#include"commodity.h"

using namespace std;

class history {
public:
    //初始化
    bool init(const string &customer_id);

    //打印记录
    void print(const string &time_);

    //插入
    void insert(const string &time, vector<commodity> v);

    //保存
    void save();

    //更改csv文件中的一行
    void modifyCSVLine(const std::string &filename, const std::string &targetName, const std::string &newContent);

private:
    //历史记录
    map<string, vector<commodity>> m;
    //当前历史记录所属用户的用户名
    string name;
};


#endif //OP_HISTORY_H

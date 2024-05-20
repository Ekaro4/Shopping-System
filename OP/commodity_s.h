//
// Created by ヒヤシンス on 2023/11/13.
//

#ifndef OP_COMMODITY_S_H
#define OP_COMMODITY_S_H

#include<map>
#include<iostream>
#include<fstream>
#include<filesystem>
#include<ostream>
#include<string>
#include<sstream>

#include"commodity.h"

//#include"commodity.cpp"

using namespace std;

class commodity_s {
public:
    //打印商品信息
    void print ();

    //查找商品
    bool find(const string &id);

    //初始化 从文件读入商品信息
    bool init();

    //添加商品
    bool add(const commodity &cur);

    //保存商品信息
    bool save();

    //获取商品对象引用
    commodity &get_com(const string &id);

    //删除商品信息
    bool com_delete(const string &id);

    //修改商品ID
    bool change_id(const string& id,const string& new_id);

    //修改商品单价
    bool change_price(const string& id,double new_price);

    //修改商品库存
    bool change_number(const string&id ,int new_number);

    //关键词查找
    commodity & search_by_key(string& key);

    //求字符串最大匹配长度
    int longestCommonSubstring(string str1,string str2);
private:
    //存储商品信息
    map<string, commodity> m;

};

#endif //OP_COMMODITY_S_H

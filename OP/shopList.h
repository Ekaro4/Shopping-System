//
// Created by ヒヤシンス on 2023/11/25.
//

#ifndef OP_SHOPLIST_H
#define OP_SHOPLIST_H

#include"commodity_s.h"
#include<fstream>
#include<iostream>
#include<sstream>
#include<list>
#include<iterator>

using namespace std;

class shopList {
public:
    //添加商品
    void operator+(commodity &com);

    //查询购物车信息
    void print();

    //清空信息
    void clear();

    //查询商品
    bool find(const string &id);

    //获取
    commodity &get_com(const string &id);

    //删除
    void Delete(const string &id);

    //打折前总价
    double sum();

    //打折后价格
    double check_out_sum_price();

    //保存信息
    bool save(const string &customer_id);

    //加载购物车信息
    bool init(const string &customer_id);

    //购物车信息
    list<commodity> m;
    //选择结算的商品次序
    list<int> number;
private:

};


#endif //OP_SHOPLIST_H

//
// Created by ヒヤシンス on 2023/11/13.
//

#include "commodity.h"

//重载构造函数
commodity::commodity(const string &id, const double &price, const int &number) {
    this->id = id;
    this->price = price;
    this->number = number;
}

//重载相等运算符
bool commodity::operator==(const commodity &o) const {
    if (this->id == o.id) return true;
    return false;
}
//获取ID
string commodity::get_id() const{
    return this->id;
}
//获取单价
double commodity::get_price() const{
    return this->price;
}
//获取数量
int commodity::get_number() const{
    return this->number;
}
//修改单价
void commodity::change_price(double new_price) {
    this->price = new_price;
}
//修改数量
void commodity::change_number(int new_number) {
    this->number = new_number;
}
//商品售出
void commodity::sold(int out) {
    this->number -= out;
}


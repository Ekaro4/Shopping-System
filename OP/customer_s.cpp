//
// Created by ヒヤシンス on 2023/11/13.
//

#include "customer_s.h"

//初始化
bool customer_s::init() {
    this->m.clear();
    fstream in;
    in.open("../Information/customer.csv",ios::in);
    if (!in.is_open()) {
        cout << "打开用户信息失败" << endl;
        return false;
    } else {
        while (!in.eof()) {
            //存储用户信息
            string cur_id;
            string cur_password;
            double cur_money;
            //处理逗号分隔符
            string line;
            while (getline(in, line)) {
                istringstream temp(line);
                string token;
                getline(temp, token, ',');
                //id
                cur_id = token;
                getline(temp, token, ',');
                //密码
                cur_password = token;
                getline(temp, token, ',');
                //余额
                cur_money = stod(token);
                //创建临时对象
                customer cur_cus(cur_id, cur_password, cur_money);
                //添加失败
                if (!this->add(cur_cus)) {
                    return false;
                }
            }
        }
        //确认读取完毕
        if (in.eof()) {
            in.close();
            return true;
        }
            //未读取完毕
        else {
            cout << "用户信息未读取完毕!" << endl;
            return false;
        }
    }
}

//根据id查找用户
bool customer_s::find(const string &id) {
    if (m.find(id) == m.end()) {
        //没找到
        return false;
    } else return true;
}

//添加用户
bool customer_s::add(customer cur) {
    //存在同名用户
    if (m.find(cur.get_id()) != m.end()) {
        cout << "用户已存在!" << endl;
        return false;
    } else {
        //添加用户
        m.insert(pair<string, customer>(cur.get_id(), cur));
        return true;
    }
}

//保存用户信息
bool customer_s::save() {
    //输出流
    ofstream out("../Information/customer.csv",ios::out|ios::trunc);
    if (!out.is_open()) {
        //打开失败
        cout << "保存用户信息失败!" << endl;
        return false;
    }
    for (auto &it: m) {
        //输出用户信息
        out << it.second.get_id() << ',' << it.second.get_password() << ',' << it.second.get_money() << endl;
    }
    return true;
}

//获取用户对象密码
string customer_s::get_password(const string &id) {
    for (auto &it: m) {
        //查找对应用户
        if (it.second.get_id() == id) {
            return it.second.get_password();
        }
    }
    //返回空
    return "";
}

//获取用户对象引用
customer &customer_s::get_cus(const string &id) {
    if (this->find(id)) {
        //找到
        customer &temp = m.at(id);
        return temp;
    }
}

//打印用户信息
void customer_s::print() {
    cout << "当前用户信息如下:" << endl;
    for (auto &it: m) {
        cout << it.second.get_id() << " 密码:" << it.second.get_password() << " 余额:" << it.second.get_money() << endl;
    }
}

//删除用户信息
bool customer_s::cus_delete(const string &id) {
    if (!this->find(id)) {
        //没找到
        cout << "删除失败!" << endl;
        cout << "没有叫 " << id << " 的用户!" << endl;
        return false;
    } else {
        this->m.erase(id);
        cout << "删除成功!" << endl;
        return true;
    }
}

//修改账户名
bool customer_s::change_id(const string &id, const string &new_id) {
    if (this->m.find(id) == this->m.end()) {
        //没找到
        return false;
    } else {
        //创建临时变量
        customer temp(new_id, this->get_cus(id).get_password(), this->get_cus(id).get_money());
        //删除旧的
        this->m.erase(id);
        //插入新的
        this->m.insert(pair<string, customer>(new_id, temp));
        return true;
    }
}


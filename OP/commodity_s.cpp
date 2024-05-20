//
// Created by ヒヤシンス on 2023/11/13.
//

#include "commodity_s.h"

//打印商品信息
void commodity_s::print() {
    cout << "当前商品信息如下:" << endl;
    for (auto &it: m) {
        cout << it.second.get_id() << " 单价:" << it.second.get_price() << " 剩余数量:" << it.second.get_number()
             << endl;
    }
}

//根据id查找商品
bool commodity_s::find(const string &id) {
    if (m.find(id) == m.end()) {
        //没找到
        return false;
    } else {
        //找到
        return true;
    }
}

//添加商品
bool commodity_s::add(const commodity &cur) {
    //存在同名商品
    if (m.find(cur.get_id()) != m.end()) {
        cout << "添加失败" << endl;
        cout << "商品已存在" << endl;
        return false;
    } else {
        //添加商品
        m.insert(pair<string, commodity>(cur.get_id(), cur));
        return true;
    }
}

//初始化
bool commodity_s::init() {
    this->m.clear();
    //输入流变量
    fstream in;
    //打开文件
    in.open("../Information/commodity.csv", ios::in);
    //打开失败
    if (!in.is_open()) {
        cout << "打开商品信息失败" << endl;
        return false;
    }
        //打开成功
    else {
        //读到文件尾部结束
        while (!in.eof()) {
            //存储商品信息
            string cur_id;
            double cur_price;
            int cur_number;
            //处理逗号分隔符
            string line;
            while (getline(in, line)) {
                istringstream temp(line);
                string token;
                getline(temp, token, ',');
                //id
                cur_id = token;
                getline(temp, token, ',');
                //价格
                cur_price = stod(token);
                getline(temp, token, ',');
                //数量
                cur_number = stoi(token);
                //创建临时对象
                commodity cur_com(cur_id, cur_price, cur_number);
                //添加失败
                if (!this->add(cur_com)) {
                    return false;
                }
            }

        }
        //确认读取完毕
        if (in.eof()) {
            //关闭
            in.close();
            return true;
        } else {
            //未到末尾
            cout << "商品信息未读取完毕!" << endl;
            return false;
        }
    }
}

//保存商品信息
bool commodity_s::save() {
    //输出流
    ofstream out("../Information/commodity.csv", ios::out | ios::trunc);
    //打开失败
    if (!out.is_open()) {
        cout << "保存商品信息失败!" << endl;
        return false;
    }
    //进行保存
    for (auto &it: m) {
        //输出信息
        out << it.second.get_id() << ',' << it.second.get_price() << ',' << it.second.get_number() << endl;
    }
    return true;
}

//获取商品对象引用
commodity &commodity_s::get_com(const string &id) {
    if (this->find(id)) {
        //找到
        commodity &temp = m.at(id);
        return temp;
    }
}

//删除商品信息
bool commodity_s::com_delete(const string &id) {
    if (!this->find(id)) {
        //没找到
        cout << "删除失败!" << endl;
        cout << "没有 " << id << " 商品!" << endl;
        return false;
    } else {
        //找到
        //执行删除
        this->m.erase(id);
        cout << "删除成功!" << endl;
        return true;
    }
}

//修改单个商品价格
bool commodity_s::change_price(const string &id, const double new_price) {
    //修改价格
    this->get_com(id).change_price(new_price);
    return false;
}

//修改单个商品id
bool commodity_s::change_id(const string &id, const string &new_id) {
    if (!this->find(id)) {
        //没找到
        return false;
    } else {
        //创建临时变量
        commodity temp(new_id, this->get_com(id).get_price(), this->get_com(id).get_number());
        //删除旧的
        this->m.erase(id);
        //插入新的
        this->m.insert(pair<string, commodity>(new_id, temp));
        return true;
    }
}

//修改单个商品库存
bool commodity_s::change_number(const string &id, const int new_number) {
    this->get_com(id).change_number(new_number);
    return false;
}

//关键词查找
commodity &commodity_s::search_by_key(string &key) {
    string cur_id;
    //匹配度
    int max = 0;
    int temp;
    for (auto &cur: m) {
        temp = longestCommonSubstring(key, cur.second.get_id());
        if (temp >= max) {
            max = temp;
            cur_id = cur.second.get_id();
        }
    }
    //返回引用
    return this->get_com(cur_id);
}

//求字符串最大匹配长度
int commodity_s::longestCommonSubstring(string str1, string str2) {
    int m = str1.length();
    int n = str2.length();
    // 创建一个二维数组来存储最长匹配长度
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    int maxLength = 0; // 用于存储最大匹配长度
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                maxLength = max(maxLength, dp[i][j]);
            } else {
                dp[i][j] = 0;
            }
        }
    }
    return maxLength;
}
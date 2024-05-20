//
// Created by ヒヤシンス on 2023/11/13.
//

#ifndef OP_INFORMATION_H
#define OP_INFORMATION_H

#include"customer_s.h"
#include"commodity_s.h"
#include"shopList.h"
#include"history.h"
#include<iostream>
#include<cstdlib>
#include<ctime>


//#include"customer_s.cpp"
//#include"commodity_s.cpp"
//#include"admin.cpp"

using namespace std;

class Information {
public:
    //初始化
    bool Init();
    //主菜单
    void menu();
    //保存信息
    bool save();
    //用户登录
    int login();
    //用户注册
    bool sign();
    //退出登录
    bool log_out();
    //买商品
    void Buy();
    //用户菜单
    void cus_menu();
    //管理员菜单
    void admin_menu();
    //管理 用户个人信息
    void cus_inf_menu();
    //修改商品信息
    void com_inf_modify();
    //购物车菜单
    void shopListMenu();
    //优惠券相关的总价计算
    double coupon_check(double x);
    //优惠券发放
    void coupon_discount();
    //优惠码生成
    string generateCouponCode();
    //活动情况
    bool event_discount();
    //活动相关总价计算
    double event_check(double x);
    //结算完成改数量
    void checked();
    // 将时间点转换为本地时间结构
    string convertLocalTimeToBeijingTime();
private:
    commodity_s com_s;
    customer_s cus_s;
    shopList sL;
    //管理员账密
    string admin_id = "Hyacinth";
    string admin_password = "Samsara";
    //记录当前的账户名和账户类型
    int curr_user_type = -1;
    string curr_user_id = "null";
    //优惠券信息
    string coupon_id = "null";
    //活动信息
    string event = "null";
    //折扣信息
    double coupon_dis = 0.8;
    double event_dis = 1;
    history history;
};

#endif //OP_INFORMATION_H

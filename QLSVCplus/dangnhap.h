#ifndef DANGNHAP_H
#define DANGNHAP_H

#include <iostream>
#include <string>
using namespace std;

struct DANGNHAP {
    string MaSV;
    string MATKHAU;
};

// Khai báo hàm đăng nhập
bool dangNhap(DANGNHAP ds[], int soLuong, string& maSVDangNhap);

#endif

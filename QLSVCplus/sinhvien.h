#ifndef SINHVIEN_H
#define SINHVIEN_H

#include <iostream>
#include <string>
using namespace std;

struct SINHVIEN {
    string MaSV;
    string HoTenSV;
    string GioiTinh;
    int NamSinh;
    float TrungbinhHK;
};

// Khai báo hàm hiển thị thông tin sinh viên
void hienThiThongTin(const SINHVIEN& sv);

#endif

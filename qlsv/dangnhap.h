#ifndef DANGNHAP_H
#define DANGNHAP_H

#include "qlsv.h"

extern DANGNHAP dangNhapList[MAX_SINHVIEN];

// Hàm đọc thông tin đăng nhập
void docThongTinDangNhap();

// Hàm kiểm tra đăng nhập
int dangNhap();

#endif

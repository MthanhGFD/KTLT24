#ifndef MENU_H
#define MENU_H

#include "sinhvien.h"
#include "diemso.h"

// Khai báo hàm menu cho sinh viên
void menuSinhVien(SINHVIEN& sv, DIEMSO& diem);

// Khai báo hàm menu cho giảng viên với tham số mảng
void menuGiangVien(SINHVIEN ds[], DIEMSO diem[], int soLuong);


#endif // MENU_H

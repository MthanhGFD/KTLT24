#ifndef DIEMSO_H
#define DIEMSO_H

#include "sinhvien.h"
#include <iostream>
#include <string>
using namespace std;

struct DIEMSO {
    string MaSV;
    float KTLT;  // Điểm môn Kỹ thuật lập trình
    float MMT;   // Điểm môn Mạng máy tính
    float CTDL;  // Điểm môn Cấu trúc dữ liệu
};

// Hàm tính điểm trung bình học kỳ cho sinh viên
void tinhDiemTB(SINHVIEN& sv, DIEMSO& diem);

#endif

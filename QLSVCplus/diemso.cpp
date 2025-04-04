#include "diemso.h"
#include "sinhvien.h"
#include <iostream>
using namespace std;

// Hàm tính điểm trung bình học kỳ
void tinhDiemTB(SINHVIEN& sv, DIEMSO& diem) {
    sv.TrungbinhHK = (diem.KTLT * 4 + diem.MMT * 3 + diem.CTDL * 3) / 10.0;
}

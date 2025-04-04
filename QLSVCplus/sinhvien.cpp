#include "sinhvien.h"

// Hàm hiển thị thông tin sinh viên
void hienThiThongTin(const SINHVIEN& sv) {
    cout << "MaSV: " << sv.MaSV << endl;
    cout << "HoTen: " << sv.HoTenSV << endl;
    cout << "GioiTinh: " << sv.GioiTinh << endl;
    cout << "NamSinh: " << sv.NamSinh << endl;
    cout << "TrungBinhHK: " << sv.TrungbinhHK << endl;
}

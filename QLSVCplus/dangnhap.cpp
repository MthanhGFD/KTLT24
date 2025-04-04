#include "dangnhap.h"

// Hàm kiểm tra đăng nhập
bool dangNhap(DANGNHAP ds[], int soLuong, string& maSVDangNhap) {
    string maSV, matKhau;
    cout << "Nhap MaSV: ";
    cin >> maSV;
    cout << "Nhap Mat Khau: ";
    cin >> matKhau;

    // Kiểm tra thông tin trong danh sách tài khoản
    for (int i = 0; i < soLuong; i++) {
        if (ds[i].MaSV == maSV && ds[i].MATKHAU == matKhau) {
            maSVDangNhap = maSV; // Lưu lại mã số sinh viên đang đăng nhập
            return true;
        }
    }

    cout << "Dang nhap that bai!\n";
    return false;
}

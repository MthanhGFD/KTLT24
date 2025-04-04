#include "dangnhap.h"
#include "sinhvien.h"
#include "menu.h"
#include "diemso.h"
#include <iostream>
using namespace std;

int main() {
    // Tạo danh sách tài khoản
    DANGNHAP ds[] = {
        {"11377", "admin123"},  // Giảng viên
        {"22001", "pass1"},     // Sinh viên 1
        {"22002", "pass2"}      // Sinh viên 2
    };
    int soLuong = sizeof(ds) / sizeof(ds[0]);
    string maSVDangNhap;

    // Gọi hàm đăng nhập và kiểm tra
    if (dangNhap(ds, soLuong, maSVDangNhap)) {
        if (maSVDangNhap == "11377") {
            // Giảng viên
            cout << "Dang nhap thanh cong! Ban la Giang vien.\n";
            
            // Giả sử có một danh sách sinh viên mẫu
            SINHVIEN dsSinhVien[3] = {
                {"22001", "Nguyen Van A", "Nam", 2000, 0},
                {"22002", "Le Thi B", "Nu", 1999, 0},
                {"22003", "Tran Thi C", "Nu", 2001, 0}
            };
            DIEMSO diem[3] = {
                {"22001", 8.0, 7.0, 6.5},
                {"22002", 9.0, 8.5, 8.0},
                {"22003", 6.0, 7.5, 8.0}
            };

            // Tính điểm trung bình học kỳ cho tất cả sinh viên
            for (int i = 0; i < 3; ++i) {
                tinhDiemTB(dsSinhVien[i], diem[i]);
            }

            // Gọi menu giảng viên
            menuGiangVien(dsSinhVien, diem, 3);
        } else {
            // Sinh viên
            cout << "Dang nhap thanh cong! Ban la Sinh vien.\n";
            
            // Giả sử có thông tin sinh viên mẫu
            SINHVIEN sv = {"22001", "Nguyen Van A", "Nam", 2000, 0};
            DIEMSO diem = {"22001", 8.0, 7.0, 6.5};
            
            // Tính điểm trung bình học kỳ cho sinh viên
            tinhDiemTB(sv, diem);

            // Gọi menu sinh viên
            menuSinhVien(sv, diem);
        }
    } else {
        cout << "Dang nhap khong thanh cong.\n";
    }

    return 0;
}



























/*// Hàm menu cho sinh viên
void menuSinhVien(SINHVIEN& sv, DIEMSO& diem) {
    cout << "Chao mung " << sv.HoTenSV << " den voi he thong quan ly thong tin sinh vien.\n";
    cout << "Thong tin sinh vien:\n";
    hienThiThongTin(sv);  // Hiển thị thông tin sinh viên

    cout << "\nDanh sach diem so:\n";
    cout << "KTLT: " << diem.KTLT << endl;
    cout << "MMT: " << diem.MMT << endl;
    cout << "CTDL: " << diem.CTDL << endl;
    cout << "Diem TB HK: " << sv.TrungbinhHK << endl;
}


// Hàm menu cho giảng viên
void menuGiangVien(SINHVIEN ds[], DIEMSO diem[], int soLuong) {
    int luaChon;
    do {
        cout << "\nMenu Giang Vien:\n";
        cout << "1. Them sinh vien\n";
        cout << "2. Cap nhat thong tin sinh vien\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1:
                // Thêm sinh viên mới
                cout << "Chuc nang them sinh vien chua duoc thuc hien.\n";
                break;
            case 2:
                // Cập nhật thông tin sinh viên
                cout << "Chuc nang cap nhat thong tin sinh vien chua duoc thuc hien.\n";
                break;
            case 0:
                cout << "Thoat.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (luaChon != 0);
}*/
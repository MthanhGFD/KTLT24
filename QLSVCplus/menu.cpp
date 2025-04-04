#include "menu.h"
#include "sinhvien.h"
#include "diemso.h"
#include <iostream>
#include <string>
using namespace std;

// Hàm thêm sinh viên
void themSinhVien(SINHVIEN ds[], int& soLuong) {
    SINHVIEN svMoi;
    cout << "Nhap MaSV: ";
    cin >> svMoi.MaSV;
    cout << "Nhap HoTen: ";
    cin.ignore();  // Để xóa ký tự '\n' còn lại trong buffer
    getline(cin, svMoi.HoTenSV);
    cout << "Nhap GioiTinh: ";
    cin >> svMoi.GioiTinh;
    cout << "Nhap NamSinh: ";
    cin >> svMoi.NamSinh;

    // Thêm sinh viên mới vào danh sách
    ds[soLuong] = svMoi;
    soLuong++;  // Tăng số lượng sinh viên

    cout << "Them sinh vien thanh cong.\n";
}

// Hàm cập nhật thông tin sinh viên
void capNhatThongTin(SINHVIEN ds[], int soLuong) {
    string maSV;
    cout << "Nhap MaSV can cap nhat: ";
    cin >> maSV;

    // Tìm sinh viên theo MaSV
    for (int i = 0; i < soLuong; ++i) {
        if (ds[i].MaSV == maSV) {
            cout << "Sinh vien tim thay: " << ds[i].HoTenSV << endl;
            cout << "Nhap thong tin moi:\n";

            cout << "Nhap HoTen moi: ";
            cin.ignore();  // Để xóa ký tự '\n' còn lại trong buffer
            getline(cin, ds[i].HoTenSV);
            cout << "Nhap GioiTinh moi: ";
            cin >> ds[i].GioiTinh;
            cout << "Nhap NamSinh moi: ";
            cin >> ds[i].NamSinh;

            cout << "Cap nhat thong tin thanh cong.\n";
            return;
        }
    }

    cout << "Khong tim thay sinh vien co MaSV: " << maSV << endl;
}

// Hàm menu cho sinh viên
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

// Đảm bảo rằng tham số là mảng và tham số 'soLuong' là tham chiếu
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
                themSinhVien(ds, soLuong);
                break;
            case 2:
                // Cập nhật thông tin sinh viên
                capNhatThongTin(ds, soLuong);
                break;
            case 0:
                cout << "Thoat.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (luaChon != 0);
}
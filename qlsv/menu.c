#include "menu.h"
#include "sinhvien.h"
#include "diemso.h"
#include <stdio.h>
#include <stdlib.h>

extern SINHVIEN sinhVienList[MAX_SINHVIEN];
extern DIEMSO diemList[MAX_SINHVIEN];
extern int soLuongSinhVien;

void hienThiThongTinSinhVien(char* maSV) {
    for (int i = 0; i < soLuongSinhVien; i++) {
        if (strcmp(sinhVienList[i].MaSV, maSV) == 0) {
            printf("MaSV: %s\n", sinhVienList[i].MaSV);
            printf("Ho Ten: %s\n", sinhVienList[i].HoTenSV);
            printf("Gioi Tinh: %s\n", sinhVienList[i].GioiTinh);
            printf("Nam Sinh: %d\n", sinhVienList[i].NamSinh);
            printf("Trung Binh HK: %.2f\n", sinhVienList[i].TrungbinhHK);
            return;
        }
    }
    printf("Sinh vien khong ton tai.\n");
}

void hienThiDiemSoSinhVien(char* maSV) {
    for (int i = 0; i < soLuongSinhVien; i++) {
        if (strcmp(diemList[i].MaSV, maSV) == 0) {
            printf("MaSV: %s\n", diemList[i].MaSV);
            printf("KTLT: %.2f\n", diemList[i].KTLT);
            printf("MMT: %.2f\n", diemList[i].MMT);
            printf("CTDL: %.2f\n", diemList[i].CTDL);
            return;
        }
    }
    printf("Diem so cua sinh vien khong ton tai.\n");
}

void hienThiMenu(char* maSV) {
    int luaChon;

    // Hiển thị menu
    printf("\n1. Xem thong tin sinh vien\n");
    printf("2. Xem diem so sinh vien\n");
    printf("3. Thoat\n");

    printf("Chon chuc nang: ");
    scanf("%d", &luaChon);

    switch (luaChon) {
        case 1:
            hienThiThongTinSinhVien(maSV);  // Gọi hàm hiển thị thông tin sinh viên
            break;
        case 2:
            hienThiDiemSoSinhVien(maSV);    // Gọi hàm hiển thị điểm số sinh viên
            break;
        case 3:
            printf("Thoat chuong trinh.\n");
            exit(0);  // Thoát chương trình
        default:
            printf("Lua chon khong hop le.\n");
            break;
    }
}

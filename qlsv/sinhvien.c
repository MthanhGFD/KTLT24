#include "sinhvien.h"

SINHVIEN sinhVienList[MAX_SINHVIEN];
int soLuongSinhVien = 0;

void docThongTinSinhVien() {
    FILE *file = fopen("thongtinSV.txt", "r");
    if (!file) {
        printf("Khong the mo file thongtinSV.txt.\n");
        return;
    }

    while (fscanf(file, "%s %s %s %d", sinhVienList[soLuongSinhVien].MaSV, sinhVienList[soLuongSinhVien].HoTenSV,
            sinhVienList[soLuongSinhVien].GioiTinh, &sinhVienList[soLuongSinhVien].NamSinh) != EOF) {
        soLuongSinhVien++;
    }

    fclose(file);
}

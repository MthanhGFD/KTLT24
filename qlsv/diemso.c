#include "diemso.h"
#include "sinhvien.h"

DIEMSO diemList[MAX_SINHVIEN];

void docDiemSoSinhVien() {
    FILE *file = fopen("diemso.txt", "r");
    if (!file) {
        printf("Khong the mo file diemso.txt.\n");
        return;
    }

    while (fscanf(file, "%s %f %f %f", diemList[soLuongSinhVien].MaSV, &diemList[soLuongSinhVien].KTLT, 
            &diemList[soLuongSinhVien].MMT, &diemList[soLuongSinhVien].CTDL) != EOF) {
        // Tìm sinh viên theo MaSV và tính điểm trung bình
        for (int i = 0; i < soLuongSinhVien; ++i) {
            if (strcmp(sinhVienList[i].MaSV, diemList[soLuongSinhVien].MaSV) == 0) {
                sinhVienList[i].TrungbinhHK = (diemList[soLuongSinhVien].KTLT * 4 + diemList[soLuongSinhVien].MMT * 3 + diemList[soLuongSinhVien].CTDL * 3) / 10;
                break;
            }
        }
    }

    fclose(file);
}

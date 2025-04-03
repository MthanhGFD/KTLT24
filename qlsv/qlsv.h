#ifndef QLSV_H
#define QLSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SINHVIEN 100

typedef struct {
    char MaSV[20];
    char HoTenSV[50];
    char GioiTinh[10];
    int NamSinh;
    float TrungbinhHK;
} SINHVIEN;

typedef struct {
    char MaSV[20];
    float KTLT, MMT, CTDL;
} DIEMSO;

typedef struct {
    char MaSV[20];
    char MATKHAU[20];
} DANGNHAP;

// Hàm đọc dữ liệu từ file
void docThongTinSinhVien();
void docDiemSoSinhVien();
void docThongTinDangNhap();

// Hàm đăng nhập
int dangNhap();

// Hàm tính điểm trung bình học kỳ
void tinhDiemTrungBinh();

#endif

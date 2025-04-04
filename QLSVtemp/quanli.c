#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100

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

DANGNHAP dangNhapList[MAX];
SINHVIEN sinhVienList[MAX];
DIEMSO diemList[MAX];
int soLuongSinhVien = 0;
int soLuongDiem = 0;
int soLuongTaiKhoan = 0;

// Hàm đọc dữ liệu từ file
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

void docDiemSoSinhVien() {
    FILE *file = fopen("diemso.txt", "r");
    if (!file) {
        printf("Khong the mo file diemso.txt.\n");
        return;
    }

    while (fscanf(file, "%s %f %f %f", diemList[soLuongDiem].MaSV, 
        &diemList[soLuongDiem].KTLT, 
        &diemList[soLuongDiem].MMT, 
        &diemList[soLuongDiem].CTDL) != EOF) {
        // Tìm sinh viên theo MaSV và tính điểm trung bình
        for (int i = 0; i < soLuongSinhVien; ++i) {
            if (strcmp(sinhVienList[i].MaSV, diemList[soLuongDiem].MaSV) == 0) {
                sinhVienList[i].TrungbinhHK = (diemList[soLuongDiem].KTLT * 4 + 
                                                diemList[soLuongDiem].MMT * 3 + 
                                                diemList[soLuongDiem].CTDL * 3) / 10;
                break;
            }
        }
        soLuongDiem++;
    }

    fclose(file);
}

// Hàm đăng nhập
void docThongTinDangNhap() {
    FILE *file = fopen("dangnhap.txt", "r");
    if (!file) {
        printf("Khong the mo file dangnhap.txt.\n");
        return;
    }

    while (fscanf(file, "%s %s", dangNhapList[soLuongTaiKhoan].MaSV, dangNhapList[soLuongTaiKhoan].MATKHAU) != EOF) {
        soLuongTaiKhoan++;
    }

    fclose(file);
}

bool dangNhap(char *maSVDangNhap) {
    char MaSV[20], MatKhau[20];
    int soLanSai = 0;
    bool isLoggedIn = false;

    printf("Nhap MaSV: ");
    scanf("%s", MaSV);
    
    while (soLanSai < 5) {
        printf("Nhap MatKhau: ");
        scanf("%s", MatKhau);
        
        for (int i = 0; i < soLuongTaiKhoan; i++) {
            if (strcmp(dangNhapList[i].MaSV, MaSV) == 0 && 
                strcmp(dangNhapList[i].MATKHAU, MatKhau) == 0) {
                isLoggedIn = true;
                strcpy(maSVDangNhap, MaSV); // Gán mã sinh viên ra ngoài
                break;
            }
        }        

        if (isLoggedIn) {
            printf("Dang nhap thanh cong.\n");
            return true;
        } else {
            soLanSai++;
            printf("Sai MaSV hoac MatKhau. Ban con %d lan thu lai.\n", 5 - soLanSai);
        }
    }

    printf("Dang nhap khong thanh cong. Thoat chuong trinh.\n");
    return false;
}


// Hàm tính điểm trung bình học kỳ
void tinhDiemTrungBinh();

//Menu
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
    for (int i = 0; i < soLuongDiem; i++) {
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

void hienThiMenu(char *maSV) {
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

//CHẠY CHƯƠNG TRÌNH:
int main() {
    char MaSV[20];

    // Đọc dữ liệu từ các file
    docThongTinSinhVien();
    docDiemSoSinhVien();
    docThongTinDangNhap();

    // Đăng nhập
    if (dangNhap(MaSV)) {
        hienThiMenu(MaSV); // Tiến hành các chức năng menu sinh viên/giảng viên
    } else {
        
    }

    return 0;
}
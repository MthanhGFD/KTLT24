#include "dangnhap.h"

DANGNHAP dangNhapList[MAX_SINHVIEN];

void docThongTinDangNhap() {
    FILE *file = fopen("dangnhap.txt", "r");
    if (!file) {
        printf("Khong the mo file dangnhap.txt.\n");
        return;
    }

    int i = 0;
    while (fscanf(file, "%s %s", dangNhapList[i].MaSV, dangNhapList[i].MATKHAU) != EOF) {
        i++;
    }

    fclose(file);
}

int dangNhap() {
    char MaSV[20], MatKhau[20];
    int soLanSai = 0;
    int isLoggedIn = 0;

    printf("Nhap MaSV: ");
    scanf("%s", MaSV);
    printf("Nhap MatKhau: ");
    scanf("%s", MatKhau);

    // Kiểm tra đăng nhập
    while (soLanSai < 5) {
        for (int i = 0; i < MAX_SINHVIEN; i++) {
            /*printf("Checking: %s %s vs %s %s\n", dangNhapList[i].MaSV, dangNhapList[i].MATKHAU, MaSV, MatKhau);*/
            if (strcmp(dangNhapList[i].MaSV, MaSV) == 0 && strcmp(dangNhapList[i].MATKHAU, MatKhau) == 0) {
                isLoggedIn = 1;
                break;
            }
        }

        if (isLoggedIn) {
            return 1; // Đăng nhập thành công
        } else {
            soLanSai++;
            printf("Sai MaSV hoac MatKhau. Thao tac thu %d/5.\n", soLanSai);
            if (soLanSai < 5) {
                printf("Nhap lai MaSV: ");
                scanf("%s", MaSV);
                printf("Nhap lai MatKhau: ");
                scanf("%s", MatKhau);
            }
        }
    }

    return 0; // Thoát nếu sai quá 5 lần
}

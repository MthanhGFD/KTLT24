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
    FILE *file = fopen("C:/Users/admin/Desktop/KTLT24/QLSVtemp/thongtinSV.txt", "r");
    if (!file) {
        printf("Khong the mo file thongtinSV.txt.\n");
        return;
    }

    while (fscanf(file, "%s %s %d %[^\n]", sinhVienList[soLuongSinhVien].MaSV,
        sinhVienList[soLuongSinhVien].GioiTinh,
        &sinhVienList[soLuongSinhVien].NamSinh,
        sinhVienList[soLuongSinhVien].HoTenSV) != EOF) {
    soLuongSinhVien++; // Đọc và lưu lại mảng
}
    fclose(file);
}

// Hàm tính điểm trung bình học kỳ cho sinh viên
void tinhDiemTrungBinh(SINHVIEN *sinhVien, DIEMSO diem) {
    sinhVien->TrungbinhHK = (diem.KTLT * 4 + diem.MMT * 3 + diem.CTDL * 3) / 10;
}

void docDiemSoSinhVien() {
    FILE *file = fopen("C:/Users/admin/Desktop/KTLT24/QLSVtemp/diemso.txt", "r");
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
                // Tính điểm trung bình
                tinhDiemTrungBinh(&sinhVienList[i], diemList[soLuongDiem]);
                break;
            }
        }
        soLuongDiem++;
    }

    fclose(file);
}

// Hàm đăng nhập
void docThongTinDangNhap() {
    FILE *file = fopen("C:/Users/admin/Desktop/KTLT24/QLSVtemp/dangnhap.txt", "r");
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
    bool MaSVTonTai = false;

    while (1) {
        printf("Nhap MaSV ('exit' de thoat): ");
        scanf("%s", MaSV);

        // Kiểm tra nếu người dùng muốn thoát
        if (strcmp(MaSV, "exit") == 0) {
            printf("Thoat chuong trinh.\n");
            exit(0);
        }

        // Kiểm tra xem mã sinh viên có tồn tại trong danh sách tài khoản không
        MaSVTonTai = false;
        for (int i = 0; i < soLuongTaiKhoan; i++) {
            if (strcmp(dangNhapList[i].MaSV, MaSV) == 0) {
                MaSVTonTai = true;
                break;
            }
        }

        // Nếu mã sinh viên không tồn tại
        if (!MaSVTonTai) {
            printf("MaSV khong ton tai. Vui long nhap lai.\n");
            continue;
        }

        // Nếu mã sinh viên tồn tại
        while (soLanSai < 5) {
            printf("Nhap mat khau: ");
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
                printf("Sai mat khau. Ban con %d lan thu lai.\n", 5 - soLanSai);
            }
        }

        printf("Dang nhap khong thanh cong. Thoat chuong trinh.\n");
        return false;
    }
}

void xoaSinhVien() {
    char MaSV[20];
    printf("Nhap ma sinh vien can xoa: ");
    scanf("%s", MaSV);

    int found = 0;
    for (int i = 0; i < soLuongSinhVien; i++) {
        if (strcmp(sinhVienList[i].MaSV, MaSV) == 0) {
            found = 1;
            // Xóa sinh viên bằng cách dịch chuyển các sinh viên còn lại
            for (int j = i; j < soLuongSinhVien - 1; j++) {
                sinhVienList[j] = sinhVienList[j + 1];
            }
            soLuongSinhVien--;
            break;
        }
    }

    if (found) {
        // Lưu lại danh sách sinh viên vào file sau khi xóa
        FILE *file = fopen("thongtinSV.txt", "w");
        if (file) {
            for (int i = 0; i < soLuongSinhVien; i++) {
                fprintf(file, "%s %s %d %s\n", sinhVienList[i].MaSV, sinhVienList[i].GioiTinh,
                        sinhVienList[i].NamSinh, sinhVienList[i].HoTenSV);
            }
            fclose(file);
            printf("Sinh vien da duoc xoa thanh cong!\n");
        } else {
            printf("Loi khi luu du lieu sau khi xoa sinh vien.\n");
        }
    } else {
        printf("Sinh vien voi ma %s khong ton tai.\n", MaSV);
    }
}

void hienKhongCanhBao() {
    printf("Danh sach sinh vien khong bi canh bao:\n");

    int found = 0;
    for (int i = 0; i < soLuongSinhVien; i++) {
        if (sinhVienList[i].TrungbinhHK >= 4.0) {
            found = 1;
            printf("MaSV: %s, Ho Ten: %s, Trung Binh HK: %.2f\n", sinhVienList[i].MaSV,
                   sinhVienList[i].HoTenSV, sinhVienList[i].TrungbinhHK);
        }
    }

    if (!found) {
        printf("Khong co sinh vien nao thoa man dieu kien.\n");
    }
}

void xuatDanhSachSinhVien() {
    FILE *file = fopen("C:/Users/admin/Desktop/KTLT24/QLSVtemp/thongtinSV_export.txt", "w");
    if (file) {
        for (int i = 0; i < soLuongSinhVien; i++) {
            fprintf(file, "%s %s %d %s %.2f\n", sinhVienList[i].MaSV, sinhVienList[i].GioiTinh,
                    sinhVienList[i].NamSinh, sinhVienList[i].HoTenSV, sinhVienList[i].TrungbinhHK);
        }
        fclose(file);
        printf("Danh sach sinh vien da duoc xuat ra.\n");
    } else {
        printf("Loi khi xuat danh sach sinh vien ra file.\n");
    }
}

// Hàm tìm kiếm sinh viên theo mã sinh viên
void timKiemSinhVien() {
    char MaSV[20];
    printf("Nhap MaSV cua sinh vien can tim: ");
    scanf("%s", MaSV);

    int found = 0;
    for (int i = 0; i < soLuongSinhVien; i++) {
        if (strcmp(sinhVienList[i].MaSV, MaSV) == 0) {
            found = 1;
            printf("Thong tin sinh vien tim duoc:\n");
            printf("MaSV: %s\n", sinhVienList[i].MaSV);
            printf("Ho Ten: %s\n", sinhVienList[i].HoTenSV);
            printf("Gioi Tinh: %s\n", sinhVienList[i].GioiTinh);
            printf("Nam Sinh: %d\n", sinhVienList[i].NamSinh);
            printf("Trung Binh HK: %.2f\n", sinhVienList[i].TrungbinhHK);
            break;
        }
    }

    if (!found) {
        printf("Sinh vien voi MaSV %s khong ton tai.\n", MaSV);
    }
}

//Menu
void hienThiThongTinSinhVien(char* maSV) {
    for (int i = 0; i < soLuongSinhVien; i++) {
        if (strcmp(sinhVienList[i].MaSV, maSV) == 0) {
            printf("\nMaSV: %s\n", sinhVienList[i].MaSV);
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
            printf("\nMaSV: %s\n", diemList[i].MaSV);
            printf("KTLT: %.2f\n", diemList[i].KTLT);
            printf("MMT: %.2f\n", diemList[i].MMT);
            printf("CTDL: %.2f\n", diemList[i].CTDL);
            return;
        }
    }
    printf("Diem so cua sinh vien khong ton tai.\n");
}

void themSinhVien() {
    SINHVIEN sinhVienMoi;

    printf("Nhap MaSV: ");
    scanf("%s", sinhVienMoi.MaSV);
    printf("Nhap Ho Ten: ");
    scanf(" %[^\n]", sinhVienMoi.HoTenSV); // Đọc chuỗi có khoảng trắng
    printf("Nhap Gioi Tinh: ");
    scanf("%s", sinhVienMoi.GioiTinh);
    printf("Nhap Nam Sinh: ");
    scanf("%d", &sinhVienMoi.NamSinh);

    // Tính điểm trung bình học kỳ
    sinhVienMoi.TrungbinhHK = 0.0;

    // Thêm sinh viên vào danh sách
    sinhVienList[soLuongSinhVien] = sinhVienMoi;
    soLuongSinhVien++;

    // Lưu lại vào file "thongtinSV.txt"
    FILE *file = fopen("C:/Users/admin/Desktop/KTLT24/QLSVtemp/thongtinSV.txt", "a");
    if (file) {
        fprintf(file, "%s %s %d %s\n", sinhVienMoi.MaSV, sinhVienMoi.GioiTinh,
                sinhVienMoi.NamSinh, sinhVienMoi.HoTenSV);
        fclose(file);
        printf("Sinh vien da duoc them thanh cong!\n");
    } else {
        printf("Loi khi luu du lieu sinh vien.\n");
    }

    // Tạo tài khoản cho sinh viên mới
    DANGNHAP taiKhoanMoi;
    strcpy(taiKhoanMoi.MaSV, sinhVienMoi.MaSV);
    // Mật khẩu mặc định: "123456"
    strcpy(taiKhoanMoi.MATKHAU, "123456");

    // Lưu tài khoản vào file "dangnhap.txt"
    file = fopen("C:/Users/admin/Desktop/KTLT24/QLSVtemp/dangnhap.txt", "a");
    if (file) {
        fprintf(file, "\n%s %s\n", taiKhoanMoi.MaSV, taiKhoanMoi.MATKHAU);
        fclose(file);
        printf("Tai khoan sinh vien da duoc tao thanh cong\n");
    } else {
        printf("Loi khi luu du lieu tai khoan.\n");
    }
}

void capNhatThongTin() {
    char MaSV[20];
    printf("Nhap MaSV cua sinh vien can cap nhat: ");
    scanf("%s", MaSV);

    // Tìm sinh viên trong danh sách
    int found = 0;
    for (int i = 0; i < soLuongSinhVien; i++) {
        if (strcmp(sinhVienList[i].MaSV, MaSV) == 0) {
            found = 1;

            // Cập nhật thông tin sinh viên
            printf("Nhap Ho Ten moi: ");
            scanf(" %[^\n]", sinhVienList[i].HoTenSV);
            printf("Nhap Gioi Tinh moi: ");
            scanf("%s", sinhVienList[i].GioiTinh);
            printf("Nhap Nam Sinh moi: ");
            scanf("%d", &sinhVienList[i].NamSinh);

            // Tính lại điểm trung bình học kỳ
            sinhVienList[i].TrungbinhHK = 0.0;

            // Lưu lại vào file "thongtinSV.txt" sau khi cập nhật
            FILE *file = fopen("thongtinSV.txt", "w");
            if (file) {
                for (int j = 0; j < soLuongSinhVien; j++) {
                    fprintf(file, "%s %s %d %s\n", sinhVienList[j].MaSV, sinhVienList[j].GioiTinh,
                            sinhVienList[j].NamSinh, sinhVienList[j].HoTenSV);
                }
                fclose(file);
                printf("Thong tin sinh vien da duoc cap nhat.\n");
            } else {
                printf("Loi khi cap nhat thong tin sinh vien.\n");
            }

            break;
        }
    }

    if (!found) {
        printf("Sinh vien voi MaSV %s khong ton tai.\n", MaSV);
    }
}

void doiMatKhau(char *maSV) {
    char matKhauCu[20], matKhauMoi[20], matKhauXacNhan[20];
    int found = 0;

    // Tìm tài khoản trong danh sách
    for (int i = 0; i < soLuongTaiKhoan; i++) {
        if (strcmp(dangNhapList[i].MaSV, maSV) == 0) {
            found = 1;
            printf("Nhap mat khau cu: ");
            scanf("%s", matKhauCu);

            // Kiểm tra mật khẩu cũ
            if (strcmp(dangNhapList[i].MATKHAU, matKhauCu) != 0) {
                printf("Mat khau cu khong chinh xac!\n");
                return;
            }

            // Nhập mật khẩu mới
            printf("Nhap mat khau moi: ");
            scanf("%s", matKhauMoi);
            printf("Xac nhan mat khau moi: ");
            scanf("%s", matKhauXacNhan);

            if (strcmp(matKhauMoi, matKhauXacNhan) != 0) {
                printf("Mat khau moi khong khop. Vui long thu lai!\n");
                return;
            }

            strcpy(dangNhapList[i].MATKHAU, matKhauMoi);
            printf("Doi mat khau thanh cong!\n");

            // Ghi lại danh sách vào file
            FILE *file = fopen("C:/Users/admin/Desktop/KTLT24/QLSVtemp/dangnhap.txt", "w");
            if (file) {
                for (int j = 0; j < soLuongTaiKhoan; j++) {
                    fprintf(file, "%s %s\n", dangNhapList[j].MaSV, dangNhapList[j].MATKHAU);
                }
                fclose(file);
                printf("Mat khau da duoc cap nhat.\n");
            } else {
                printf("Loi.\n");
            }

            return;
        }
    }

    if (!found) {
        printf("Tai khoan khong ton tai!\n");
    }
}

void hienThiMenu(char *maSV) {
    int luaChon;

    while (1) {
        // Nếu là giảng viên (MaSV == 11377), hiển thị menu giảng viên
        if (strcmp(maSV, "11377") == 0) {
            printf("\n1. Them sinh vien\n");
            printf("2. Cap nhat thong tin sinh vien\n");
            printf("3. Xoa sinh vien\n");
            printf("4. Tim kiem sinh vien\n");
            printf("5. Hien thi danh sach sinh vien khong canh bao\n");
            printf("6. Xuat danh sach sinh vien ra file\n");
            printf("7. Thoat\n");
            printf("Chon chuc nang: ");
            scanf("%d", &luaChon);

            switch (luaChon) {
                case 1:
                    themSinhVien();
                    break;
                case 2:
                    capNhatThongTin();
                    break;
                case 3:
                    xoaSinhVien();
                    break;
                case 4:
                    timKiemSinhVien();
                    break;
                case 5:
                    hienKhongCanhBao();
                    break;
                case 6:
                    xuatDanhSachSinhVien();
                    break;
                case 7:
                    printf("Thoat chuong trinh.\n");
                    return; // Thoát khỏi menu
                default:
                    printf("Lua chon khong hop le.\n");
                    break;
            }
        } else {
            printf("\n1. Xem thong tin sinh vien\n");
            printf("2. Xem diem so sinh vien\n");
            printf("3. Doi mat khau\n");
            printf("4. Thoat\n");

            printf("Chon chuc nang: ");
            scanf("%d", &luaChon);

            switch (luaChon) {
                case 1:
                    hienThiThongTinSinhVien(maSV);
                    break;
                case 2:
                    hienThiDiemSoSinhVien(maSV);
                    break;
                case 3:
                    doiMatKhau(maSV);
                    break;
                case 4:
                    printf("Thoat chuong trinh.\n");
                    return;
                default:
                    printf("Lua chon khong hop le.\n");
                    break;
            }
        }
    }
}

//CHẠY CHƯƠNG TRÌNH:
int main() {
    char MaSV[20];

    // Đọc dữ liệu từ các file
    docThongTinSinhVien();
    docDiemSoSinhVien();
    docThongTinDangNhap();
    while(1){
    // Đăng nhập
        if (dangNhap(MaSV)) {
            hienThiMenu(MaSV); // Sau khi xong menu, quay lại màn hình đăng nhập
        } else {
            break; // Nếu đăng nhập sai 5 lần → thoát chương trình
        }
    }
    return 0;
}
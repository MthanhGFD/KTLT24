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

    while (fscanf(file, "%s %s %d %[^\n]", sinhVienList[soLuongSinhVien].MaSV,
        sinhVienList[soLuongSinhVien].GioiTinh,
        &sinhVienList[soLuongSinhVien].NamSinh,
        sinhVienList[soLuongSinhVien].HoTenSV) != EOF) {
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
    bool isMaSVExist = false;

    while (1) {
        printf("Nhap MaSV (hoac 'exit' de thoat): ");
        scanf("%s", MaSV);

        // Kiểm tra nếu người dùng muốn thoát
        if (strcmp(MaSV, "exit") == 0) {
            printf("Thoat chuong trinh.\n");
            exit(0); // Thoát chương trình ngay lập tức
        }

        // Kiểm tra xem mã sinh viên có tồn tại trong danh sách tài khoản không
        isMaSVExist = false; // Reset lại trạng thái
        for (int i = 0; i < soLuongTaiKhoan; i++) {
            if (strcmp(dangNhapList[i].MaSV, MaSV) == 0) {
                isMaSVExist = true;
                break;
            }
        }

        // Nếu mã sinh viên không tồn tại, yêu cầu nhập lại
        if (!isMaSVExist) {
            printf("MaSV khong ton tai. Vui long nhap lai hoac nhap 'exit' de thoat.\n");
            continue; // Quay lại vòng lặp để nhập lại mã sinh viên
        }

        // Nếu mã sinh viên tồn tại, yêu cầu nhập mật khẩu
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
                printf("Sai MatKhau. Ban con %d lan thu lai.\n", 5 - soLanSai);
            }
        }

        printf("Dang nhap khong thanh cong. Thoat chuong trinh.\n");
        return false;
    }
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

    // Tính điểm trung bình học kỳ (vì chưa có điểm số, tạm để 0.0)
    sinhVienMoi.TrungbinhHK = 0.0;

    // Thêm sinh viên vào danh sách
    sinhVienList[soLuongSinhVien] = sinhVienMoi;
    soLuongSinhVien++;

    // Lưu lại vào file "thongtinSV.txt"
    FILE *file = fopen("thongtinSV.txt", "a");
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
    // Mật khẩu mặc định cho sinh viên mới là "123456" (hoặc bạn có thể cho phép nhập mật khẩu)
    strcpy(taiKhoanMoi.MATKHAU, "123456");

    // Lưu tài khoản vào file "dangnhap.txt"
    file = fopen("dangnhap.txt", "a");
    if (file) {
        fprintf(file, "%s %s\n", taiKhoanMoi.MaSV, taiKhoanMoi.MATKHAU);
        fclose(file);
        printf("Tai khoan sinh vien da duoc tao thanh cong!\n");
    } else {
        printf("Loi khi luu du lieu tai khoan.\n");
    }
}

void capNhatThongTinSinhVien() {
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

            // Tính lại điểm trung bình học kỳ (vì có thể có thay đổi về điểm số)
            sinhVienList[i].TrungbinhHK = 0.0;  // Tạm thời để 0.0 hoặc tính lại từ điểm số

            // Lưu lại vào file "thongtinSV.txt" sau khi cập nhật
            FILE *file = fopen("thongtinSV.txt", "w");
            if (file) {
                for (int j = 0; j < soLuongSinhVien; j++) {
                    fprintf(file, "%s %s %d %s\n", sinhVienList[j].MaSV, sinhVienList[j].GioiTinh,
                            sinhVienList[j].NamSinh, sinhVienList[j].HoTenSV);
                }
                fclose(file);
                printf("Thong tin sinh vien da duoc cap nhat!\n");
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

void hienThiMenu(char *maSV) {
    int luaChon;

    while(1) {
        // Nếu là giảng viên (MaSV == 11377), hiển thị menu giảng viên
        if (strcmp(maSV, "11377") == 0) {
            printf("\n1. Them sinh vien\n");
            printf("2. Cap nhat thong tin sinh vien\n");
            printf("3. Thoat\n");
            printf("Chon chuc nang: ");
            scanf("%d", &luaChon);

            switch (luaChon) {
                case 1:
                    themSinhVien();  // Gọi hàm thêm sinh viên
                    break;
                case 2:
                    capNhatThongTinSinhVien();  // Gọi hàm cập nhật thông tin sinh viên
                    break;
                case 3:
                    printf("Thoat chuong trinh.\n");
                    return; // Thoát khỏi menu
                default:
                    printf("Lua chon khong hop le.\n");
                    break;
            }
        } else {
            // Nếu là sinh viên, chỉ hiển thị các chức năng của sinh viên
            printf("\n1. Xem thong tin sinh vien\n");
            printf("2. Xem diem so sinh vien\n");
            printf("3. Thoat\n");

            printf("Chon chuc nang: ");
            scanf("%d", &luaChon);

            switch (luaChon) {
                case 1:
                    hienThiThongTinSinhVien(maSV);  // Hiển thị thông tin sinh viên
                    break;
                case 2:
                    hienThiDiemSoSinhVien(maSV);    // Hiển thị điểm số sinh viên
                    break;
                case 3:
                    printf("Thoat chuong trinh.\n");
                    return; // Thoát khỏi chương trình
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
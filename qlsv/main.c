#include "qlsv.h"
#include "sinhvien.h"
#include "diemso.h"
#include "dangnhap.h"
#include "menu.h"

int main() {
    // Đọc dữ liệu từ các file
    docThongTinSinhVien();
    docDiemSoSinhVien();
    docThongTinDangNhap();

    // Đăng nhập
    if (dangNhap()) {
        printf("Dang nhap thanh cong!\n");

        // Tiến hành các chức năng menu sinh viên/giảng viên
        hienThiMenu();
    } else {
        printf("Dang nhap khong thanh cong. Thoat chuong trinh.\n");
    }

    return 0;
}

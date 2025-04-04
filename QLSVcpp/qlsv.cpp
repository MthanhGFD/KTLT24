#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

#define MAX 100

using namespace std;

struct SINHVIEN {
    string MaSV;
    string HoTenSV;
    string GioiTinh;
    int NamSinh;
    float TrungbinhHK;
};

struct DIEMSO {
    string MaSV;
    float KTLT, MMT, CTDL;
};

struct DANGNHAP {
    string MaSV;
    string MATKHAU;
};

DANGNHAP dangNhapList[MAX];
SINHVIEN sinhVienList[MAX];
DIEMSO diemList[MAX];
int soLuongSinhVien = 0;
int soLuongDiem = 0;

// Hàm trim để loại bỏ khoảng trắng dư thừa
string trim(const string &str) {
    size_t first = str.find_first_not_of(" \t");
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

void docThongTinSinhVien() {
    ifstream file("thongtinSV.txt");
    if (!file) {
        cout << "Khong the mo file thongtinSV.txt." << endl;
        return;
    }

    while (file >> sinhVienList[soLuongSinhVien].MaSV 
                >> sinhVienList[soLuongSinhVien].HoTenSV
                >> sinhVienList[soLuongSinhVien].GioiTinh 
                >> sinhVienList[soLuongSinhVien].NamSinh) {
        sinhVienList[soLuongSinhVien].MaSV = trim(sinhVienList[soLuongSinhVien].MaSV);
        sinhVienList[soLuongSinhVien].HoTenSV = trim(sinhVienList[soLuongSinhVien].HoTenSV);
        sinhVienList[soLuongSinhVien].GioiTinh = trim(sinhVienList[soLuongSinhVien].GioiTinh);
        soLuongSinhVien++;
    }

    file.close();
}

void docDiemSoSinhVien() {
    ifstream file("diemso.txt");
    if (!file) {
        cout << "Khong the mo file diemso.txt." << endl;
        return;
    }

    while (file >> diemList[soLuongDiem].MaSV 
                >> diemList[soLuongDiem].KTLT
                >> diemList[soLuongDiem].MMT
                >> diemList[soLuongDiem].CTDL) {
        diemList[soLuongDiem].MaSV = trim(diemList[soLuongDiem].MaSV);
        for (int i = 0; i < soLuongSinhVien; ++i) {
            if (sinhVienList[i].MaSV == diemList[soLuongDiem].MaSV) {
                sinhVienList[i].TrungbinhHK = (diemList[soLuongDiem].KTLT * 4 + 
                                                diemList[soLuongDiem].MMT * 3 + 
                                                diemList[soLuongDiem].CTDL * 3) / 10;
                break;
            }
        }
        soLuongDiem++;
    }

    file.close();
}

void docThongTinDangNhap() {
    ifstream file("dangnhap.txt");
    if (!file) {
        cout << "Khong the mo file dangnhap.txt." << endl;
        return;
    }

    int i = 0;
    while (file >> dangNhapList[i].MaSV >> dangNhapList[i].MATKHAU) {
        dangNhapList[i].MaSV = trim(dangNhapList[i].MaSV);
        dangNhapList[i].MATKHAU = trim(dangNhapList[i].MATKHAU);
        i++;
    }

    file.close();
}

bool dangNhap() {
    string MaSV, MatKhau;
    int soLanSai = 0;
    bool isLoggedIn = false;

    cout << "Nhap MaSV: ";
    cin >> MaSV;

    MaSV = trim(MaSV);

    while (soLanSai < 5) {
        cout << "Nhap MatKhau: ";
        cin >> MatKhau;

        MatKhau = trim(MatKhau);

        for (int i = 0; i < MAX; i++) {
            if (dangNhapList[i].MaSV == MaSV && dangNhapList[i].MATKHAU == MatKhau) {
                isLoggedIn = true;
                break;
            }
        }

        if (isLoggedIn) {
            cout << "Dang nhap thanh cong." << endl;
            return true;
        } else {
            soLanSai++;
            cout << "Sai MaSV hoac MatKhau. Ban con " << (5 - soLanSai) << " lan thu lai." << endl;
        }
    }

    cout << "Dang nhap khong thanh cong. Thoat chuong trinh." << endl;
    return false;
}

void hienThiThongTinSinhVien(const string& maSV) {
    for (int i = 0; i < soLuongSinhVien; i++) {
        if (sinhVienList[i].MaSV == maSV) {
            cout << "MaSV: " << sinhVienList[i].MaSV << endl;
            cout << "Ho Ten: " << sinhVienList[i].HoTenSV << endl;
            cout << "Gioi Tinh: " << sinhVienList[i].GioiTinh << endl;
            cout << "Nam Sinh: " << sinhVienList[i].NamSinh << endl;
            cout << "Trung Binh HK: " << sinhVienList[i].TrungbinhHK << endl;
            return;
        }
    }
    cout << "Sinh vien khong ton tai." << endl;
}

void hienThiDiemSoSinhVien(const string& maSV) {
    for (int i = 0; i < soLuongSinhVien; i++) {
        if (diemList[i].MaSV == maSV) {
            cout << "MaSV: " << diemList[i].MaSV << endl;
            cout << "KTLT: " << diemList[i].KTLT << endl;
            cout << "MMT: " << diemList[i].MMT << endl;
            cout << "CTDL: " << diemList[i].CTDL << endl;
            return;
        }
    }
    cout << "Diem so cua sinh vien khong ton tai." << endl;
}

void hienThiMenu(const string& maSV) {
    int luaChon;

    cout << "\n1. Xem thong tin sinh vien\n";
    cout << "2. Xem diem so sinh vien\n";
    cout << "3. Thoat\n";

    cout << "Chon chuc nang: ";
    cin >> luaChon;

    switch (luaChon) {
        case 1:
            hienThiThongTinSinhVien(maSV);
            break;
        case 2:
            hienThiDiemSoSinhVien(maSV);
            break;
        case 3:
            cout << "Thoat chuong trinh." << endl;
            exit(0);
        default:
            cout << "Lua chon khong hop le." << endl;
            break;
    }
}

int main() {
    string MaSV;

    // Đọc dữ liệu từ các file
    docThongTinSinhVien();
    docDiemSoSinhVien();
    docThongTinDangNhap();

    // Đăng nhập
    if (dangNhap()) {
        cout << "Nhap MaSV de truy cap menu: ";
        cin >> MaSV;
        hienThiMenu(MaSV);
    } else {
        cout << "Dang nhap khong thanh cong." << endl;
    }

    return 0;
}

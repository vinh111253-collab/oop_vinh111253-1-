#include <iostream>
#include <string>

using namespace std;

class KhachHang {
    string ten, diachi, sdt;
    int ma;

public:
    KhachHang();
    void nhap();
    void in();
};

KhachHang::KhachHang() {
    ten = "";
    diachi = "";
    sdt = "";
    ma = 0;
}

void KhachHang::nhap() {
    cout << "Nhap ten khach hang: ";
    getline(cin >> ws, ten);
    cout << "Nhap dia chi: ";
    getline(cin >> ws, diachi);
    cout << "Nhap so dien thoai: ";
    cin >> sdt;
    cout << "Nhap ma khach hang: ";
    cin >> ma;
}

void KhachHang::in() {
    cout << "Ten khach hang: " << ten << endl;
    cout << "Dia chi: " << diachi << endl;
    cout << "So dien thoai: " << sdt << endl;
    cout << "Ma khach hang: " << ma << endl;
}

class ChuCuaHang {
    string ten, diachi, sdt, masothue; 
    int ma;

public:
    ChuCuaHang();
    void nhap();
    void in();
};

ChuCuaHang::ChuCuaHang() {
    ten = "";
    diachi = "";
    sdt = "";
    ma = 0;
    masothue = "";
}

void ChuCuaHang::nhap() {
    cout << "Nhap ten chu cua hang: ";
    getline(cin >> ws, ten);
    cout << "Nhap dia chi: ";
    getline(cin >> ws, diachi);
    cout << "Nhap so dien thoai: ";
	cin >> sdt;
    cout << "Nhap ma chu cua hang: ";
    cin >> ma;
    cout << "Nhap ma so thue cua chu cua hang: ";
    cin >> masothue;
}

void ChuCuaHang::in() {
    cout << "Ten chu cua hang: " << ten << endl;
    cout << "Dia chi: " << diachi << endl;
    cout << "So dien thoai: " << sdt << endl;
    cout << "Ma chu cua hang: " << ma << endl;
    cout << "Ma so thue cua chu cua hang: " << masothue << endl;
}

class HangHoa {
    string tenhang, donvitinh;
    int dongia, soluong, mahang;

public:
    HangHoa();
    void nhap();
    void in();
    float TinhTien() {
        return dongia * soluong;
    }
};

HangHoa::HangHoa() {
    tenhang = "";
    donvitinh = "";
    dongia = 0;
    soluong = 0;
    mahang = 0;
}

void HangHoa::nhap() {
    cout << "Nhap ten hang: ";
    getline(cin >> ws, tenhang);
    cout << "Nhap don vi tinh: ";
    cin >> donvitinh;
    cout << "Nhap don gia: ";
    cin >> dongia;
    cout << "Nhap so luong: ";
    cin >> soluong;
    cout << "Nhap ma hang: ";
    cin >> mahang;
}

void HangHoa::in() {
    cout << "Ten hang hoa: " << tenhang << endl;
    cout << "Don vi tinh: " << donvitinh << endl;
    cout << "Don gia: " << dongia << endl;
    cout << "So luong: " << soluong << endl;
    cout << "Ma hang hoa: " << mahang << endl;
    cout << "Thanh tien: " << TinhTien() << endl;
}

class HoaDon {
    ChuCuaHang x;
    KhachHang y;
    int soluonghang;
    HangHoa *a;

public:
    HoaDon();   
    void nhap();
    void in();
};

HoaDon::HoaDon() {
    soluonghang = 0;
    a = nullptr; // Khoi tao con tro rong
}



void HoaDon::nhap() {
    x.nhap();
    y.nhap();
    cout << "Nhap so luong hang: ";
    cin >> soluonghang;    
    a = new HangHoa[soluonghang];
    
    for (int i = 0; i < soluonghang; i++) {        
        a[i].nhap();
    }
}

void HoaDon::in() {
    cout << "\n-----HOA DON BAN HANG-----\n";
    x.in();
    cout << "\n";
    y.in();
    cout << "\n";
    for (int i = 0; i < soluonghang; i++) {
        a[i].in();
        cout << endl;
    }
}

int main() {
    HoaDon h1;
    h1.nhap();
    h1.in();
    return 0;
}

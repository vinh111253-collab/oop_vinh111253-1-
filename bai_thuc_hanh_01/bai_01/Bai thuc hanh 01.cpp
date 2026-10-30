#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
using namespace std;

class Xe {
private:
    int maXe;                  // Mã d?nh danh xe
    string loaiXe;             // "Car", "Motorcycle", "Bicycle"
    int gioVao;                // 0..23
    int thoiGianDo;            // 1..23
    double phiDoXe;            // VND
    bool dangChiemCho;

public:
    Xe(){
        maXe = 0;
        loaiXe = "";
        gioVao = 0;
        thoiGianDo = 0;
        phiDoXe = 0.0;
        dangChiemCho = false;
    };

    Xe(int ma, const string& loai, int gio, int thoiLuong){
        maXe = ma;
        loaiXe = chuanHoaLoaiXe(loai);
        gioVao = gio;
        thoiGianDo = thoiLuong;
        dangChiemCho = true;
        tinhPhiDoXe();
    };

    int layMaXe() const{
        return maXe;
    };
    string layLoaiXe() const{
        return loaiXe;
    };
    int layGioVao() const{
        return gioVao;
    };
    int layThoiGianDo() const{
        return thoiGianDo;
    };
    double layPhiDoXe() const{
        return phiDoXe;
    };
    bool layDangChiemCho() const{
        return dangChiemCho;
    };

    void ganMaXe(int ma){
        maXe = ma;
    };
    void ganLoaiXe(const string& loai){
        loaiXe = chuanHoaLoaiXe(loai);
        tinhPhiDoXe();
    };
    void ganGioVao(int gio){
        gioVao = gio;
        tinhPhiDoXe();
    };
    void ganThoiGianDo(int thoiLuong){
        thoiGianDo = thoiLuong;
        tinhPhiDoXe();
    };
    void ganPhiDoXe(double phi){
        phiDoXe = phi;
    };
    void ganDangChiemCho(bool trangThai){
        dangChiemCho = trangThai;
    };

    static string chuanHoaLoaiXe(string loai) {
        for (size_t i = 0; i < loai.length(); ++i) {
            loai[i] = static_cast<char>(tolower(static_cast<unsigned char>(loai[i])));
        }
        if (loai == "car") return "Car";
        if (loai == "motorcycle") return "Motorcycle";
        if (loai == "bicycle") return "Bicycle";
        return loai;
    };

    static bool laLoaiXeHopLe(const string& loai) {
        string t = chuanHoaLoaiXe(loai);
        return (t == "Car" || t == "Motorcycle" || t == "Bicycle");
    };

    void tinhPhiDoXe() {
        if (!dangChiemCho) { 
            phiDoXe = 0; 
            return; 
        }
        string chuanHoa = chuanHoaLoaiXe(loaiXe);
        double giaCoBan = 0.0;
        if (chuanHoa == "Car") giaCoBan = 6.0;
        else if (chuanHoa == "Motorcycle") giaCoBan = 4.0;
        else if (chuanHoa == "Bicycle") giaCoBan = 2.0;

        bool gioCaoDiem = (gioVao >= 6 && gioVao <= 9) || (gioVao >= 15 && gioVao <= 18);
        int h1 = (thoiGianDo > 2) ? 2 : thoiGianDo;
        int h2 = (thoiGianDo > 2) ? (thoiGianDo - 2) : 0;
        phiDoXe = h1 * (gioCaoDiem ? giaCoBan * 1.30 : giaCoBan * 0.95) + h2 * (giaCoBan * 0.90);
    };

    void hienThi() const {
        if (dangChiemCho)
            cout << "  [Xe ID: " << maXe << " | " << loaiXe << " | Gio vao: " << gioVao << "h | Do: " << thoiGianDo << "h | Phi: $" << fixed << setprecision(2) << phiDoXe << "]\n";
    };
};

class BaiDoXe {
private:
    int maBai;
    char kichThuoc;
    Xe xe1, xe2, xe3;
    bool coXe1, coXe2, coXe3;

public:
    BaiDoXe() : maBai(0), kichThuoc('S'), coXe1(false), coXe2(false), coXe3(false) {}
    BaiDoXe(int ma, char kt) : maBai(ma), kichThuoc(static_cast<char>(toupper(static_cast<unsigned char>(kt)))), coXe1(false), coXe2(false), coXe3(false) {}

    int layMaBai() const { 
        return maBai; 
    };
    char layKichThuoc() const { 
        return kichThuoc; 
    };
    Xe layXe1() const { 
        return xe1; 
    };
    Xe layXe2() const { 
        return xe2; 
    };
    Xe layXe3() const { 
        return xe3; 
    };
    bool layCoXe1() const { 
        return coXe1; 
    };
    bool layCoXe2() const { 
        return coXe2; 
    };
    bool layCoXe3() const { 
        return coXe3; 
    };

    int laySucChua() const { 
        return (kichThuoc == 'S') ? 1 : ((kichThuoc == 'M') ? 2 : 3); 
    };

    bool kTraXeTonTai(int ma) const {
        if (coXe1 && xe1.layMaXe() == ma) return true;
        if (coXe2 && xe2.layMaXe() == ma) return true;
        if (coXe3 && xe3.layMaXe() == ma) return true;
        return false;
    };

    bool themXe(const Xe& x) {
        int cap = laySucChua();
        if (cap >= 1 && !coXe1) { 
            xe1 = x; 
            coXe1 = true; 
            return true; 
        }
        if (cap >= 2 && !coXe2) { 
            xe2 = x; 
            coXe2 = true; 
            return true; 
        }		
        if (cap >= 3 && !coXe3) { 
            xe3 = x; 
            coXe3 = true; 
            return true; 
        }
        return false;
    };

    bool xoaXe(int ma) {
        if (coXe1 && xe1.layMaXe() == ma) { 
            coXe1 = false; 
            return true; 
        }
        if (coXe2 && xe2.layMaXe() == ma) { 
            coXe2 = false; 
            return true; 
        }
        if (coXe3 && xe3.layMaXe() == ma) { 
            coXe3 = false; 
            return true; 
        }
        return false;
    };

    void hienThi() const {
        cout << "--- Bai ID: " << maBai << " | Kich thuoc: " << kichThuoc << " ---\n";
        bool coXe = false;
        if (coXe1) { 
            xe1.hienThi(); 
            coXe = true; 
        }
        if (coXe2) { 
            xe2.hienThi(); 
            coXe = true; 
        }
        if (coXe3) { 
            xe3.hienThi(); 
            coXe = true; 
        }
        if (!coXe) cout << "  (Trong)\n";
    };
};

class GiaoDienHeThong {
private:
    BaiDoXe bai1, bai2, bai3;
    bool coBai1, coBai2, coBai3;

    bool kTraTrungBai(int ma) const {
        if (coBai1 && bai1.layMaBai() == ma) return true;
        if (coBai2 && bai2.layMaBai() == ma) return true;
        if (coBai3 && bai3.layMaBai() == ma) return true;
        return false;
    };

    bool kTraTrungXe(int ma) const {
        if (coBai1 && bai1.kTraXeTonTai(ma)) return true;
        if (coBai2 && bai2.kTraXeTonTai(ma)) return true;
        if (coBai3 && bai3.kTraXeTonTai(ma)) return true;
        return false;
    };

    void tinhPhiLoaiXe(const Xe& x, bool coXe, double& tongOTo, int& demOTo, double& tongXeMay, int& demXeMay, double& tongXeDap, int& demXeDap) const {
        if (coXe) {
            string t = x.layLoaiXe();
            if (t == "Car") { tongOTo += x.layPhiDoXe(); demOTo++; }
            else if (t == "Motorcycle") { tongXeMay += x.layPhiDoXe(); demXeMay++; }
            else if (t == "Bicycle") { tongXeDap += x.layPhiDoXe(); demXeDap++; }
        }
    };

public:
    GiaoDienHeThong() : coBai1(false), coBai2(false), coBai3(false) {}

    void chayMenu() {
        int chon;
        do {
            cout << "\n================ MENU QUAN LY BAI DO XE ================\n"
                 << "1. Tao Bai  2. Them xe  3. Xoa bai  4. Lay xe  5. Xem tat ca\n"
                 << "6. Xem chi tiet bai  7. Tim theo loai  8. Bao cao phi  9. Thoat\nChon (1-9): ";
            cin >> chon;

            switch (chon) {
                case 1: taoBai(); break;
                case 2: themXe(); break;
                case 3: xoaBai(); break;
                case 4: layXe(); break;
                case 5: hienThiTatCa(); break;
                case 6: hienThiChiTiet(); break;
                case 7: timTheoLoai(); break;
                case 8: baoCaoPhi(); break;
                case 9: cout << "Da thoat chuong trinh!\n"; break;
                default: cout << "[Loi] Lua chon khong hop le!\n";
            }
        } while (chon != 9);
    };

private:
    void taoBai() {
        int ma; char kt;
        cout << "Nhap ID bai: "; 
        cin >> ma;
        if (kTraTrungBai(ma)) {
            cout << "[Loi] ID bai do xe da ton tai!\n";
            return;
        }

        cout << "Nhap kich thuoc (S/M/L): "; 
        cin >> kt;
        kt = static_cast<char>(toupper(static_cast<unsigned char>(kt)));
        if (kt != 'S' && kt != 'M' && kt != 'L') {
            cout << "[Loi] Kich thuoc khong hop le (chi nhan S, M hoac L)!\n";
            return;
        }

        if (!coBai1) { bai1 = BaiDoXe(ma, kt); coBai1 = true; }
        else if (!coBai2) { bai2 = BaiDoXe(ma, kt); coBai2 = true; }
        else if (!coBai3) { bai3 = BaiDoXe(ma, kt); coBai3 = true; }
        else { cout << "[Loi] Da dat toi da 3 bai do xe!\n"; return; }
        cout << "[OK] Da tao bai ID " << ma << "\n";
    };

    void themXe() {
        int ma, gio, doL; string loai;
        cout << "Nhap ID xe: "; cin >> ma;
        if (kTraTrungXe(ma)) {
            cout << "[Loi] ID xe da ton tai trong he thong!\n";
            return;
        }

        cout << "Nhap loai xe (Car/Motorcycle/Bicycle): "; cin >> loai;
        if (!Xe::laLoaiXeHopLe(loai)) { cout << "[Loi] Loai xe khong hop le!\n"; return; }

        cout << "Nhap gio vao (0-23): "; cin >> gio;
        if (gio < 0 || gio > 23) {
            cout << "[Loi] Gio vao phai tu 0 den 23!\n";
            return;
        }

        cout << "Nhap so gio do (1-23): "; cin >> doL;
        if (doL < 1 || doL > 23) {
            cout << "[Loi] So gio do phai tu 1 den 23!\n";
            return;
        }

        Xe x(ma, loai, gio, doL);
        if (coBai1 && bai1.themXe(x)) cout << "[OK] Da them vao Bai ID " << bai1.layMaBai() << "\n";
        else if (coBai2 && bai2.themXe(x)) cout << "[OK] Da them vao Bai ID " << bai2.layMaBai() << "\n";
        else if (coBai3 && bai3.themXe(x)) cout << "[OK] Da them vao Bai ID " << bai3.layMaBai() << "\n";
        else cout << "[Loi] Tat ca cac bai deu day hoac chua duoc tao!\n";
    };

    void xoaBai() {
        int ma; cout << "Nhap ID bai can xoa: "; cin >> ma;
        if (coBai1 && bai1.layMaBai() == ma) coBai1 = false;
        else if (coBai2 && bai2.layMaBai() == ma) coBai2 = false;
        else if (coBai3 && bai3.layMaBai() == ma) coBai3 = false;
        else { cout << "[Loi] Khong tim thay bai!\n"; return; }
        cout << "[OK] Da xoa bai ID " << ma << "\n";
    };

    void layXe() {
        int ma; cout << "Nhap ID xe can lay: "; cin >> ma;
        if ((coBai1 && bai1.xoaXe(ma)) || (coBai2 && bai2.xoaXe(ma)) || (coBai3 && bai3.xoaXe(ma)))
            cout << "[OK] Da lay xe ra khoi he thong!\n";
        else cout << "[Loi] Khong tim thay xe!\n";
    };

    void hienThiTatCa() {
        if (!coBai1 && !coBai2 && !coBai3) cout << "Chua co bai do xe nao.\n";
        if (coBai1) bai1.hienThi();
        if (coBai2) bai2.hienThi();
        if (coBai3) bai3.hienThi();
    };

    void hienThiChiTiet() {
        int ma; cout << "Nhap ID bai: "; cin >> ma;
        if (coBai1 && bai1.layMaBai() == ma) bai1.hienThi();
        else if (coBai2 && bai2.layMaBai() == ma) bai2.hienThi();
        else if (coBai3 && bai3.layMaBai() == ma) bai3.hienThi();
        else cout << "[Loi] Khong tim thay bai!\n";
    };

    void timTheoLoai() {
        string loai; cout << "Nhap loai xe (Car/Motorcycle/Bicycle): "; cin >> loai;
        string norm = Xe::chuanHoaLoaiXe(loai);

        if (coBai1) {
            if (bai1.layCoXe1() && bai1.layXe1().layLoaiXe() == norm) bai1.layXe1().hienThi();
            if (bai1.layCoXe2() && bai1.layXe2().layLoaiXe() == norm) bai1.layXe2().hienThi();
            if (bai1.layCoXe3() && bai1.layXe3().layLoaiXe() == norm) bai1.layXe3().hienThi();
        }
        if (coBai2) {
            if (bai2.layCoXe1() && bai2.layXe1().layLoaiXe() == norm) bai2.layXe1().hienThi();
            if (bai2.layCoXe2() && bai2.layXe2().layLoaiXe() == norm) bai2.layXe2().hienThi();
            if (bai2.layCoXe3() && bai2.layXe3().layLoaiXe() == norm) bai2.layXe3().hienThi();
        }
        if (coBai3) {
            if (bai3.layCoXe1() && bai3.layXe1().layLoaiXe() == norm) bai3.layXe1().hienThi();
            if (bai3.layCoXe2() && bai3.layXe2().layLoaiXe() == norm) bai3.layXe2().hienThi();
            if (bai3.layCoXe3() && bai3.layXe3().layLoaiXe() == norm) bai3.layXe3().hienThi();
        }
    };

    void baoCaoPhi() {
        double tongOTo = 0, tongXeMay = 0, tongXeDap = 0;
        int demOTo = 0, demXeMay = 0, demXeDap = 0;

        if (coBai1) {
            tinhPhiLoaiXe(bai1.layXe1(), bai1.layCoXe1(), tongOTo, demOTo, tongXeMay, demXeMay, tongXeDap, demXeDap);
            tinhPhiLoaiXe(bai1.layXe2(), bai1.layCoXe1(), tongOTo, demOTo, tongXeMay, demXeMay, tongXeDap, demXeDap);
            tinhPhiLoaiXe(bai1.layXe3(), bai1.layCoXe1(), tongOTo, demOTo, tongXeMay, demXeMay, tongXeDap, demXeDap);
        }
        if (coBai2) {
            tinhPhiLoaiXe(bai2.layXe1(), bai2.layCoXe1(), tongOTo, demOTo, tongXeMay, demXeMay, tongXeDap, demXeDap);
            tinhPhiLoaiXe(bai2.layXe2(), bai2.layCoXe1(), tongOTo, demOTo, tongXeMay, demXeMay, tongXeDap, demXeDap);
            tinhPhiLoaiXe(bai2.layXe3(), bai2.layCoXe1(), tongOTo, demOTo, tongXeMay, demXeMay, tongXeDap, demXeDap);
        }
        if (coBai3) {
            tinhPhiLoaiXe(bai3.layXe1(), bai3.layCoXe1(), tongOTo, demOTo, tongXeMay, demXeMay, tongXeDap, demXeDap);
            tinhPhiLoaiXe(bai3.layXe2(), bai3.layCoXe1(), tongOTo, demOTo, tongXeMay, demXeMay, tongXeDap, demXeDap);
            tinhPhiLoaiXe(bai3.layXe3(), bai3.layCoXe1(), tongOTo, demOTo, tongXeMay, demXeMay, tongXeDap, demXeDap);
        }

        cout << "\n--- BAO CAO PHI TRUNG BINH THEO LOAI XE ---\n";
        int tongSoXe = demOTo + demXeMay + demXeDap;
        if (tongSoXe == 0) {
            cout << "Chua co xe nao trong he thong.\n";
        } else {
            if (demOTo > 0) cout << "  * Car: $" << fixed << setprecision(2) << (tongOTo / demOTo) << " (" << demOTo << " xe)\n";
            else cout << "  * Car: N/A (0 xe)\n";

            if (demXeMay > 0) cout << "  * Motorcycle: $" << fixed << setprecision(2) << (tongXeMay / demXeMay) << " (" << demXeMay << " xe)\n";
            else cout << "  * Motorcycle: N/A (0 xe)\n";

            if (demXeDap > 0) cout << "  * Bicycle: $" << fixed << setprecision(2) << (tongXeDap / demXeDap) << " (" << demXeDap << " xe)\n";
            else cout << "  * Bicycle: N/A (0 xe)\n";
        }
    };
};

int main(){
    GiaoDienHeThong app;
    app.chayMenu();
    return 0;
}

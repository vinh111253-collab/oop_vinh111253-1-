#include <iostream>
#include <string>
using namespace std;

class MatHang{
	private:
	string ten;
	int soluong;
	double giaban;
	
	public:
		void nhap(){
			cout<<"Ten mat hang: ";
			getline(cin>>ws,ten);	
			cout<<"So luong: ";
			cin>>soluong;
			cout<<"Gia ban: ";
			cin>>giaban;
		}
		double ThanhTien(){
			return soluong * giaban;
		}
		void xuat(){
			cout<<ten<<", "<<soluong<<", "<<giaban<<ThanhTien();
		}
};

class HoaDon{
	private:
		string tenKH;
		int n;
		MatHang ds[100];
	public:
		void nhap(){
			cout<<"Nhap ho ten khach: ";
			getline(cin>>ws,tenKH);
			cout<<"Nhap so mat hang da mua: ";
			cin>>n;
			for(int i=0;i<n;i++){
				cout<<"Nhap mat hang thu "<<i+1<<":\n";
				ds[i].nhap();
			}
		}
		double TongTien(){
			double tong =0;
			for(int i=0;i<n;i++){
				tong+= ds[i].ThanhTien();
			}
			return tong;
		}
		void xuat(){
			cout<<"\nHoa don ban hang\n";
			cout<<"Ho ten khach: "<<tenKH<<"\n";
			cout<<"Danh sach cac mat hang da mua: "<<n<<"\n";
			for(int i=0;i<n;i++){
			cout<<i+1<<". ";
			ds[i].xuat();
			cout<<"\n";
			}
			cout<<"Tong tien: "<<TongTien()<<"\n";
		}
};

int main(){
	HoaDon hd;
	hd.nhap();
	hd.xuat();
	return 0;
}

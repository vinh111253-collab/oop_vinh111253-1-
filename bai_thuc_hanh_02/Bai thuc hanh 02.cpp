#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Vehicle {
private:
    int vehicleID;
    string vehicleType;
    int entryTime;
    int parkingDuration;
    double parkingFee;

public:
    Vehicle() : vehicleID(0), vehicleType(""), entryTime(0), parkingDuration(0), parkingFee(0.0) {}
    Vehicle(int id, string type, int entry, int duration)
        : vehicleID(id), vehicleType(type), entryTime(entry), parkingDuration(duration) {
        parkingFee = calculateFee();
    }

    int getID() const { return vehicleID; }
    string getType() const { return vehicleType; }
    double getFee() const { return parkingFee; }
    void setID(int id) { vehicleID = id; }

    double calculateFee() const {
        double fee = (vehicleType == "Car") ? 6.00 : (vehicleType == "Motorcycle") ? 4.00 : 2.00;
        bool peakHours = (entryTime >= 6 && entryTime <= 9) || (entryTime >= 15 && entryTime <= 18);
        double tinhphi = 0;
        for (int i = 0; i < parkingDuration; ++i) {
            tinhphi += fee * (i < 2 ? (peakHours ? 1.30 : 0.95) : 0.9);
        }
        return tinhphi;
    }

    void HienThi() const {
        cout << "Ma xe: " << vehicleID << "\t"
             << "Loai xe: " << vehicleType << "\t"
             << "Gio vao: " << entryTime << "\t"
             << "Gio do: " << parkingDuration << "\t"
             << "Phi do xe: $" << fixed << setprecision(2) << parkingFee << "\n";
    }
};

class ParkingLot {
private:
    int parkID;
    char size;
    static const int MAX_VEHICLES = 3;
    Vehicle vehicles[MAX_VEHICLES];
    int currentVehicleCount;

    int getMaxCapacity() const {
        return (size == 'S') ? 1 : (size == 'M') ? 2 : 3;
    }

public:
    ParkingLot() : parkID(0), size('S'), currentVehicleCount(0) {}
    ParkingLot(int id, char size) : parkID(id), size(size), currentVehicleCount(0) {}

    int getID() const { return parkID; }

    bool isFull() const {
        return currentVehicleCount >= getMaxCapacity();
    }

    int findVehicleIndex(int vID) const {
        for (int i = 0; i < currentVehicleCount; ++i) {
            if (vehicles[i].getID() == vID) return i;
        }
        return -1;
    }

    bool addVehicle(const Vehicle& v) {
        if (isFull()) return false;
        vehicles[currentVehicleCount++] = v;
        return true;
    }

    bool removeVehicle(int vID) {
        int idx = findVehicleIndex(vID);
        if (idx == -1) return false;
        for (int i = idx; i < currentVehicleCount - 1; ++i) {
            vehicles[i] = vehicles[i + 1];
        }
        --currentVehicleCount;
        return true;
    }

    void displayLotInfo() const {
        cout << "Bai " << parkID << " [" << size << "] " << currentVehicleCount << "/" << getMaxCapacity() << " xe\n";
        for (int i = 0; i < currentVehicleCount; ++i) {
            vehicles[i].HienThi();
        }
    }

    int getCount() const { return currentVehicleCount; }
    Vehicle getVehicle(int index) const { return vehicles[index]; }
};

class SystemInterface {
private:
    static const int MAX_LOTS = 10;
    ParkingLot parkingLots[MAX_LOTS];
    int currentLotCount;

public:
    SystemInterface() : currentLotCount(0) {
        srand((unsigned int)time(0));
    }

    bool isParkIDExists(int pID) const {
        for (int i = 0; i < currentLotCount; ++i) {
            if (parkingLots[i].getID() == pID) return true;
        }
        return false;
    }

    bool isVehicleIDExists(int vID) const {
        for (int i = 0; i < currentLotCount; ++i) {
            if (parkingLots[i].findVehicleIndex(vID) != -1) return true;
        }
        return false;
    }

    int generateRandomID() const {
        int id;
        do {
            id = 1000 + rand() % 9000;
        } while (isParkIDExists(id) || isVehicleIDExists(id));
        return id;
    }

    int batloi(const string& msg) {
        int x;
        while (true) {
            cout << msg;
            cin >> x;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Sai kieu du lieu! Vui long nhap lai.\n";
            } else {
                return x;
            }
        }
    }

    void giaodien() {
        int chon;
        while (true) {
            cout << "\n----- QUAN LY BAI DO XE -----\n"
                 << "1. Tao bai do xe moi\n"
                 << "2. Them xe vao bai do\n"
                 << "3. Xoa bai do xe\n"
                 << "4. Lay xe\n"
                 << "5. Hien thi danh sach bai do xe\n"
                 << "6. Hien thi danh sach xe theo bai cu the\n"
                 << "7. Liet ke xe theo loai\n"
                 << "8. Tom tat phi do xe trung binh\n"
                 << "9. Thoat\n";
            chon = batloi("Chon: ");

            switch (chon) {
                case 1: {
                    if (currentLotCount >= MAX_LOTS) {
                        cout << "He thong da dat toi da " << MAX_LOTS << " bai do!\n";
                        break;
                    }
                    int id = batloi("Ma bai: ");
                    if (isParkIDExists(id)) {
                        id = generateRandomID();
                        cout << "Ma bai bi trung! Tu dong gan ma moi: " << id << "\n";
                    }
                    char s;
                    cout << "Kich thuoc (S/M/L): ";
                    cin >> s;
                    parkingLots[currentLotCount++] = ParkingLot(id, s);
                    cout << "Da tao bai " << id << "\n";
                    break;
                }

                case 2: {
                    if (currentLotCount == 0) {
                        cout << "Chua co bai do nao\n";
                        break;
                    }
                    int id = batloi("Ma xe: ");
                    if (isVehicleIDExists(id)) {
                        id = generateRandomID();
                        cout << "Ma xe bi trung! Tu dong gan ma moi: " << id << "\n";
                    }
                    string type;
                    cout << "Loai (Car/Motorcycle/Bicycle): ";
                    cin >> type;
                    int entry = batloi("Gio vao (0-23): ");
                    int duration = batloi("Thoi luong (1-23): ");

                    Vehicle v(id, type, entry, duration);
                    bool added = false;
                    for (int i = 0; i < currentLotCount; ++i) {
                        if (!parkingLots[i].isFull()) {
                            parkingLots[i].addVehicle(v);
                            cout << "Da them xe " << id << " vao bai " << parkingLots[i].getID()
                                 << "\tPhi: $" << fixed << setprecision(2) << v.getFee() << "\n";
                            added = true;
                            break;
                        }
                    }
                    if (!added) cout << "Tat ca cac bai do deu da day\n";
                    break;
                }

                case 3: {
                    int id = batloi("Ma bai can xoa: ");
                    bool found = false;
                    for (int i = 0; i < currentLotCount; ++i) {
                        if (parkingLots[i].getID() == id) {
                            for (int j = i; j < currentLotCount - 1; ++j) {
                                parkingLots[j] = parkingLots[j + 1];
                            }
                            --currentLotCount;
                            found = true;
                            cout << "Da xoa bai " << id << "\n";
                            break;
                        }
                    }
                    if (!found) cout << "Khong tim thay bai " << id << "\n";
                    break;
                }

                case 4: {
                    int vID = batloi("Ma xe can lay: ");
                    bool ok = false;
                    for (int i = 0; i < currentLotCount; ++i) {
                        if (parkingLots[i].removeVehicle(vID)) {
                            ok = true;
                            break;
                        }
                    }
                    cout << (ok ? "Da lay xe ra\n" : "Khong tim thay xe\n");
                    break;
                }

                case 5: {
                    for (int i = 0; i < currentLotCount; ++i) {
                        parkingLots[i].displayLotInfo();
                    }
                    break;
                }

                case 6: {
                    int id = batloi("Ma bai: ");
                    bool found = false;
                    for (int i = 0; i < currentLotCount; ++i) {
                        if (parkingLots[i].getID() == id) {
                            parkingLots[i].displayLotInfo();
                            found = true;
                            break;
                        }
                    }
                    if (!found) cout << "Khong tim thay bai " << id << "\n";
                    break;
                }

                case 7: {
                    string type;
                    cout << "Loai xe: ";
                    cin >> type;
                    for (int i = 0; i < currentLotCount; ++i) {
                        for (int j = 0; j < parkingLots[i].getCount(); ++j) {
                            Vehicle v = parkingLots[i].getVehicle(j);
                            if (v.getType() == type) {
                                cout << "[Bai " << parkingLots[i].getID() << "] ";
                                v.HienThi();
                            }
                        }
                    }
                    break;
                }

                case 8: {
                    string types[3] = {"Car", "Motorcycle", "Bicycle"};

                    cout << "--- TOAN HE THONG ---\n";
                    for (int t = 0; t < 3; ++t) {
                        int count = 0;
                        double totalFee = 0;
                        for (int i = 0; i < currentLotCount; ++i) {
                            for (int j = 0; j < parkingLots[i].getCount(); ++j) {
                                Vehicle v = parkingLots[i].getVehicle(j);
                                if (v.getType() == types[t]) {
                                    ++count;
                                    totalFee += v.getFee();
                                }
                            }
                        }
                        cout << types[t] << ": ";
                        if (count == 0) cout << "khong co xe\n";
                        else cout << count << " xe | TB: $" << fixed << setprecision(2) << totalFee / count << "\n";
                    }

                    cout << "--- THEO TUNG BAI ---\n";
                    for (int i = 0; i < currentLotCount; ++i) {
                        cout << "Bai " << parkingLots[i].getID() << ":\n";
                        for (int t = 0; t < 3; ++t) {
                            int count = 0;
                            double totalFee = 0;
                            for (int j = 0; j < parkingLots[i].getCount(); ++j) {
                                Vehicle v = parkingLots[i].getVehicle(j);
                                if (v.getType() == types[t]) {
                                    ++count;
                                    totalFee += v.getFee();
                                }
                            }
                            cout << "  " << types[t] << ": ";
                            if (count == 0) cout << "khong co xe\n";
                            else cout << count << " xe | TB: $" << fixed << setprecision(2) << totalFee / count << "\n";
                        }
                    }
                    break;
                }

                case 9:
                    return;

                default:
                    cout << "Lua chon khong hop le!\n";
            }
        }
    }
};

int main() {
    SystemInterface sys;
    sys.giaodien();
    return 0;
}

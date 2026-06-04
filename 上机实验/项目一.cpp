#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
using namespace std;


int main() {
    SetConsoleOutputCP(CP_UTF8);
    int n, k;
    cin>>n>>k;
    vector<int>station;
    station.push_back(0);
    /////////////////count
    int count = 0;
    /////////////////
    for (int i = 0; i < n+1; i++) {
        int length = 0;
        cin>>length;
        station.push_back(length);
    }
    bool result = true;
    vector<int>add_station;
    int total_fuel = 0;//耗油量
    int j = 0;
    for (int i = 1; i < station.size(); i = j + 1) {
        if (result == false) {
            break;
        }
        int fuel_cost = 0;
        for (j = i; j < station.size(); j++) {
            if (station[j] > n) {
                result = false;
                break;
            }
            fuel_cost += station[j];
            if (fuel_cost >= n) {
                fuel_cost -= station[j];
                add_station.push_back(--j);
                total_fuel += fuel_cost;
                break;
            }
        }
    }
    if (result == true) {
        cout<<add_station.size()<<endl;
        for (int i = 0; i < add_station.size()-1; i++) {
            cout<<add_station[i]<<" ";
        }
        cout<<add_station[add_station.size()]<<endl;
        cout<<total_fuel<<endl;

        ofstream write("C:/Users/LENOVO/Desktop/output.txt");
        write<<add_station.size()<<endl;
        for (int i = 0; i < add_station.size()-1; i++) {
            write<<add_station[i]<<" ";
        }
        write<<add_station[add_station.size()-1]<<endl;
        write<<total_fuel;
        write.close();
    }
    else {
        ofstream write("C:/Users/LENOVO/Desktop/output.txt");
        write<<"No solution"<<endl;
        write.close();
        cout<<"No solution"<<endl;
    }
    return 0;;
}
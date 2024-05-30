//#include "src/pedestrian/Pedestrian.cpp"
#include <nlohmann/json.hpp>
//#include "src/ward/Ward.cpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
// gia su co numVisitor tu bai truoc

using json = nlohmann::json;

using namespace std;

struct WardData {
    string ward;
    int value;
};

// Hàm chọn ký tự với số lượng còn lại lớn nhất
char Chon_1_Ward(vector<WardData> &ward_values) {
    // Tìm phần tử có giá trị lớn nhất
    auto max_it = max_element(ward_values.begin(), ward_values.end(),
                              [](const WardData &a, const WardData &b) {
                                  return a.value < b.value;
                              });
    // Lấy ký tự đầu tiên của phần tử có giá trị lớn nhất khac A (Do start = end = A)
    char selected;
    if (max_it->ward[0] != 'A'){
        selected = max_it->ward[0];
    }
    else{
        selected = max_it->ward[1];
    }
    
    // Giảm số lượng của ký tự đó
    max_it->value--;
    // Trả về ký tự được chọn
    return selected;
}


vector<char> Chon_3_Ward(vector<WardData> &ward_values, int n, string start, string end) {
    sort(ward_values.begin(), ward_values.end(), [](const WardData &a, const WardData &b) {
        return a.value > b.value;
    });

    vector<char> selected;
    for (int i = 0; i < ward_values.size() && selected.size() < n; ++i) {
        selected.push_back(ward_values[i].ward[0]);
        ward_values[i].value--;  // Giảm số lượng của ký tự sau khi chọn
        // Kiểm tra nếu không đủ ký tự được chọn
        if (ward_values[i].value < 0){
            cerr << "Không đủ ward để chọn!" << endl;
            //Quay lai bai 4 sinh file ward.json khac va thuc hien lai bai 5
        }
        //cout << ward_values[i].value;
    }
    return selected;
}

void Ex5(){
    ifstream jsonFile1("Statistic.json");

    // Check if the file was successfully opened
    if (!jsonFile1.is_open()) {
        cerr << "Could not open the file 1!" << endl;
        return;
    }
    
    // Parse the JSON file
    json jsonStatistic;
    jsonFile1 >> jsonStatistic;

    // Close the file
    jsonFile1.close();

    ifstream jsonFile2("Ward.json");

    // Check if the file was successfully opened
    if (!jsonFile2.is_open()) {
        cerr << "Could not open the file 2!" << endl;
        return;
    }
    
    // Parse the JSON file
    json jsonWard;
    jsonFile2 >> jsonWard;

    // Close the file
    jsonFile2.close();

    int single = jsonStatistic["type"]["visitorCount"];
    int triple = (int)jsonStatistic["type"]["personelCount"] + (int)jsonStatistic["type"]["patientCount"];

    vector<WardData> ward_values;

    // Lặp qua các cặp key-value trong JSON và thêm vào vector
    for (json::iterator it = jsonWard.begin(); it != jsonWard.end(); ++it) {
        WardData ward_data;
        ward_data.ward = it.key(); // Key là tên của ward
        ward_data.value = it.value(); // Value là giá trị của ward
        ward_values.push_back(ward_data);
    }

    ifstream jsonFile3("Pedestrian.json");

    // Check if the file was successfully opened
    if (!jsonFile3.is_open()) {
        cerr << "Could not open the file 3!" << endl;
        return;
    }
    
    // Parse the JSON file
    json jsonPedestrian;
    jsonFile3 >> jsonPedestrian;

    // Close the file
    jsonFile3.close();

    for (auto &item : jsonPedestrian) {
        string type = item["type"];
        //int ID = item["ID"];
        if (type == "Visitor") {
            // Chọn một ký tự cho Visitor
            char selected = Chon_1_Ward(ward_values);
            cout << selected << endl;
            item["journey"] = string(1, selected);
        } else if (type == "Personel" || type == "Patient") {
            // Chọn ba ký tự cho Personnel và Patient
            string start = item["start"];
            string end = item["end"];
            vector<char> selected = Chon_3_Ward(ward_values, 3, start, end);
            // Kiểm tra nếu strselected có string "A" thì đổi vị trí để "A" nằm ở index 1
            if(selected[0] == 'A'){
                swap(selected[0], selected[1]);
            }
            if(selected[2] == 'A'){
                swap(selected[2], selected[1]);
            }

            vector<string> strselected;
            for (char c : selected) 
            {
                string s(1, c); // Tạo một chuỗi từ một ký tự
                strselected.push_back(s); // Thêm chuỗi vào vector string
                cout << s;
            }
            
            cout << endl;
            item["journey"] = strselected;
            //cout << strselected[0] << strselected[1] << strselected[2] << endl;
        }
    }

    ofstream outFile("Pedestrian.json");
    if (!outFile.is_open()) {
        cerr << "Không thể mở tệp để ghi!" << endl;
        return;
    }

    // Ghi JSON đã cập nhật vào tệp
    outFile << jsonPedestrian.dump(4);  // Dinh dang JSON
    outFile.close();

    return;
}
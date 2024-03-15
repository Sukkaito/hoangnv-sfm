#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <lib/nlohmann/json.hpp>

using json = nlohmann::json;

struct Pedestrian {
    int age;
    double openness;
    double neuroticism;
    std::map<std::string, double> initial_emotions;
    std::string type;
    std::string department; // chỉ sử dụng cho Personnel
};

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<Pedestrian> generate_pedestrians(json& data) {
    std::vector<Pedestrian> pedestrians;

    int num_agents = data["numOfAgents"]["value"].get<int>();
    double no_disability_percentage = data["p1"]["value"].get<double>() + data["p2"]["value"].get<double>();
    int num_personnel = static_cast<int>(num_agents * (no_disability_percentage / 100));

    for (int i = 0; i < num_agents; ++i) {
        Pedestrian pedestrian;
        pedestrian.age = rand() % 80 + 11; // Tuổi từ 11 đến 90
        pedestrian.openness = static_cast<double>(rand() % 11 + 45) / 100.0; // Từ 0.45 đến 0.55
        pedestrian.neuroticism = static_cast<double>(rand() % 101) / 100.0; // Từ 0 đến 1

        for (const auto& emotion : {"pleasure", "surprise", "anger", "fear", "hate", "sad"}) {
            pedestrian.initial_emotions[emotion] = emotion == "pleasure" ? 0.75 : -0.4;
        }

        if (i < num_personnel) {
            pedestrian.type = "Personnel";
            pedestrian.department = split(data["journeyDistribution"]["value"].get<std::string>(), ',')[rand() % 6 + 1]; // Random từ khoảng không gian 1 đến 6
        } else {
            pedestrian.type = (rand() % 2) == 0 ? "Patient" : "Visitor";
        }

        pedestrians.push_back(pedestrian);
    }

    return pedestrians;
}

void write_json_file(const std::string& filename, const std::vector<Pedestrian>& pedestrians) {
    json root;

    for (const auto& pedestrian : pedestrians) {
        json pedestrian_json;
        pedestrian_json["age"] = pedestrian.age;
        pedestrian_json["openness"] = pedestrian.openness;
        pedestrian_json["neuroticism"] = pedestrian.neuroticism;
        pedestrian_json["initial_emotions"]["pleasure"] = pedestrian.initial_emotions.at("pleasure");
        pedestrian_json["initial_emotions"]["surprise"] = pedestrian.initial_emotions.at("surprise");
        pedestrian_json["initial_emotions"]["anger"] = pedestrian.initial_emotions.at("anger");
        pedestrian_json["initial_emotions"]["fear"] = pedestrian.initial_emotions.at("fear");
        pedestrian_json["initial_emotions"]["hate"] = pedestrian.initial_emotions.at("hate");
        pedestrian_json["initial_emotions"]["sad"] = pedestrian.initial_emotions.at("sad");
        pedestrian_json["type"] = pedestrian.type;
        if (pedestrian.type == "Personnel") {
            pedestrian_json["department"] = pedestrian.department;
        }
        root.push_back(pedestrian_json);
    }

    std::ofstream file(filename);
    file << root.dump(4); // Ghi dữ liệu JSON vào tệp với định dạng đẹp
}

int main() {
    srand(time(nullptr)); // Khởi tạo seed cho random

    std::ifstream file("dataEx3.json");
    json data;
    file >> data;

    std::vector<Pedestrian> pedestrians = generate_pedestrians(data);
    write_json_file("output.json", pedestrians);

    return 0;
}

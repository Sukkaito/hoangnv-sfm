import json
import random

class Pedestrian:
    def __init__(self, age, department, personality):
        self.age = age
        self.department = department
        self.personality = personality

    def toJSON(self):
        return {
            "age": self.age,
            "department": self.department,
            "personality": self.personality
        }


class Patient(Pedestrian):
    def __init__(self, age, department, personality, status):
        super().__init__(age, department, personality)
        self.type = "Patient"
        self.status = status

    def toJSON(self):
        json_data = super().toJSON()
        json_data.update({
            "type": self.type,
            "status": self.status
        })
        return json_data


class Visitor(Pedestrian):
    def __init__(self, age, department, personality):
        super().__init__(age, department, personality)
        self.type = "Visitor"
        self.status = random.choices(["noDisabilityNoOvertaking", "noDisabilityOvertaking"],
                                     weights=[60, 10])[0]

    def toJSON(self):
        json_data = super().toJSON()
        json_data.update({
            "type": self.type,
            "status": self.status
        })
        return json_data


class Personnel(Pedestrian):
    def __init__(self, age, departments, personality):
        super().__init__(age, departments, personality)
        self.type = "Personnel"
        self.departments = departments
        self.status = random.choices(["noDisabilityNoOvertaking", "noDisabilityOvertaking"],
                                     weights=[60, 10])[0]

    def toJSON(self):
        json_data = super().toJSON()
        json_data.update({
            "type": self.type,
            "status": self.status,
            "department": self.departments
        })
        return json_data


def generate_pedestrians(data):
    pedestrians = []
    num_openness = 0
    num_neuroticism = 0

    num_agents = data["numOfAgents"]["value"]
    num_personnel = int(num_agents * random.uniform(0.8, 0.9) * (
                data["walkability"]["distribution"]["noDisabilityNoOvertaking"]["value"] +
                data["walkability"]["distribution"]["noDisabilityOvertaking"]["value"]) / 100)

    departments = list(data["wardDistribution"]["distribution"].keys())[:-1]  # Exclude 'normal'
    journey_distribution = data["walkability"]["distribution"]["journeyDistribution"]["distribution"]
    for key in journey_distribution:
        if key != "forPersonel" and journey_distribution[key]["start"] in departments:
            departments.remove(journey_distribution[key]["start"])

    num_patients = 0
    num_visitors = 0
    num_crutches = 0
    num_sticks = 0
    num_wheelchairs = 0
    num_blind = 0

    while len(pedestrians) < num_agents:
        age = random.randint(11, 90)
        personality = random.choice(["open", "neurotic"])

        if (num_neuroticism >= 0.53 * num_agents):
            personality = "open"

        if (num_openness >= 0.53 * num_agents):
            personality = "neurotic"

        if len(pedestrians) < num_personnel:
            # Personnel
            departments_for_personnel = random.sample(departments, 3)  # Chọn ngẫu nhiên 3 khoa viện
            pedestrian = Personnel(age, departments_for_personnel, personality)
        else:
            pedestrian_type = random.choices([Patient, Visitor], weights=[70, 30])[0]
            department = random.choice(departments)
            if pedestrian_type == Patient:
                # Lấy danh sách các loại bệnh và trọng số tương ứng
                illnesses = ["crutches", "sticks", "wheelchairs", "blind"]
                weights = [data["walkability"]["distribution"][illness]["value"] for illness in illnesses]
                # Chuẩn hóa trọng số để tổng bằng 1
                total_weight = sum(weights)
                weights = [weight / total_weight for weight in weights]
                illness_type = random.choices(illnesses, weights=weights)[0]
                pedestrian = pedestrian_type(age, department, personality, illness_type)
                num_patients += 1
                if illness_type == "crutches":
                    num_crutches += 1
                elif illness_type == "sticks":
                    num_sticks += 1
                elif illness_type == "wheelchairs":
                    num_wheelchairs += 1
                elif illness_type == "blind":
                    num_blind += 1
            else:
                pedestrian = pedestrian_type(age, department, personality)
                num_visitors += 1

        if pedestrian.age < 11 and pedestrian.personality == "neurotic":
            continue

        if isinstance(pedestrian, Personnel):
            if pedestrian.age < 23 or pedestrian.age > 61:
                continue

        if personality == "open":
            num_openness += 1
        elif personality == "neurotic":
            num_neuroticism += 1

        pedestrians.append(pedestrian)

    print("Number of personnel:", num_personnel)
    print("Number of visitors:", num_visitors)
    print("Number of patients:", num_patients)
    print("Number of patients with crutches:", num_crutches)
    print("Number of patients with sticks:", num_sticks)
    print("Number of patients with wheelchairs:", num_wheelchairs)
    print("Number of blind patients:", num_blind)
    print("Number of people with openness:", num_openness)
    print("Number of people with neuroticism:", num_neuroticism)

    return pedestrians


def write_json_file(filename, data):
    with open(filename, "w") as json_file:
        json.dump([pedestrian.toJSON() for pedestrian in data], json_file, indent=4)


def main():
    with open("../../data/input.json", "r") as file:
        data = json.load(file)

    pedestrians = generate_pedestrians(data)

    write_json_file("outputEx3.json", pedestrians)


if __name__ == "__main__":
    main()
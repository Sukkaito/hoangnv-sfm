import json
import random


class Pedestrian:
    def __init__(self, age, personality):
        self.age = age
        self.personality = personality
        self.emotions = {
            "pleasure": 0.75,
            "surprise": 0.5,
            "anger": -0.2,
            "fear": -0.2,
            "hate": -0.4,
            "sad": -0.4
        }


class Patient(Pedestrian):
    def __init__(self, age, personality, status, department):
        super().__init__(age, personality)
        self.type = "Patient"
        self.status = status
        self.department = department

    def toJSON(self):
        return {
            "type": self.type,
            "age": self.age,
            "personality": self.personality,
            "emotions": self.emotions,
            "status": self.status,
            "department": self.department
        }


class Visitor(Pedestrian):
    def __init__(self, age, personality, status, department):
        super().__init__(age, personality)
        self.type = "Visitor"
        self.status = status
        self.department = department

    def toJSON(self):
        return {
            "type": self.type,
            "age": self.age,
            "personality": self.personality,
            "emotions": self.emotions,
            "status": self.status,
            "department": self.department
        }


class Personnel(Pedestrian):
    def __init__(self, age, personality, status, departments):
        super().__init__(age, personality)
        self.type = "Personnel"
        self.status = status
        self.departments = departments

    def toJSON(self):
        return {
            "type": self.type,
            "age": self.age,
            "personality": self.personality,
            "emotions": self.emotions,
            "status": self.status,
            "departments": self.departments
        }


def generate_pedestrians(data):
    pedestrians = []

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
    num_openness = 0
    num_neuroticism = 0

    while len(pedestrians) < num_agents:
        age = random.randint(data["ageDistribution"]["distribution"]["normal"]["minValue"], data["ageDistribution"]["distribution"]["normal"]["maxValue"])
        personality = random.choice(["open", "neurotic"])

        if num_neuroticism >= 0.53 * num_agents:
            personality = "open"

        if num_openness >= 0.53 * num_agents:
            personality = "neurotic"

        if len(pedestrians) < num_personnel:
            # Personnel
            status = random.choices(["noDisabilityNoOvertaking", "noDisabilityOvertaking"],
                                    weights=[data["walkability"]["distribution"]["noDisabilityNoOvertaking"]["value"], data["walkability"]["distribution"]["noDisabilityOvertaking"]["value"]])[0]
            departments_for_personnel = random.sample(departments, 3)  # Chọn ngẫu nhiên 3 khoa viện
            pedestrian = Personnel(age, personality, status, departments_for_personnel)
        else:
            pedestrian_type = random.choice([Patient, Visitor])
            department = random.choice(departments)
            if pedestrian_type == Patient:
                # Lấy danh sách các loại bệnh và trọng số tương ứng
                statuses = ["crutches", "sticks", "wheelchairs", "blind"]
                weights = [data["walkability"]["distribution"][status]["value"] for status in statuses]
                # Chuẩn hóa trọng số để tổng bằng 1
                total_weight = sum(weights)
                weights = [weight / total_weight for weight in weights]
                status = random.choices(statuses, weights=weights)[0]
                pedestrian = pedestrian_type(age, personality, status, department)
                num_patients += 1
                if status == "crutches":
                    num_crutches += 1
                elif status == "sticks":
                    num_sticks += 1
                elif status == "wheelchairs":
                    num_wheelchairs += 1
                elif status == "blind":
                    num_blind += 1
            else:
                status = random.choices(["noDisabilityNoOvertaking", "noDisabilityOvertaking"],
                                        weights=[data["walkability"]["distribution"]["noDisabilityNoOvertaking"]["value"], data["walkability"]["distribution"]["noDisabilityOvertaking"]["value"]])[0]
                pedestrian = pedestrian_type(age, personality, status, department)
                num_visitors += 1

        if pedestrian.age < 11 and pedestrian.status == "neurotic":
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
        json.dump(
            [pedestrian.toJSON() if hasattr(pedestrian, 'toJSON') else pedestrian.__dict__ for pedestrian in data],
            json_file, indent=4)


def main():
    with open("../../data/input.json", "r") as file:
        data = json.load(file)

    pedestrians = generate_pedestrians(data)

    write_json_file("outputEx3.json", pedestrians)


if __name__ == "__main__":
    main()

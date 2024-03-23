import json
import random

def generate_pedestrians(data):
    pedestrians = []

    num_agents = data["numOfAgents"]["value"]
    no_disability_percentage = data["walkability"]["distribution"]["noDisabilityNoOvertaking"]["value"] + data["walkability"]["distribution"]["noDisabilityOvertaking"]["value"]
    num_personnel = int(num_agents * (no_disability_percentage / 100))

    # Convert department keys to a list for random selection
    department_keys = list(data["wardDistribution"]["distribution"].keys())

    # Generate pedestrians
    for _ in range(num_agents):
        pedestrian = {
            "age": random.randint(11, 90),
            "openness": round(random.uniform(0.45, 0.55), 2),
            "neuroticism": round(random.uniform(0, 1), 2),
            "initial_emotions": {
                "pleasure": 0.75,
                "surprise": 0.5,
                "anger": -0.2,
                "fear": -0.2,
                "hate": -0.4,
                "sad": -0.4
            }
        }

        if len(pedestrians) < num_personnel:
            pedestrian["type"] = "Personnel"
            pedestrian["department"] = random.choice(department_keys)  # Select a department randomly
        else:
            pedestrian["type"] = random.choice(["Patient", "Visitor"])

        pedestrians.append(pedestrian)

    return pedestrians

def write_json_file(filename, data):
    with open(filename, "w") as json_file:
        json.dump(data, json_file, indent=4)

def main():
    # Load data from file
    with open("../../data/input.json", "r") as file:
        data = json.load(file)

    # Generate pedestrians
    pedestrians = generate_pedestrians(data)

    # Write output to JSON file
    write_json_file("outputEx3.json", pedestrians)

if __name__ == "__main__":
    main()

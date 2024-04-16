import json
import random
import numpy as np
import scipy.stats as stats

class Pedestrian:
    pedestrianCount = 0

    def __init__(self, age = 0, personality = [], journey = [], emotion = {}, start = 'A', end = 'A', velocity = 0, events = [],
     walkingTime = 0, distance = 0, impactOfAGV = [], tempPoints = (0,0)):
        self.ID = Pedestrian.pedestrianCount
        Pedestrian.pedestrianCount += 1
        self.start = start
        self.end = end
        self.journey = journey
        self.velocity = velocity
        self.personality = personality
        self.events = events
        self.walkingTime = walkingTime
        self.distance = distance
        self.age = age
        self.impactOfAGV = impactOfAGV
        self.tempPoints = tempPoints

        self.emotion = {
            "pleasure": 0.75,
            "surprise": 0.5,
            "anger": -0.2,
            "fear": -0.2,
            "hate": -0.4,
            "sad": -0.4
        }

class Patient(Pedestrian):
    def __init__(self, age, personality, walkability, journey, events):
        super().__init__(age=age, personality=personality, journey=journey, events=events)
        self.type = "Patient"
        self.walkability = walkability

class Visitor(Pedestrian):
    def __init__(self, age, personality, walkability, journey, events):
        super().__init__(age=age, personality=personality, journey=journey, events=events)
        self.type = "Visitor"
        self.walkability = walkability

class Personel(Pedestrian):
    def __init__(self, age, personality, walkability, journey, events):
        super().__init__(age=age, personality=personality, journey=journey, events=events)
        self.type = "Personel"
        self.walkability = walkability

class Event:
    def __init__(self, intensity = [], time = 0):
        self.intensity = intensity
        self.time = time

def generate_time(data) -> ([list, int]): #Return timeDistribution list and size of list
    n = data["timeBetweenEventsDistribution"]["distribution"]["normal"]["samples"] #n = 43
    k = data["timeBetweenEventsDistribution"]["distribution"]["normal"]["numberOfValues"] #k = 200
    min_value = data["timeBetweenEventsDistribution"]["distribution"]["normal"]["minValue"] #min_value = 100
    max_value = data["timeBetweenEventsDistribution"]["distribution"]["normal"]["maxValue"] #max_value = 3600

    mean = (min_value + max_value) / 2 #Mean
    std = (max_value - min_value) / 6 #Standard deviation, both can be modified
    while (True):
        sample = np.random.normal(mean, std, n) #Samples follow normal distribution
        sample = np.round(sample, 0) #Round to nearest whole

        stat, p_value = stats.shapiro(sample) # Calculate p_value

        alpha = 0.05 # Level of significant
        if p_value < alpha:
            continue #Retry until normal distribution is achieved
        else:
            return [sample.tolist(), n]

def generate_events(data) -> ([list, int]): #Return eventList and size of list
    n = data["eventDistribution"]["distribution"]["normal"]["samples"] #n = 43
    k = data["eventDistribution"]["distribution"]["normal"]["numberOfValues"] #k = 200
    min_value = data["eventDistribution"]["distribution"]["normal"]["minValue"] #min_value = -1
    max_value = data["eventDistribution"]["distribution"]["normal"]["maxValue"] #max_value = 1
    emo_type_count = data["eventDistribution"]["distribution"]["normal"]["numberOfFields"] # emo_type_count = 6
    
    mean = (min_value + max_value) / 2 #Mean
    std = (max_value - min_value) / 6 #Standard deviation, both can be modified

    allEvents = []

    i = 0
    while (i < emo_type_count): #6 types of emotion
        sample = np.random.normal(mean, std, n) #Samples follow normal distribution
        sample = np.round(sample, 1) #1 significant floating point
        
        stat, p_value = stats.shapiro(sample)  #Calculate p_value
        alpha = 0.05 #Level of significant
        if p_value < alpha:
            continue
        allEvents.append(sample)
        i += 1

    events = []

    #Standardize impact of events and convert 6xn -> nx6 array
    for i in range(0, n):
        if(allEvents[0][i] < 0):
            events.append([(-1)*abs(allEvents[j][i]) for j in range(0, emo_type_count) ])
        else:
            events.append([abs(allEvents[j][i]) for j in range(0, emo_type_count)])
    return [events, n]

def generate_pedestrians(data):
    pedestrians = []

    num_agents = data["numOfAgents"]["value"]
    num_noDisability = int(num_agents * (
            data["walkability"]["distribution"]["noDisabilityNoOvertaking"]["value"] +
            data["walkability"]["distribution"]["noDisabilityOvertaking"]["value"]) / 100)
    num_personel = int(random.uniform(0.8, 0.9) * num_noDisability)

    journeys = list(data["wardDistribution"]["distribution"].keys())[:-1]  # Exclude 'normal'
    journey_distribution = data["walkability"]["distribution"]["journeyDistribution"]["distribution"]
    for key in journey_distribution:
        if key != "forPersonel" and journey_distribution[key]["start"] in journeys:
            journeys.remove(journey_distribution[key]["start"])

    # num_patients = 0
    # num_visitors = 0
    # num_crutches = 0
    # num_sticks = 0
    # num_wheelchairs = 0
    # num_blind = 0
    num_openness = 0
    num_neuroticism = 0

    allEvents, eventCount = generate_events(data)
    allTimeDistances, timeDistancesCount = generate_time(data)

    while len(pedestrians) < num_agents:
        age = random.randint(data["ageDistribution"]["distribution"]["normal"]["minValue"],
                             data["ageDistribution"]["distribution"]["normal"]["maxValue"])

        if num_neuroticism >= 0.53 * num_agents:
            personality = "open"
            num_openness += 1
        elif num_openness >= 0.53 * num_agents:
            personality = "neurotic"
            num_neuroticism += 1
        else:
            personality = random.choice(["open", "neurotic"])
            if (personality == "open"): num_openness += 1
            else: num_neuroticism += 1 

        if len(pedestrians) < num_personel:
            # Personel
            walkability = random.choices(["noDisabilityNoOvertaking", "noDisabilityOvertaking"],
                                    weights=[data["walkability"]["distribution"]["noDisabilityNoOvertaking"]["value"],
                                             data["walkability"]["distribution"]["noDisabilityOvertaking"]["value"]])[0]
            journeyss = random.sample(journeys, 3)  # Chọn ngẫu nhiên 3 khoa viện
            pedestrian = Personel(age, personality, walkability, journeyss, [])
        elif len(pedestrians) < num_noDisability:
            # Visitor, assuming Visitor must be NoDisability
            walkability = random.choices(["noDisabilityNoOvertaking", "noDisabilityOvertaking"],
                                    weights=[data["walkability"]["distribution"]["noDisabilityNoOvertaking"]["value"],
                                             data["walkability"]["distribution"]["noDisabilityOvertaking"]["value"]])[0]
            journey = random.choice(journeys)
            pedestrian = Visitor(age, personality, walkability, journey, [])
            # num_visitors += 1
        else:
            # Patient
            journey = random.choice(journeys)
            # Lấy danh sách các loại bệnh và trọng số tương ứng
            statuses = ["crutches", "sticks", "wheelchairs", "blind"]
            weights = [data["walkability"]["distribution"][walkability]["value"] for walkability in statuses]
            # Chuẩn hóa trọng số để tổng bằng 1
            total_weight = sum(weights)
            weights = [weight / total_weight for weight in weights]
            walkability = random.choices(statuses, weights=weights)[0]
            pedestrian = Patient(age, personality, walkability, journey, [])
            # num_patients += 1
            # if status == "crutches":
            #     num_crutches += 1
            # elif status == "sticks":
            #     num_sticks += 1
            # elif status == "wheelchairs":
            #     num_wheelchairs += 1
            # elif status == "blind":
            #     num_blind += 1

        if pedestrian.age < 11 and pedestrian.walkability == "neurotic":
            continue

        if isinstance(pedestrian, Personel):
            if pedestrian.age < 23 or pedestrian.age > 61:
                continue

        for i in range(20):
            eventID = random.randint(0, eventCount - 1)
            timeDistancesID = random.randint(0, timeDistancesCount - 1)
            pedestrian.events.append(Event(allEvents[eventID], allTimeDistances[timeDistancesID]))
        pedestrians.append(pedestrian)

    # print("Number of personel:", num_personel)
    # print("Number of visitors:", num_visitors)
    # print("Number of patients:", num_patients)
    # print("Number of patients with crutches:", num_crutches)
    # print("Number of patients with sticks:", num_sticks)
    # print("Number of patients with wheelchairs:", num_wheelchairs)
    # print("Number of blind patients:", num_blind)
    # print("Number of people with openness:", num_openness)
    # print("Number of people with neuroticism:", num_neuroticism)

    return pedestrians


def write_json_file(filename, data: list):
    with open(filename, "w") as json_file:
        json.dump(
            data,
            json_file, indent=4,
            default=lambda x: x.__dict__)


def main():
    with open("../../data/input.json", "r") as file:
        data = json.load(file)

    pedestrians = generate_pedestrians(data)

    write_json_file("../../data/Pedestrian.json", pedestrians)


if __name__ == "__main__":
    main()

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

def generate_time(data) -> list[list, int]: #Return timeDistribution list and size of list
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

def generate_events(data) -> list[list, int]: #Return eventList and size of list
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

def generate_ages(data) -> list[list, int]: #Return ageList and size of list
    # n = data["ageDistribution"]["distribution"]["normal"]["samples"] # Using jsonref
    n = data["numOfAgents"]["value"] #n = numOfAgents
    k = data["ageDistribution"]["distribution"]["normal"]["numberOfValues"]
    min_value = data["ageDistribution"]["distribution"]["normal"]["minValue"] # min_value = 5
    max_value = data["ageDistribution"]["distribution"]["normal"]["maxValue"] # max_value = 104

    mean = (min_value + max_value) / 2 # Mean
    std = (max_value - min_value) / 6 # Standard deviation
    while (True):
        sample = np.random.normal(mean, std, n) #Samples follow normal distribution
        sample = np.clip(sample, min_value, max_value) # Value trimming
        sample = np.round(sample, 1)

        stat, p_value = stats.kstest(sample, 'norm', args=(mean, std)) # Calc p_value

        alpha = 0.05 # Level of significant
        if p_value < alpha:
            continue
        else:
            f = lambda x: ((x >= 23) & (x <= 61)) #Personels' age range: 23 <= x <= 61
            cond = f(sample)
            sample = np.concatenate((np.extract(~cond, sample), np.extract(cond, sample)))
            #Put special value of age LAST, prioritize Personels' age in this case
            return [sample.tolist(), n]

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

    num_openness = 0
    num_neuroticism = 0

    allEvents, eventCount = generate_events(data)
    allTimeDistances, timeDistancesCount = generate_time(data)
    allAge, ageCount = generate_ages(data) # Prioritize Personel first

    #Prioritize order: Personel > Visitor > Patient
    while len(pedestrians) < num_agents:
        age = allAge.pop() # Prioritize Personel first by popping LAST value

        if (num_neuroticism >= 0.53 * num_agents) | (age < 11): #Age < 11 must be "open" personality
            personality = "open"
            num_openness += 1
        elif num_openness >= 0.53 * num_agents:
            personality = "neurotic"
            num_neuroticism += 1
        else:
            personality = random.choice(["open", "neurotic"])
            if (personality == "open"): num_openness += 1
            else: num_neuroticism += 1

        if (num_personel > 0) & (age >= 23) & (age <= 61): #Age outside 23 - 61 can't be Personel
            # Personel
            walkability = random.choices(["noDisabilityNoOvertaking", "noDisabilityOvertaking"],
                                    weights=[data["walkability"]["distribution"]["noDisabilityNoOvertaking"]["value"],
                                             data["walkability"]["distribution"]["noDisabilityOvertaking"]["value"]])[0]
            journeyss = random.sample(journeys, 3)  # Chọn ngẫu nhiên 3 khoa viện
            pedestrian = Personel(age, personality, walkability, journeyss, [])
            num_personel -= 1
            num_noDisability -= 1
        elif (num_noDisability > 0):
            # Visitor, assuming Visitor must be NoDisability
            walkability = random.choices(["noDisabilityNoOvertaking", "noDisabilityOvertaking"],
                                    weights=[data["walkability"]["distribution"]["noDisabilityNoOvertaking"]["value"],
                                             data["walkability"]["distribution"]["noDisabilityOvertaking"]["value"]])[0]
            journey = random.choice(journeys)
            pedestrian = Visitor(age, personality, walkability, journey, [])
            num_noDisability -= 1
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

        for i in range(20):
            eventID = random.randint(0, eventCount - 1)
            timeDistancesID = random.randint(0, timeDistancesCount - 1)
            pedestrian.events.append(Event(allEvents[eventID], allTimeDistances[timeDistancesID]))
        pedestrians.append(pedestrian)

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

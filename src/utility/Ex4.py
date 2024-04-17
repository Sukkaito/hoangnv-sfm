import numpy as np
import scipy.stats as stats
import json
jsonfile=open('data\input.json','r')
readfile=jsonfile.read()
data=json.loads(readfile)
ward1=data["wardDistribution"].get("distribution")
ward=[]
for each in ward1:
    ward.append(each)
ward.pop()
#doc du lieu triple tu Pedestrian.json
triple=0
n=data["numOfAgents"].get("value")
jsonfile2=open('data\Pedestrian.json','r')
readfile2=jsonfile2.read()
data2=json.loads(readfile2)
for each in data2:
    if each["type"]=="Personel":
        triple+=1
single=n-triple
print(triple)
#sinh du lieu
max_value=n-len(ward)*3
min_value=1
mean=(max_value+min_value)/2
std_dev=(max_value-min_value)/6
alpha=0.05
while True:
    sample=np.random.normal(mean,std_dev,len(ward))
    sample=np.round(sample,0)
    stat,p_value=stats.shapiro(sample)
    if p_value>=alpha:
        if sum(sample)==triple*3+single and all(i>0 for i in sample):
            break
print(sample)
#ghi ra json
pair=dict(zip(ward,sample))
with open ('data\Ward.json','w') as outjson:
    json.dump(pair,outjson,indent=4)
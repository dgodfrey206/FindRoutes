__author__ = 'vka'

import json
import pprint

def createTempDB(routeID):
    #create temporary database, containing data about one route

    with open('db.json', encoding='utf-8') as f:
        db = json.load(f)

    pp = pprint.PrettyPrinter(indent = 2)

    newDB = {
        'routes': [],
        'stops': [],
        'trips': [],
        'services': [],
        'stop_times': [],
    }

    newDB['services'] = db['services'].copy()

    for r in db['routes']:
        if r['id'] == routeID:
            newDB['routes'].append(r.copy())
            break

    for trip in db['trips']:
        if trip['route_id'] == routeID:
            newDB['trips'].append(trip.copy())

    for stop in db['stops']:
        for t in newDB['trips']:
            if stop['id'] in t['stop_sec']:
                newDB['stops'].append(stop.copy())
                break

    for time in db['stop_times']:
        if time['trip_id'] in [t['id'] for t in newDB['trips']]:
            newDB['stop_times'].append(time.copy())

    with open('temp.json', 'w') as f:
        json.dump(newDB, f, indent=2)

def reformat():
    with open('temp.json', encoding='utf-8') as f:
        db = json.load(f)

    pp = pprint.PrettyPrinter(indent = 2)
    #pp.pprint(db)

    stopSchedule = {}
    for s in db['stops']:
        stopSchedule[s['id']] = []

    for t in db['stop_times']:
        if t['service_id'] == 0 and t['trip_id'] == db['trips'][0]['id']: #todo
            stopSchedule[t['stop_id']].append(t['name'])

    for k, e in stopSchedule.items():
        stopSchedule[k] = sorted(e)

    pp.pprint(stopSchedule)

    nums = {}
    for key, schedule in stopSchedule.items():
        nums[key] = len(schedule)

    pp.pprint(nums)



def getNextGreater(val, sec):
    #sec must be sorted
    for el in sec:
        if el < sec:
            return el

    return None

if __name__ == '__main__':
    createTempDB(0)
    reformat()
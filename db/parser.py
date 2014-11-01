__author__ = 'vka'

import pickle
import json
from bs4 import BeautifulSoup
import pprint

def parser():

    pp = pprint.PrettyPrinter(indent=4)

    with open('db.pickle', 'rb') as f:
        db = pickle.load(f)

    with open('stops.xml', 'r', encoding='utf-8') as f:
        geo = str(f.readlines())
        geo = BeautifulSoup(geo)

    markers = geo.find_all('marker')
    total = len(markers)
    stats = { 'found': 0, 'nfound': 0 }


    total = len(markers)
    stats = { 'found': 0, 'nfound': 0 }
    nfounds = []

    #print(' {: <55}{: >6.8} {: >9.8}{: >5}'.format('Stop name', 'Longtitude', 'Latitude', 'Found'))

    for e in db['stops']:
        found = False

        for m in markers:
            if e['name'] == m['name']:
                found = True
                stats['found'] += 1

                e['lng'] = m['lng']
                e['lat'] = m['lat']

                break
        else:
            stats['nfound'] += 1
            nfounds.append(e.copy())

    #    print(' {: <55}{: >6.8} {: >9.8}{: >5}'.format(m['name'][:53], m['lng'], m['lat'], found))

    #print()
    #print('{: >10}{: >10}{: >10}'.format('Total', 'Found', 'Not found').rjust(79))
    #print('{: >10}{: >10}{: >10}'.format(total, stats['found'], stats['nfound']).rjust(79))

    #print('\nNot found')
    #for e in nfounds:
    #    print(' ' + e['name'])

    #with open('db.json', 'w') as f:
    #    json.dump(db, f, indent=2)

    #print('\nFile saved as db.json')

    routeID = 0
    routeTrips = []
    routeTripsIds = []
    for t in db['trips']:
        if t['route_id'] == routeID:
            routeTrips.append(t.copy())
            routeTripsIds.append(t['id'])

    #pp.pprint(routeTrips)

    routeStopTimes = []

    for s in db['stop_times']:
        if s['trip_id'] in routeTripsIds:
            routeStopTimes.append(s.copy())

    #pp.pprint(routeStopTimes)

    sequences = []
    seq_id = 0
    '''
    sequence:
        seq_id:
        trip_id:
        service_id:
        seq: [stop_time]
    '''
    lastKnownStopId = None
    lastKnownTripID = None
    curID = -1
    for el in routeStopTimes:
        if lastKnownStopId is not el['stop_id'] or lastKnownTripID is not el['trip_id']:
            curID = 0
            lastKnownStopId = el['stop_id']
            lastKnownTripID = el['trip_id']
        else:
            curID += 1

        for t in routeTrips:
            if t['id'] == el['trip_id']:
                trip = t.copy()
                break

        firstStop = el['stop_id'] == t['stop_sec'][0]

        if firstStop:
            sequences.append({
                'seq_id': seq_id,
                'trip_id': trip['id'],
                'service_id': el['service_id'],
                'seq': []
            })
            seq_id += 1
        try:
            sequences[curID]['seq'].append(el['name'])
        except:
            pp.pprint(sequences)
            pp.pprint(el)
            break


if __name__ == '__main__':
    parser()
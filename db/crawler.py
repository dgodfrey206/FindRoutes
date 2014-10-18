from pprint import PrettyPrinter
import os
import re
from bs4 import BeautifulSoup
import pickle

__author__ = 'vka'


def crawler():
    root = 'rozklady.krakow/aktualne'

    database = {
        'routes': [],
        'stops': [],
        'trips': [],
        'services': [],
        'iters': None
    }
    '''
    stops:
        id:
        name:
        lon:
        lat:
    routes:
        id:
        name:
    trips:
        id:
        route_id:
        name:
        stop_sec: [stop:id]
    services:
        id:
        name: WORKDAYS/SATURDAYS/SUNDAYS
    iters:
        route:
        stop:
        trip:
        service:
    '''
    database['iters'] = {
        'route': 0,
        'stop': 0,
        'trip': 0,
        'service': 0
    }

    database['services'].append(
        {
            'id': database['iters']['service'],
            'name': 'workdays'
        }
    )
    database['iters']['service'] += 1

    database['services'].append(
        {
            'id': database['iters']['service'],
            'name': 'saturdays'
        }
    )
    database['iters']['service'] += 1

    database['services'].append(
        {
            'id': database['iters']['service'],
            'name': 'sundays'
        }
    )
    database['iters']['service'] += 1

    dirs = sorted(os.listdir(root))
    for dir in dirs: #dir contanis one route data
        if not is_number(dir):
            debug("Skipped file " + dir)
            continue #skip not matching files
        currenturl = root + os.sep + dir

        debug("Working on dir " + currenturl)

        files = sorted(os.listdir(currenturl))

        startStop = None #checked so we can notice if direction has changed
        currentTripId = None

        # we are only interested if files: _num_t_num_.htm, containing
        # route data for one stop
        for file in files:
            fullurl = currenturl + os.sep + file

            if re.match(r'\d{3,4}t\d{3,4}.htm', file):
                debug(' Matched file ' + fullurl)

                with open(fullurl, encoding="iso-8859-2") as f:
                    debug('  Opened file ' + file)
                    html = str(f.readlines())

                soup = BeautifulSoup(html)

                route = soup.find('font', {'class': 'fontline'}).text
                stop = soup.find('font', {'class': 'fontstop'}).text
                fullline = soup.find('font', {'class': 'fontroute'}).text
                firstStop = fullline.split('-')[0]

                debug('   Route: ' + route)
                debug('   Stop: ' + stop)
                debug('   First stop: ' + firstStop)

                #add route to db if necessary
                curRouteID = getIdWhereName(route, database['routes'])
                if not curRouteID:
                    database['routes'].append(
                        {
                            'id': database['iters']['route'],
                            'name': str(route)
                        }
                    )
                    curRouteID = database['iters']['route']
                    database['iters']['route'] += 1

                    debug("    Added route " + route + " to db")

                 #add stop to db if necessary
                curStopID = getIdWhereName(stop, database['stops'])
                if not curStopID:
                    database['stops'].append(
                        {
                            'id': database['iters']['stop'],
                            'name': str(stop)
                        }
                    )
                    curStopID = database['iters']['stop']
                    database['iters']['stop'] += 1

                    debug("    Added stop " + stop + " to db")

                if startStop != firstStop:
                    #first file for route opened or dir has changed
                    startStop = firstStop

                    currentTripId = database['iters']['trip']
                    database['trips'].append(
                        {
                            'id': database['iters']['trip'],
                            'route_id': curRouteID,
                            'name': 'Trip' + str(currentTripId),
                            'stop_sec': []
                        }
                    )
                    database['iters']['trip'] += 1
                    debug('    Added trip to db')

                #append stop to trip
                database['trips'][currentTripId]['stop_sec'].append(curStopID)

            else:
                debug(' Skipped file ' + fullurl)
        
    debug(database)

    #binary write database to file
    with open('db.pickle', 'wb') as f:
        pickle.dump(database, f)

def getIdWhereName(name, array):
    if array is None:
        return None

    for el in array:
        if el['name'] == name:
            return el['id']

    return None

def is_number(s):
    try:
        int(s)
        return True
    except ValueError:
        return False

def debug(msg):
    pp = PrettyPrinter(indent=4)

    #todo
    if isinstance(msg, str):
        print(msg)
    else:
        pp.pprint(msg)
if __name__ == '__main__':
    crawler()
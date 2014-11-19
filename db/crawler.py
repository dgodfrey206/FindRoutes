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
        'stop_times': [],
        'iters': None
    }
    '''
    stops:
        id:
        name:
        lon:
        lat:
        p: #value inherited from html, used for connecting routes to proper stops
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
    stop_times:
        id:
        stop_id:
        trip_id:
        service_id:
        name: (time)
    iters:
        route:
        stop:
        trip:
        service:
        stop_times:
    '''
    database['iters'] = {
        'route': 0,
        'stop': 0,
        'trip': 0,
        'service': 0,
        'stop_times': 0
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

    #load stops to database
    stopsPath = root + "/przystan.htm"

    with open(stopsPath, encoding="iso-8859-2") as f:
        debug('  Opened file ' + stopsPath)
        html = str(f.readlines())
    soup = BeautifulSoup(html)

    for stop in soup.find_all("li"):
        txt = stop.find('a')['href']
        number = re.findall(r'\d+', txt)[0]
        name = stop.text
        database['stops'].append(
            {
                'id': database['iters']['stop'],
                'name': str(name),
                'p': number
            }
        )
        database['iters']['stop'] += 1
        debug("    Added stop " + name + " to db")

    dirs = sorted(os.listdir(root))

    for dir in dirs:
        if not is_number(dir):
            debug("Skipped file " + dir)
            continue #skip not matching files

        #add route to database
        database['routes'].append(
            {
                'id': database['iters']['route'],
                'name': dir
            }
        )
        curRouteID = database['iters']['route']
        database['iters']['route'] += 1

        debug("    Added route " + dir + " to db")



        currenturl = root + os.sep + dir
        debug("Working on dir " + currenturl)

        files = sorted(os.listdir(currenturl))

        directions = []
        #match only files in format: _route_/_route_w_direction.htm
        for f in files:
            if re.match(r'\d{3,4}w\d{3,4}.htm', f):
                directions.append(f)

        tripID = 0

        for direction in directions:
            fullpath = currenturl + os.sep + direction

            with open(fullpath, encoding="iso-8859-2") as f:
                debug('  Opened file ' + fullpath)
                html = str(f.readlines())

            soup = BeautifulSoup(html)


            #create trip for route
            database['trips'].append(
                {
                    'id': database['iters']['trip'],
                    'route_id': curRouteID,
                    'name': 'Trip' + str(curRouteID) + '-' + str(tripID),
                    'stop_sec': []
                }
            )
            currentTripID = database['iters']['trip']
            database['iters']['trip'] += 1
            debug('    Added trip to db')


            stops = soup.find_all('li')
            visitedStops = []

            for s in stops:
                stopName = s.text
                stopPVal = s.find_all('a')

                if len(stopPVal) == 3: #normal stop
                    stopPVal = re.findall(r'\d+', stopPVal[2]['href'])[0]

                    found, stopID = getIdWhereParam('p', stopPVal, database['stops'])

                    if not found:
                        debug('Stop was not found by p value, aborting.')

                    if stopID not in database['trips'][currentTripID]['stop_sec']:
                        database['trips'][currentTripID]['stop_sec'].append(stopID)
                    else:
                        continue

                elif len(stopPVal) == 0:
                    #last stop

                    if stopName.endswith('(NŻ) - na żądanie'):
                        stopName = stopName.split('(NŻ) - na żądanie')[0]

                    if stopName.endswith('  NŻ'):
                        stopName = stopName.split('  NŻ')[0]

                    if stopName.endswith(' -- GRANICA TARYF.'):
                        stopName = stopName.split(' -- GRANICA TARYF.')[0]


                    found, stopID = getIdWhereName(stopName, database['stops'])

                    if not found:
                        debug(['Last stop was not found by name, aborting.', stopName])
                        debug(database)

                        return

                    if stopID not in database['trips'][currentTripID]['stop_sec']:
                        database['trips'][currentTripID]['stop_sec'].append(stopID)
                    break


                #manage stop times
                stopFile = root + os.sep + dir + os.sep + s.find_all('a', {'target': 'R'})[0]['href']

                with open(stopFile, encoding="iso-8859-2") as f:
                    debug('  Opened file ' + stopFile)
                    html = str(f.readlines())
                stopTimesSoup = BeautifulSoup(html)

                timetable = stopTimesSoup.find('td', {'class': 'celldepart'})
                trs = timetable.find_all('tr', {'align': None})#skip first, as it contains only headlines

                for row in trs:
                    try:
                        hour = row.find('td', {'class', 'cellhour'}).text
                        tds = row.find_all('td', {'class': 'cellmin'})

                    except AttributeError:
                        continue #wrong row

                    service_id = 0
                    for serviceMinutes in tds:
                        minutes = serviceMinutes.text[1:] #skip first char: ' '
                        minutes = minutes.split()
                        for el in minutes:
                            if el == '-':
                                continue

                            database['stop_times'].append({
                                'id': database['iters']['stop_times'],
                                'stop_id': stopID,
                                'trip_id': currentTripID,
                                'service_id': service_id,
                                'name': '{:0>2}:{}'.format(hour, el)
                            })

                            database['iters']['stop_times'] += 1

                        service_id += 1
                debug('    Added stop times for route and stop')

            tripID += 1
            if tripID == 2:
                #behave like nothing else can happen
                break


    #debug('\n\n****Entire database****')
    #debug(database)

    #binary write database to file
    with open('db.pickle', 'wb') as f:
        pickle.dump(database, f)

def getIdWhereName(name, array):
    return getIdWhereParam('name', name, array)

def getIdWhereParam(param, value, array):
    if array is None:
        return False, None

    for el in array:
        if el[param] == str(value):
            return True, el['id']

    return False, None

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
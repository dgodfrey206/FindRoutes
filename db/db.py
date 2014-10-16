from bs4 import BeautifulSoup
import pprint
import zipfile
import os

def main():
    # agency
    agency = getAgency()

    #dummy calendar
    calendar = getCalendar()

    #stops
    stops = getStops()

    #routes
    routes = getRoutes()

    #trips
    trips = getTrips(routes, calendar)

    #stop_times
    stop_times = getStopTipes()
    try:
        os.mkdir('tmp')
    except FileExistsError:
        pass #folder already exists

    createTxtFile("agency.txt", agency)
    createTxtFile("stops.txt", stops)
    createTxtFile("routes.txt", routes)
    createTxtFile("trips.txt", trips)
    createTxtFile("calendar.txt", calendar)
    createTxtFile("stop_times.txt", stop_times)

    with zipfile.ZipFile('db.zip', 'w') as zip:
        for file in ['agency.txt', 'stops.txt', 'routes.txt', 'trips.txt', 'calendar.txt', 'stop_times.txt']:
            try:
                zip.write(file)
                os.remove(file)
            except FileNotFoundError:
                pass #no such file, skip


def getAgency():
    agency = []
    agency.append({
        "agency_name": "MPK Kraków",
        "agency_url": "http://rozklady.mpk.krakow.pl/",
        "agency_timezone": "PL"
    })
    return agency

def getCalendar():
    calendar = []
    id = 1

    calendar.append({
        "service_id": "Service" + str(id),
        "monday": str(1),
        "tuesday": str(1),
        "wednesday": str(1),
        "thursday": str(1),
        "friday": str(1),
        "saturday": str(0),
        "sunday": str(0),
        "start_date": str(20000101),
        "end_date": str(20991231)
    })
    id += 1
    calendar.append({
        "service_id": "Service" + str(id),
        "monday": str(0),
        "tuesday": str(0),
        "wednesday": str(0),
        "thursday": str(0),
        "friday": str(0),
        "saturday": str(1),
        "sunday": str(0),
        "start_date": str(20000101),
        "end_date": str(20991231)
    })
    id += 1
    calendar.append({
        "service_id": "Service" + str(id),
        "monday": str(0),
        "tuesday": str(0),
        "wednesday": str(0),
        "thursday": str(0),
        "friday": str(0),
        "saturday": str(0),
        "sunday": str(1),
        "start_date": str(20000101),
        "end_date": str(20991231)
    })

    return calendar

def getStops():
    stops = []
    url = "rozklady.krakow/aktualne/przystan.htm"
    with open(url, encoding="iso-8859-2") as file:
        html = file.readlines()
        soup = BeautifulSoup(str(html))

        stopID = 1
        for el in soup.find_all("li"):
            stops.append(
                {"stop_name": el.text,
                 "href": el.find("a")['href'],
                 "stop_id": "Stop" + str(stopID),
                 "stop_lat": str(0),
                 "stop_lon": str(0)
                }
            )
            stopID += 1

    return stops

def getRoutes():
    routes = []
    url = "rozklady.krakow/linie.aspx"
    with open(url, encoding="iso-8859-2") as file:
        html = file.readlines()
        soup = BeautifulSoup(str(html))

        # first 3 tables are trams, rest are buses
        tableID = 1
        routeID = 1
        for el in soup.find_all("td"):
            for e in el.find_all("a"):
                text = e.text

                if not is_number(text):
                    continue  #only numeric routes are allowed

                href = e['href']
                if tableID <= 3:
                    type = 0  #tram
                else:
                    type = 3  #bus
                routes.append(
                    {
                        "route_id": "Route" + str(routeID),
                        "route_short_name": text,
                        "route_long_name": text,
                        "route_type": str(type),
                        "href": href
                    }
                )
                routeID += 1

            tableID += 1

    return routes

def getTrips(routes, calendar):
    trips = []

    url = "rozklady.krakow/aktualne/{:0>4}/{:0>4}w{:0>3}.htm"
    url2 = "rozklady.krakow/aktualne/{:0>4}/{}"
    for route in routes:
        dir = 1
        id = route['route_short_name']

        while (True):
            try:
                u = url.format(id, id, dir)
                with open(u, encoding="iso-8859-2") as file:
                    html = file.readlines()
                    soup = BeautifulSoup(str(html))

                    u2 = url2.format(id, soup.find("table").find_all("a")[1]["href"])

                    with open(u2, encoding="iso-8859-2") as file2:
                        html2 = file2.readlines()
                        soup2 = BeautifulSoup(str(html2))

                    commondays = False
                    saturdays = False
                    sundays = False

                    rows = soup2.find_all("tr")

                    for row in rows:
                        cellid = 0
                        cells = row.find_all("td")
                        for cell in cells[1::2]:
                            if cell.text != "-":
                                if cellid == 0:
                                    commondays = True
                                elif cellid == 1:
                                    saturdays = True
                                elif cellid == 2:
                                    sundays = True
                            cellid += 1

                        if commondays and saturdays and sundays:
                            break  # no need to search further

                    if commondays:
                        trips.append({
                            "route_id": route['route_id'],
                            "service_id": calendar[0]['service_id'],
                            "trip_id": route['route_id'] + calendar[0]['service_id'] + "Trip" + str(dir),
                            "url": u
                        })

                    if saturdays:
                        trips.append({
                            "route_id": route['route_id'],
                            "service_id": calendar[1]['service_id'],
                            "trip_id": route['route_id'] + calendar[1]['service_id'] + "Trip" + str(dir),
                            "url": u
                        })

                    if sundays:
                        trips.append({
                            "route_id": route['route_id'],
                            "service_id": calendar[2]['service_id'],
                            "trip_id": route['route_id'] + calendar[2]['service_id'] + "Trip" + str(dir),
                            "url": u
                        })
                # todo
                dir += 1

            except FileNotFoundError:
                # no more directions remaining
                break
    return trips

def getStopTipes():
    return None

def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        return False

def createTxtFile(filename, array):

    if array is None:
        return

    if filename == 'agency.txt':
        keys = ['agency_name', 'agency_url', 'agency_timezone']
    elif filename == 'stops.txt':
        keys = ['stop_id', 'stop_name', 'stop_lat' ,'stop_lon']
    elif filename == 'routes.txt':
        keys = ['route_id', 'route_short_name', 'route_long_name', 'route_type']
    elif filename == 'trips.txt':
        keys = ['route_id', 'service_id', 'trip_id']
    elif filename == 'calendar.txt':
        keys = ['service_id', 'monday', 'tuesday', 'wednesday', 'thursday',
                'friday', 'saturday', 'sunday', 'start_date', 'end_date']
    elif filename == 'stop_times.txt':
        keys = ['trip_id', 'arrival_time', 'departure_time', 'stop_id', 'stop_sequence']

    else:
        return

    with open(filename, "w") as f:
            f.write(','.join(keys) + '\n')

            for s in array:
                txt = ''
                for k in keys:
                    txt += s[k] + ','
                f.write(txt[:-1] + '\n')

def createZipFromTxts(filename):
    pass
if __name__ == "__main__":
    main()

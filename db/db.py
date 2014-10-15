from bs4 import BeautifulSoup
import pprint

def main():

    #agency
    agency = getAgency()

    #dummy calendar
    calendar = getCalendar()

    #stops
    stops = getStops()

    #routes
    routes = getRoutes()

    #trips
    trips = getTrips(routes, calendar)

    pp = pprint.PrettyPrinter(indent=4)
    #pp.pprint(agency)
    #pp.pprint(stops)
    #pp.pprint(routes)
    #pp.pprint(trips)

def getAgency():
    return {
        "agency_name": "MPK Kraków",
        "agency_url": "http://rozklady.mpk.krakow.pl/",
        "agency_timezone": "PL"
    }

def getCalendar():
    calendar = []
    id = 1
    calendar.append({
        "service_id": "Service" + str(id),
        "monday": 1,
        "tuesday": 1,
        "wednesday": 1,
        "thursday": 1,
        "friday": 1,
        "saturday": 1,
        "sunday": 1,
        "start_date": 20000101,
        "end_date": 20991231
    })
    id += 1
    calendar.append({
        "service_id": "Service" + str(id),
        "monday": 1,
        "tuesday": 1,
        "wednesday": 1,
        "thursday": 1,
        "friday": 1,
        "saturday": 0,
        "sunday": 0,
        "start_date": 20000101,
        "end_date": 20991231
    })
    id += 1
    calendar.append({
        "service_id": "Service" + str(id),
        "monday": 0,
        "tuesday": 0,
        "wednesday": 0,
        "thursday": 0,
        "friday": 0,
        "saturday": 1,
        "sunday": 0,
        "start_date": 20000101,
        "end_date": 20991231
    })
    id += 1
    calendar.append({
        "service_id": "Service" + str(id),
        "monday": 0,
        "tuesday": 0,
        "wednesday": 0,
        "thursday": 0,
        "friday": 0,
        "saturday": 0,
        "sunday": 1,
        "start_date": 20000101,
        "end_date": 20991231
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
                { "stop_name": el.text,
                  "href": el.find("a")['href'],
                  "stop_id": "Stop" + str(stopID),
                  "stop_lat": 0,
                  "stop_lon": 0
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

        #first 3 tables are trams, rest are buses
        tableID = 1
        routeID = 1
        for el in soup.find_all("td"):
            for e in el.find_all("a"):
                text = e.text

                if not is_number(text):
                    continue #only numeric routes are allowed

                href = e['href']
                if tableID <= 3:
                    type = 0 #tram
                else:
                    type = 3 #bus
                routes.append(
                    {
                        "route_id": "Route" + str(routeID),
                        "route_short_name": text,
                        "route_long_name": text,
                        "route_type": type,
                        "href": href
                    }
                )
                routeID += 1

            tableID += 1

    return routes

def getTrips(routes, calendar):
    trips = []

    url = "rozklady.krakow/aktualne/{:0>4}/{:0>4}w{:0>3}.htm"

    for route in routes:
        dir = 1
        id = route['route_short_name']
        print(route)

        while(True):
            try:
                with open(url.format(id, id, dir), encoding="iso-8859-2") as file:
                    pass
                    # trips.append({
                    #     "route_id",: route['route_id'],
                    #     "service_id":
                    #
                    # })
                # todo

            except FileNotFoundError:
                #no more directions remaining
                break
            break
        break

def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        return False

if __name__ == "__main__":
    main()

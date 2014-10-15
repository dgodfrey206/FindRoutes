from bs4 import BeautifulSoup

def main():

    #agency
    agency = getAgency()

    #stops
    stops = getStops()

    #routes
    routes = getRoutes()


    #print(agency)
    print(stops)
    #print(routes)

def getAgency():
    return {
        "agency_name": "MPK Kraków",
        "agency_url": "http://rozklady.mpk.krakow.pl/",
        "agency_timezone": "PL"
    }

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
                  "stop_id": stopID,
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
                href = e['href']
                if tableID <= 3:
                    type = 0 #tram
                else:
                    type = 3 #bus
                routes.append(
                    {
                        "route_id": routeID,
                        "route_short_name": text,
                        "route_long_name": text,
                        "route_type": type
                    }
                )
                routeID += 1

            tableID += 1

    return routes

if __name__ == "__main__":
    main()

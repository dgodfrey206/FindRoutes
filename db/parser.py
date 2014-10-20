__author__ = 'vka'

import pickle
import json
from bs4 import BeautifulSoup
import pprint

if __name__ == '__main__':
    pp = pprint.PrettyPrinter(indent=4)

    with open('db.pickle', 'rb') as f:
        db = pickle.load(f)
        #json.dump(p, open('db.json', 'w'), indent=2)

    with open('stops.xml', 'r', encoding='utf-8') as f:
        geo = str(f.readlines())
        geo = BeautifulSoup(geo)

    markers = geo.find_all('marker')
    total = len(markers)
    stats = { 'found': 0, 'nfound': 0 }

    # for m in markers:
    #     found = False
    #     for e in db['stops']:
    #         if e['name'] == m['name']:
    #             found = True
    #             stats['found'] += 1
    #             break
    #     else:
    #         stats['nfound'] += 1
    #
    #     print(' {: <55}{: >6.8} {: >9.8}{: >5}'.format(m['name'][:53], m['lng'], m['lat'], found))
    #
    # print()
    # print('{: >10}{: >10}{: >10}'.format('Total', 'Found', 'Not found').rjust(79))
    # print('{: >10}{: >10}{: >10}'.format(total, stats['found'], stats['nfound']).rjust(79))


    total = len(markers)
    stats = { 'found': 0, 'nfound': 0 }
    nfounds = []

    print(' {: <55}{: >6.8} {: >9.8}{: >5}'.format('Stop name', 'Longtitude', 'Latitude', 'Found'))

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

        print(' {: <55}{: >6.8} {: >9.8}{: >5}'.format(m['name'][:53], m['lng'], m['lat'], found))

    print()
    print('{: >10}{: >10}{: >10}'.format('Total', 'Found', 'Not found').rjust(79))
    print('{: >10}{: >10}{: >10}'.format(total, stats['found'], stats['nfound']).rjust(79))

    print('\nNot found')
    for e in nfounds:
        print(' ' + e['name'])

    with open('db.json', 'w') as f:
        json.dump(db, f, indent=2)

    print('\nFile saved as db.json')
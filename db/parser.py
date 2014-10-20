__author__ = 'vka'

import pickle
import json

if __name__ == '__main__':
    with open('db.pickle', 'rb') as f:
        p = pickle.load(f)
        json.dump(p, open('db.json', 'w'))

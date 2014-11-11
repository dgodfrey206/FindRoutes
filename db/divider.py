__author__ = 'vka'
import json

with open('db.json', encoding='utf-8') as f:
        db = json.load(f)

keys = list(db.keys())

for k in keys:
    with open('json/' + k + '.json', 'w') as f:
        json.dump(db[k], f, indent=2)

import matplotlib.pyplot as plt

data = {'w': [], 'p': [], 'b': []}

with open('data/save', 'r') as f:
	for line in f:
		weight, punishment, best = line.split()
		data['w'].append(weight)
		data['p'].append(punishment)
		data['b'].append(best)

time = range(len(data['w']))

plt.plot(time, data['w'], 'r', label='wagi')
plt.plot(time, data['p'], 'g', label='kara')
plt.plot(time, data['b'], 'b', label='najlepsze')
plt.legend()
plt.xlabel('Iteracja')
plt.ylabel('Wartosci')
plt.axis([0, len(time), 0, 200])
plt.show()

import matplotlib.pyplot as plt
import os

# data = {'w': [], 'p': [], 'b': []}
#
# with open('data/save', 'r') as f:
# 	for line in f:
# 		weight, punishment, best = line.split()
# 		data['w'].append(weight)
# 		data['p'].append(punishment)
# 		data['b'].append(best)
#
# time = range(len(data['w']))
#
# plt.plot(time, data['w'], 'r', label='wagi')
# plt.plot(time, data['p'], 'g', label='kara')
# plt.plot(time, data['b'], 'b', label='najlepsze')
# plt.legend()
# plt.xlabel('Iteracja')
# plt.ylabel('Wartosci')
# plt.axis([0, len(time), 0, 200])
# plt.show()


if __name__ == '__main__':
    directory = 'data/'
    subdirs = os.listdir(directory)
    
    for d in subdirs:
        curdir = directory + d + '/'
        files = os.listdir(curdir)

        for f in files:
            number, test = f.rsplit('.', 1)

            data = {'w': [], 'p': [], 'b': []}
            with open(curdir + f, 'r') as file:
                next(file) #skip first line

                for line in file:
                    weight, punishment, best = line.split()
                    data['w'].append(int(weight))
                    data['p'].append(int(punishment))
                    data['b'].append(int(best))

            time = range(len(data['w']))
            maximumVal = max([max(data['w']), max(data['b']), max(data['p'])])

            plt.plot(time, data['w'], 'r', label='wagi')
            plt.plot(time, data['p'], 'g', label='kara')
            plt.plot(time, data['b'], 'b', label='najlepsze')
            plt.legend()
            plt.xlabel('Iteracja')
            plt.ylabel('Wartosci')
            plt.title(test + ', wartosc: ' + number)
            plt.axis([0, len(time), 0, maximumVal * 1.2])

            savedir = 'plots/' + d + '/'

            if not os.path.exists(savedir):
                os.makedirs(savedir)
            plt.savefig(savedir + f + '.png')

            plt.clf()
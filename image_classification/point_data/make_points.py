import numpy as np
from math import *

from numpy.random import randn
import csv

n = 200

names = ['points_normal', 'points_ring']

for j in range(2):
  for i in range(len(names)):

    if names[i] == 'points_normal':
      class_1 = 0.6 * randn(n, 2)
      class_2 = 1.2 * randn(n, 2) + np.array([5, 1])
    else:
      class_1 = 0.6 * randn(n, 2)
      r = 0.8 * randn(n, 1) + 5
      angle = 2 * pi * randn(n, 1)
      class_2 = np.hstack((r * np.cos(angle), r * np.sin(angle)))

    label_1 = np.array([np.ones(n)])
    label_2 = np.array([np.ones(n)]) * 2;

    class_1 = np.hstack((class_1, label_1.T))
    class_2 = np.hstack((class_2, label_2.T))

    with open(names[i] + str(j) + '.csv', 'w') as f:
      writer = csv.writer(f, delimiter='\t', lineterminator='\n')
      writer.writerows(class_1)
      writer.writerows(class_2)





import numpy as np
import math

# Random input and output data
x = np.linspace(-math.pi, math.pi, 2000)
y = np.sin(x)

# e^pi - pi rounding error


#Randomly initialize weights
a = np.random.randn()
b = np.random.randn()
c = np.random.randn()
d = np.random.randn()

learning_rate = 1e-6
for t in range(2000):
    # Forward pass: predict y
    # y = a + b x + c x^2 + d x^3

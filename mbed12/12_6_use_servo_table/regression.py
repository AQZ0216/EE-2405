import matplotlib.pyplot as plt
import numpy as np

Ts = 30;   # signal interval
end = 150; # signal end point
n = int(end/Ts)+1

x = np.linspace(0, end, num=n) # signal vector

#TODO: revise this array to your results
# y = np.array([0.000, 4.865, 10.686, 14.275, 15.631, 16.508]) # speed vector
y = np.array([0.000, 6.858, 12.840, 15.870, 16.986, 16.907]) # speed vector

z = np.polyfit(x, y, 2) # Least squares polynomial fit, and return the coefficients.

goal = 5             # if we want to let the servo run at 7 cm/sec
                     # equation : z[0]*x^2 + z[1]*x + z[2] = goal
z[2] -= goal         # z[0]*x^2 + z[1]*x + z[2] - goal = 0

result = np.roots(z) # Return the roots of a polynomial with coefficients given

# output the correct one
if (0 <= result[0]) and (result[0] <= end):
    print(result[0])
else:
    print(result[1])
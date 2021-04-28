#!/usr/bin/python3
try:
    import numpy as np
except ImportError:
    print('Please install numpy libraries first!')
    quit(1)

x1 = float(input("Please enter the X coordinates of the"
                 " top right corner of the field:"))
y1 = float(input("Please enter the Y coordinates of the"
                 " top right corner of the field:"))
x2 = float(input("Please enter the X coordinates of the"
                 " top left corner of the field:"))
y2 = float(input("Please enter the Y coordinates of the"
                 " top left corner of the field:"))

X1 = np.array([[x1], [y1]])
X2 = np.array([[x2], [y2]])
length = np.linalg.norm(X1-X2)
print("The field length = ", '{0:.2f}'.format(length), 'm')

field_angle = np.arctan2(y1-y2, x1-x2)
print("The field angle = ", '{0:.2f}'.format(field_angle), 'rad')

width = float(input("Please enter the desired width of the field:"))

rotation_matrix = np.matrix([[np.cos(field_angle), -np.sin(field_angle)],
                             [np.sin(field_angle),  np.cos(field_angle)]])

flag_distance = float(input("Please enter the distance from the border to "
                            "the flag:"))

F1 = np.array([[flag_distance], [width/2.]])
F1 = rotation_matrix*F1
F1 = X1 - F1

F2 = np.array([[-flag_distance], [width/2.]])
F2 = rotation_matrix*F2
F2 = X2 - F2

X3 = np.array([[0], [width]])
X3 = rotation_matrix*X3
X3 = X2 - X3

X4 = np.array([[0], [width]])
X4 = rotation_matrix*X4
X4 = X1 - X4

print("The field coordinates (formated for MOOS config):")
print('{', '{0:.2f}'.format(float(X1[0])), ',', '{0:.2f}'.format(float(X1[1])),
      ':', '{0:.2f}'.format(float(X2[0])), ',', '{0:.2f}'.format(float(X2[1])),
      ':', '{0:.2f}'.format(float(X3[0])), ',', '{0:.2f}'.format(float(X3[1])),
      ':', '{0:.2f}'.format(float(X4[0])), ',', '{0:.2f}'.format(float(X4[1])),
      '}')

X12 = np.median((X1, X2), axis=0)
X34 = np.median((X3, X4), axis=0)

print("The first half field coordinates (formated for MOOS config):")
print('{', '{0:.2f}'.format(float(X1[0])), ',',
      '{0:.2f}'.format(float(X1[1])),
      ':', '{0:.2f}'.format(float(X12[0])), ',',
      '{0:.2f}'.format(float(X12[1])),
      ':', '{0:.2f}'.format(float(X34[0])), ',',
      '{0:.2f}'.format(float(X34[1])),
      ':', '{0:.2f}'.format(float(X4[0])), ',',
      '{0:.2f}'.format(float(X4[1])),
      '}')

print("The second half field coordinates (formated for MOOS config):")
print('{', '{0:.2f}'.format(float(X12[0])), ',',
      '{0:.2f}'.format(float(X12[1])),
      ':', '{0:.2f}'.format(float(X2[0])), ',',
      '{0:.2f}'.format(float(X2[1])),
      ':', '{0:.2f}'.format(float(X3[0])), ',',
      '{0:.2f}'.format(float(X3[1])),
      ':', '{0:.2f}'.format(float(X34[0])), ',',
      '{0:.2f}'.format(float(X34[1])),
      '}')

print("The first flag coordinates are: "
      "{", '{0:.2f}'.format(float(F1[0])), ',',
      '{0:.2f}'.format(float(F1[1])), "}")
print("The second flag coordinates are: "
      "{", '{0:.2f}'.format(float(F2[0])), ',',
      '{0:.2f}'.format(float(F2[1])), "}")

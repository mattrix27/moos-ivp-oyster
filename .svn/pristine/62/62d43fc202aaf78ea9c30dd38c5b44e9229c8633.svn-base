#!/usr/bin/python3
try:
    import numpy as np
except ImportError:
    print('Please install numpy libraries first!')
    quit(1)

# algorithm from http://slabode.exofire.net/circle_draw.shtml
# void DrawCircle(float cx, float cy, float r, int num_segments)
# {
# 	glBegin(GL_LINE_LOOP);
# 	for(int ii = 0; ii < num_segments; ii++)
# 	{
#       //get the current angle
# 		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);
#
# 		float x = r * cosf(theta);//calculate the x component
# 		float y = r * sinf(theta);//calculate the y component
#
# 		glVertex2f(x + cx, y + cy);//output vertex
#
# 	}
# 	glEnd();
# }


def createCircleApproximation(cx, cy, r, num_segments):
    points = []
    for i in range(num_segments):
        theta = 2 * np.pi * float(i) / float(num_segments)
        x = (r * np.cos(theta))
        y = (r * np.sin(theta))
        points.append((x + cx, y + cy))

    return points


def array2MOOSVector(ar):
    s = '{'

    for i in ar[:-1]:  # all elements but the last
        s += '{0:.2f}'.format(float(i[0])) + ','
        s += '{0:.2f}'.format(float(i[1])) + ':'

    # last gets special treatment
    s += '{0:.2f}'.format(float(ar[-1][0])) + ','
    s += '{0:.2f}'.format(float(ar[-1][1])) + '}'

    return s

x1 = float(input("Please enter the X coordinates of the"
                 " center of the polygon: "))
y1 = float(input("Please enter the Y coordinates of the"
                 " center of the polygon: "))
r1 = float(input("Please enter the radius of the polygon: "))
n1 = int(input("Please enter the number of segments of the polygon: "))

vertices = createCircleApproximation(x1, y1, r1, n1)
print(array2MOOSVector(vertices))

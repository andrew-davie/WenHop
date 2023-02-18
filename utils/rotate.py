# Import math Library
import math
size = 100.0


for i in range(180,0,-5):
    height = size * math.cos(math.radians(90-i))
    step = 19/height
    print('{',int(height+0.5), ',', int(step*256), ', },')




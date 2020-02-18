import numpy as np
import matplotlib.pyplot as plt
from scipy.linalg import solve
fo = open('ex1data1.txt')
print ("文件名为: ", fo.name)

filelist = fo.readlines()                   #将txt文件转换为所有的行组成的列表  
numberoflines =len(filelist)                #得到行数            
print ("行数: %s" % (numberoflines))
returnMat = np.zeros((numberoflines,2))        #生成一个numberoflines行，3列的矩阵
print(returnMat)
index=0
dataset = []

x1=[]
y1=[]
for row in filelist:
    row = row.strip('\n')
    row = row.split(',')
    x1.append(row[0])
    y1.append(row[1])

print(returnMat)


# for line in filelist:
#     line = line.strip()     #去掉每行头尾空白 
#     listline=line.split('\t')       #按换行符分割数据
#     dataset.append(listline)
#     # returnMat = np.array(dataset)
#     returnMat = pd.Series(dataset)
#     # returnMat[index,:] =listline[0:2]        #将文本数据前二列存入数据矩阵
#     index+=1
# print(returnMat)
fo.close()
x1 = np.array(x1,dtype = float)
y1 = np.array(y1,dtype = float)
def linear_regression(x, y):
    N = len(x)
    sumx = sum(x)
    sumy = sum(y)
    sumx2 = sum(x ** 2)
    sumxy = sum(x * y)

    A = np.array([[N, sumx], [sumx, sumx2]])  #也可以用mat
    b = np.array([sumy, sumxy])

    return np.linalg.solve(A, b)

a0, a1 = linear_regression(x1,y1)
_x = [0,25]
_y = [a0 + a1 * x for x in _x]
plt.plot(x1, y1, 'ro', _x, _y, 'b', linewidth=2)
plt.title("y = {} + {}x".format(a0, a1))
plt.show()
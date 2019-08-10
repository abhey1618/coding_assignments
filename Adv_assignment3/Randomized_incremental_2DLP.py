#I have assumed that the input of linear program will be feasible.
#I am also assuming that the user will change the
#initial variables A,b,c,C and m according to his use inside the program.

import sys
import random

def sign(a): #Returns sign of number
    if a>0: return 1
    return -1

def Compute(pt,obj): #Computes the objective function at point
    a = pt[0]*obj[0] + pt[1]*obj[1]
    return a    

#Projects the constraint on the new line
#and checks whether feasible region is on the
#left or right
def Project(lcon,obj,rcon,lco,rco,pt):
    if lcon[1] != 0:
        y = (rcon - lcon[0]*(pt[0]-1))/lcon[1]
        a = feasible([pt[0]-1,y],lco,rco)
    else:
        a = feasible([pt[0],pt[1]-1],lco,rco)
    return a #a=1 means feasible region on the left

def Intersect(aa,ab,ca,cb): #Find point of intersection
    x = (-aa[1]*cb+ ab[1]*ca)/(aa[0]*ab[1]-ab[0]*aa[1])
    y = (aa[0]*cb- ab[0]*ca)/(aa[0]*ab[1]-ab[0]*aa[1])
    return [x,y]

def feasible(opt,lcon,rcon): #Point is feasible for the new constraint
    a = lcon[0]*opt[0] + lcon[1]*opt[1]
    if a<=rcon:
        return 1
    return 0

if __name__ == "__main__":
    c = [3,2] #objective function
    m = 1 #1 means maximization, -1 means minimization
    #Assumed that all the constraints are of <= type.
    #If the constraint is x+y >= 2. Input it as -x-y <= 2
    
    #A is the coefficient matrix of constraints
    Ax = [[sign(c[0])*m,0],[0,sign(c[1])*m],[2,1],[2,3],[3,1],[-1,0],[0,-1]]
    A = Ax[2:] #For shuffling
    Ax = Ax[:2]
    random.seed(6)
    random.shuffle(A)
    Ax.extend(A) #Getting the full Ax after shuffling

    #b is the right hand side of the constraints
    bx = [sys.maxsize,sys.maxsize,18,42,24,0,0]
    b = bx[2:] #For shuffling
    bx = bx[:2]
    random.seed(6)
    random.shuffle(b)
    bx.extend(b) #Getting the full bx after shuffling
    C = [] #List of corner points at each iteration
    #Corner Point based on the first 2 constraints
    C.append([sign(c[0])*sys.maxsize*m,sign(c[1])*sys.maxsize*m])
    for i in range(len(bx)-2):
        j=i+2
        z = feasible(C[i],A[i],b[i])#Checking feasibility w.r.t new constraint
        if z==1:
            C.append(C[i]) #Old optimal is still optimal
        else: #New optimal lies on new constraint
            left = []
            right = []
            for k in range(j):
                try:
                    pt = Intersect(Ax[k],Ax[j],bx[k],bx[j])#If lines are not parallel
                except:
                    continue #If parallel just skip that constraint
                a = Project(Ax[j],c,bx[j],Ax[k],bx[k],pt)
                if a==1:#feasible region on the left so, point is towards right
                    right.append(pt)
                    #print(k, a, pt)
                else:
                    left.append(pt)
                    #print(k, a, pt)
            try:
                maxi = Compute(max(left),c) #if left not empty
            except:
                maxi = -m*sys.maxsize
            try:
                mini = Compute(min(right),c) #if right not empty
            except:
                mini = -m*sys.maxsize

            if m*maxi >= m*mini: #Take the better one w.r.t our motive m
                #print(maxi, mini)
                C.append(max(left))
            else:
                C.append(min(right))
    k = sys.maxsize
    if abs(int(C[len(bx)-2][0])) >= k | abs(int(C[len(bx)-2][1])) >= k:
        #If one coordinate is unbounded
        print("Solution unbounded", C)
        i = 0
    if i!=0:
        print(Compute(C[len(bx)-2],c))
##Answer is 22

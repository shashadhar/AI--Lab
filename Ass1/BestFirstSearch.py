


import copy
import time
import numpy as np

def printNode(node):
    print(node[0],node[1],node[2])
    print(node[3],node[4],node[5])
    print(node[6],node[7],node[8])
    global nodeNumber
    print('Node:', nodeNumber)
    print('Depth:', len(node[9:]))
    print('Moves:', node[9:])
    print('------')
    nodeNumber += 1

def checkFinal(node):
    if node[:9]==finalNode:
        printNode(node)
        return True
    if node[:9] not in visitedList:
        printNode(node)
        nodeList.append(node)
        visitedList.append(node[:9])
    return False

def calculateHeuristic(node):
    distance = 0
    for current, target in enumerate(node):
        currentRow = int(current/3)
        currentColumn = current%3
        targetRow = int(target/3)
        targetColumn = target%3
        distance += abs(currentRow-targetRow) + abs(currentColumn-targetColumn)
    return distance

if __name__ == '__main__':
    startNode = []
    print("Enter the start state: ")
    for i in range(0, 9):
        ele = int(input())
 
        startNode.append(ele)
    finalNode = []
    print("Enter the Goal state : ")
    for i in range(0, 9):
        ele = int(input())
 
        finalNode.append(ele)
    print("START STATE:")
    arr=np.array(startNode)
    new=arr.reshape(3,3)
    print(new)
    
     
    print("GOAL STATE:")   
    arr=np.array(finalNode)
    new=arr.reshape(3,3)
    print(new)
    
    
    found = False
    nodeNumber = 0
    visitedList = []
    nodeList = []
    nodeList.append(startNode)
    visitedList.append(startNode)
    printNode(startNode)
    t0 = time.time()

    while (not found and not len(nodeList)==0):
        fList = []
        for node in nodeList:
            h = calculateHeuristic(node[:9])
            g = len(node[9:])
            f = g+h
            fList.append(f)
        currentNode = nodeList.pop(fList.index(min(fList)))
        blankIndex = currentNode.index(0)
        if blankIndex!=0 and blankIndex!=1 and blankIndex!=2:
            upNode = copy.deepcopy(currentNode)
            upNode[blankIndex] = upNode[blankIndex-3]
            upNode[blankIndex-3] = 0
            upNode.append('up')
            found = checkFinal(upNode)
        if blankIndex!=0 and blankIndex!=3 and blankIndex!=6 and found==False:
            leftNode = copy.deepcopy(currentNode)
            leftNode[blankIndex] = leftNode[blankIndex-1]
            leftNode[blankIndex-1] = 0
            leftNode.append('left')
            found = checkFinal(leftNode)
        if blankIndex!=6 and blankIndex!=7 and blankIndex!=8 and found==False:
            downNode = copy.deepcopy(currentNode)
            downNode[blankIndex] = downNode[blankIndex+3]
            downNode[blankIndex+3] = 0
            downNode.append('down')
            found = checkFinal(downNode)
        if blankIndex!=2 and blankIndex!=5 and blankIndex!=8 and found==False:
            rightNode = copy.deepcopy(currentNode)
            rightNode[blankIndex] = rightNode[blankIndex+1]
            rightNode[blankIndex+1] = 0
            rightNode.append('right')
            found = checkFinal(rightNode)

    t1 = time.time()
    print('Time:', t1-t0)
    print('------')


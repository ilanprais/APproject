import socket
import argparse as ap
import random


def coords(s):
    try:
        x, y = map(int, s.split(','))
        return x, y
    except:
        print("error in coords")

endl = "\r\n"
parser = ap.ArgumentParser(description="Client To Test Ex4 in Advanced programming")
parser.add_argument("-p", default=8081, type=int, help="port to use")
parser.add_argument("-a", default="DFS", choices=["A*", "BFS", "DFS", "BestFS"],
                    help="the algorithm to ask the server to use, default A*")
parser.add_argument("-s", default=(0, 0), type=coords, help="starting point separated by comma")
parser.add_argument("-e", default=(-1, -1), type=coords, help="ending point separated by comma")
args = parser.parse_args()
port = args.p
algorithm = args.a

#for k in range(500):
#    height = random.randint(5, 100)
#    width = random.randint(5, 100)
#    matString = str(height) + ',' + str(width) + endl
#    for i in range(height):
#        for j in range(width):
#            matString += str(random.randint(0, height))
#            if (j < width - 1):
#                matString += ','
#            else:
#                matString += endl
#    matString += str(0) + ',' + str(0) + endl
#    matString += str(height - 1) + ',' + str(width - 1) + endl + endl
#    with open('matrices.txt', 'a') as f:
#        f.write(matString)

with open('matrices.txt', 'r') as f:
    while True:

        sock = socket.socket()
        sock.connect(("127.0.0.1", port))
        sock.send(str.encode(f"solve find-graph-path {algorithm}{endl*2}"))
        sock.recv(1000).decode()

        firstline = f.readline()
        if firstline == '':
            break
            
        index = firstline.find(',')
        height = int(firstline[0 : index])
        width = int(firstline[(index + 1):])

        mat = {}
        i = 0
        while i < height:
            line = f.readline()
            mat[i] = [num.replace('\r','').replace('\n','') for num in line.split(',')]
            i = i + 1

        if f.readline() == '':
            break

        matString = ''
        for i in range(height):
            for j in range(width - 1):
                matString += mat[i][j] + ','
            matString += mat[i][width - 1]+endl
        startingPoint = str(0) + ',' + str(0)
        endingPoint = f'{height - 1},{width - 1}'

        message = str(height) + ',' + str(width) + endl + matString + startingPoint + endl + endingPoint + endl + endl
        print(message)
        sock.send(str.encode(message))
        result = sock.recv(1000).decode()
        print(result)
        with open('ampire.txt', 'a') as g:
            g.write(result + '\r\n')
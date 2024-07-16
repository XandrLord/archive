from collections import deque

diri = [-1, 0, 1, 0, -1, 1, 1, -1]
dirj = [0, 1, 0, -1, 1, 1, -1, -1]

C, R, sc, sr = map(int, input().split())
sr -= 1
sc -= 1

mapa = []
for _ in range(R):
    mapa.append(input())

vist = [[False] * C for _ in range(R)]
vist[sr][sc] = True

q = deque([(sr, sc)])

while q:
    i, j = q.popleft()
    for k in range(8):
        x, y = i + diri[k], j + dirj[k]
        if 0 <= x < R and 0 <= y < C and not vist[x][y] and mapa[x][y] == '.':
            vist[x][y] = True
            q.append((x, y))

for i in range(R):
    if not vist[i][0]:
        vist[i][0] = True
        q.append((i, 0))

for i in range(R):
    if not vist[i][C - 1]:
        vist[i][C - 1] = True
        q.append((i, C - 1))

for i in range(C):
    if not vist[0][i]:
        vist[0][i] = True
        q.append((0, i))

for i in range(C):
    if not vist[R - 1][i]:
        vist[R - 1][i] = True
        q.append((R - 1, i))

while q:
    i, j = q.popleft()
    for k in range(4):
        x, y = i + diri[k], j + dirj[k]
        if 0 <= x < R and 0 <= y < C and not vist[x][y]:
            vist[x][y] = True
            q.append((x, y))

res = 0

for tx in range(R):
    for ty in range(C):
        if not vist[tx][ty] and mapa[tx][ty] == '#':
            vist[tx][ty] = True
            q.append((tx, ty))

            while q:
                i, j = q.popleft()
                for k in range(4):
                    x, y = i + diri[k], j + dirj[k]
                    if 0 <= x < R and 0 <= y < C and not vist[x][y] and mapa[x][y] == '#':
                        vist[x][y] = True
                        q.append((x, y))

            res += 1

print(res)
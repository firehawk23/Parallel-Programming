class Solution:
    #checks wheather a cell is within the matrix 
    def withinBoundry(self, m, n, row, col):
        return (0 <= row < m) and (0 <= col < n)
    
    #finds the number of live neighbours for current cell in all 8 directions
    def findNeighbours(self,board,m,n,row,col):
        num_neigh = 0
        #8 directions
        directions = [(row-1, col-1), (row, col-1), (row+1, col-1),
                      (row-1, col), (row+1, col),
                      (row-1, col+1), (row, col+1), (row+1, col+1)]
        #calculate number of neighbours for each cell
        for dir in directions:
            if self.withinBoundry(m,n,dir[0],dir[1]):
                num_neigh = num_neigh+board[dir[0]][dir[1]]
        return num_neigh
        
    def gameOfLife(self, board):
        m = len(board) #number of rows
        n = len(board[0]) #number of columns
        neighbours = [[0 for j in range(n)] for i in range(m)]
        # Find neighbors for all cells
        for row in range(m):
            for col in range(n):
                neighbours[row][col] = self.findNeighbours(board,m,n,row,col)
        #simulation for next generation
        for row in range(m):
            for col in range(n):
                if board[row][col]==1 and neighbours[row][col]<2:#condition 1
                    board[row][col]=0
                elif board[row][col]==1 and (2<=neighbours[row][col]<=3):#condition 2
                    board[row][col]=1
                elif board[row][col]==1 and neighbours[row][col]>3:#condition 3
                    board[row][col]=0
                elif board[row][col]==0 and neighbours[row][col]==3:#condition 4
                    board[row][col]=1
                else:
                    pass
        return board
    
    def generation(self,board,ng):
        next_gen = board #initialize next generation to board
        i = ng
        while(ng):
            next_gen = self.gameOfLife(next_gen)
            ng=ng-1
        print("\nGeneration %i :" % (i)) #print nth generation value
        print(next_gen)
        return next_gen
    
sol = Solution()
with open('input.txt', 'r') as f:
    board = [[int(num) for num in line.split(',')] for line in f] #getting input from file

a = sol.gameOfLife(board)
b = sol.generation(board,2)
with open('output.txt', 'w') as f:
    #writing output in a file
    for row in b:
        for x in row:
            f.write(str(x) + ',')
        f.write("\n")
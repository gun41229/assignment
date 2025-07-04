import random
import time
import pickle
import heapq

# 명령어:
# O: 칸 열기
# M: 깃발 표시 (지뢰가 있다고 표시하는 용도)
# R: 게임 재시작
# Q: 게임 종료

dx = (-1,0,1,-1,1,-1,0,1)
dy = (-1,-1,-1,0,0,1,1,1)

def main():
    print("게임판의 크기를 입력하세요.")
    N = None
    
    while N is None:
        while N is None:
            try:
                N = int(input())
            except:
                print("정수를 입력하세요.")

        if N <= 1 or N > 20:
            print("2 이상 20 이하의 값을 입력하세요.")
            N = None

    print("지뢰 개수를 입력하세요.")
    M = None

    while M is None:
        while M is None:
            try:
                M = int(input())
            except:
                print("정수를 입력하세요.")

        if M <= 0 or M >= N * N:
            print(f"1 이상 {N * N - 1} 이하의 값을 입력하세요.")
            M = None

    game = Mine_sweeper(N,M)
    game.set_newgame()

    while True:
        print("명령어를 입력하세요. (O: 열기, M: 깃발, R: 재시작, Q: 종료)")
        game.query(input())
        game.print_arr()

def get_ranking_data():
    try:
        with open("rank.p",'rb') as f: 
            return pickle.load(f)
    except FileNotFoundError:
        return []

def update_ranking(user_record, player_name):
    data = get_ranking_data()
    heapq.heappush(data,(user_record,player_name))
    
    temp_data = []
    rank = 1
    for _ in range(min(10,len(data))):
        record,name = heapq.heappop(data)

        if record == float('inf'):
            print(f"이름: {name}, 실패")
        else:
            print(f"{rank}위 - 이름: {name}, 기록: {record:.2f}초")
        rank += 1

        heapq.heappush(temp_data,(record,name))
    
    with open("rank.p",'wb') as f:
        pickle.dump(temp_data,f)

class Mine_sweeper:
    # -1: 지뢰, 나머지: 빈칸
    # 0: 열리지 않은 칸, 1: 열린 칸, -1: 깃발 칸

    def __init__(self,size,max_mine):
        self.arr = None
        self.interface = None
        self.mine = max_mine
        self.size = size
        self.remain_cell = size * size - max_mine
        self.record = time.time()

    def quit(self,code):
        if code == 0:
            print("게임이 종료되었습니다.")
        elif code == 1:
            user_record = time.time() - self.record

            print("게임 클리어!")
            print(f"걸린 시간: {user_record}")
            print("이름을 입력하세요.")
            update_ranking(user_record, input())
        else:
            print("게임 오버")
        exit(0)

    def set_newgame(self):
        self.interface = [[0] * self.size for _ in range(self.size)]
        self.arr = [[0] * self.size for _ in range(self.size)]
        self.remain_cell = self.size * self.size - self.mine 

        remain_mine = self.mine
        remain_cell = self.size * self.size

        random.seed(time.time_ns())

        for y in range(self.size):
            for x in range(self.size):
                chance = random.randint(1,remain_cell)

                if chance <= remain_mine:
                    remain_mine -= 1
                    self.arr[y][x] = -1
                
                remain_cell -= 1
        
        for y in range(self.size):
            for x in range(self.size):
                
                if self.arr[y][x] == -1:
                    for i in range(8):
                        rx = x+dx[i]
                        ry = y+dy[i]

                        if 0 <= rx < self.size and 0 <= ry < self.size and self.arr[ry][rx] != -1:
                            self.arr[ry][rx] += 1
    
    def print_arr(self):
        for y in range(self.size):
            for x in range(self.size):
                if self.interface[y][x] == 0:
                    print('■',end=' ')
                elif self.interface[y][x] == 1:
                    if self.arr[y][x] == -1:
                        print('*',end=' ')
                    elif self.arr[y][x] == 0:
                        print('.',end=' ')
                    else:
                        print(self.arr[y][x],end=' ')
                else:
                    print('F',end=' ')
            print()
    
    def open_cell(self,x,y):
        if self.interface[y][x] == -1:
            print("깃발이 표시된 칸은 열 수 없습니다.")
            return
        if self.interface[y][x] == 1:
            print("이미 열린 칸입니다.")
            return
        
        self.interface[y][x] = 1
        self.remain_cell -= 1
        if self.remain_cell == 0:
            self.quit(1)

        if self.arr[y][x] == -1:
            self.quit(-1)
        elif self.arr[y][x] == 0:

            for i in range(8):
                rx = x+dx[i]
                ry = y+dy[i]

                if 0 <= rx < self.size and 0 <= ry < self.size and self.interface[ry][rx] == 0:
                    self.open_cell(rx,ry)
    
    def query(self,command):
        if command == 'O' or command == 'M':
            print("좌표를 입력하세요: (열: x, 행: y, 0부터 시작)")

            x = None
            y = None
            while x is None:
                try:
                    x,y = map(int,input().split())
                except:
                    print(f"올바른 형식으로 입력하세요 (정수 두 개)")

                if x < 0 or x >= self.size or y < 0 or y >= self.size:
                    print(f"범위를 벗어났습니다. 0부터 {self.size - 1} 사이로 입력하세요.")
                    x = None
            
            if command == 'O':
                self.open_cell(x,y)
            else:
                if self.interface[y][x] == 0:
                    self.interface[y][x] = -1
                elif self.interface[y][x] == -1:
                    self.interface[y][x] = 0
        elif command == 'R':
            print("게임을 다시 시작하시겠습니까? (Y/N)")

            inp = input()
            if inp == 'Y':
                self.set_newgame()
        elif command == 'Q':
            print("게임을 종료하시겠습니까? (Y/N)")

            inp = input()
            if inp == 'Y':
                self.quit(0)
        else:
            print("올바른 명령어를 입력하세요. (O, M, R, Q 중 하나)")

if __name__ == "__main__":
    main()
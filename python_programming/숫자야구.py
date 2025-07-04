import time
import random
import pickle
import heapq

def main():
    game = Pitcher()
    
    while True:
        print("세 개의 숫자를 입력하세요: ",end='')
        try:
            user_input = list(map(int,input()))
        except:
            print("잘못된 입력입니다. 정수 3개를 입력하세요.")
            continue

        if len(user_input) != 3:
            print("정수 3개를 입력해야 합니다.")
            continue

        game.query(user_input)
        

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
    print("\n랭킹 현황:")
    for _ in range(min(10,len(data))):
        record,name = heapq.heappop(data)

        if record != float('inf'):
            print(f"{rank}위: {name}, 기록: {record:.2f}초")
        else:
            print(f"{rank}위: {name}, 실패")
        rank += 1

        heapq.heappush(temp_data,(record,name))
    
    with open("rank.p",'wb') as f:
        pickle.dump(temp_data,f)

class Pitcher:
    def __init__(self):
        random.seed(time.time_ns())
        self.number = [0]*3
        self.count = 0

        for i in range(3):
            self.number[i] = random.randint(0,9)
        
        self.start_time = time.time()
        
    def exit(self,code):
        self.user_record = time.time() - self.start_time

        if code == -1:
            self.user_record = float('inf')
            print("게임 오버")
        else:
            print(f"축하합니다! 점수: {code}")
            print(f"소요 시간: {self.user_record:.2f}초")
        
        print("이름을 입력하세요: ")
        update_ranking(self.user_record, input())
        exit()

    def query(self,user_input):
        self.count += 1
        self.ball = 0
        self.strike = 0

        for i in range(3):
            for j in range(3):
                if user_input[i] == self.number[j]:
                    if i == j:
                        self.strike += 1
                    else:
                        self.ball += 1
        
        if self.strike == 3:
            self.exit(self.count)
        elif self.strike == 0 and self.ball == 0:
            print("아웃")
        else:
            print(f"{self.strike}스트라이크 {self.ball}볼")
        
        if self.count == 9:
            self.exit(-1)

if __name__ == "__main__":
    main()
# 산책로 디자인 비용계산 프로그램 설계

**과목** **|** 알고리즘

**과제명** **|** 알고리즘 설계과제2



## 목차

**1. 개요**

1. 설계의 목적
2. 요구 사항
3. 입출력 제한사항
4. 개발 환경

**2. 필요한 자료구조 및 기능**

1. 필요한 자료구조
2. 기능

**3. 기능별 알고리즘 명세**

**4. 인터페이스 및 사용법**

**5. Prim 알고리즘 설명**



### 1. 개요

##### 1) 설계의 목적

- 최소 비용으로 산책로들에 크리스마스 전구를 설치하기 위해 Prim 알고리즘을 이용하여 조형물을 연결하는 프로그램을 작성한다.



##### 2) 요구 사항

- Prim 알고리즘에서 사용되는 우선순위 큐(Priority Queue)는 STL을 사용하지 말고 정렬되지 않은 시퀀스 또는 힙으로 직접 구현하여 사용해야 한다.
- 가중그래프 정보를 표준입력으로 입력받아, 인접리스트기반(adjacency list representation) 그래프 자료구조를 생성하여 관리한다. 이 때 가중그래프는 무향 연결그래프(connected, undirected graph)로 주어진다.
- 사용가능한 STL은 vector로 제한한다.
- 표준입력으로 입력 받고 표준출력으로 출력한다.



##### 3) 입출력 제한사항

- 프로그램의 한 입력에 대해 정점 정보는 최대 10^4개, 간선 정보는 최대 10^5개, 질의는 최대 5개가 입력된다.
- 채점서버의 입력들에 대해 총 4초의 제한시간 이내에 수행되어야 한다.
- 제시한 입출력 형싱대로 표준입출력을 사용하여 처리한다.
- 문제에서 설명되지 않은 예외 처리를 해야 할 질의는 입력되지 않는다.



##### 4) 개발 환경

- 개발 언어 : C++
- 개발 환경 : Visual Studio 2017



### 2. 필요한 자료구조 밎 기능

##### 1) 필요한 자료구조

- MinHeap

![image](https://user-images.githubusercontent.com/84285337/142722516-da59f945-7985-4e78-b367-1b4af13a2dc1.png)

정점의 Fringe set을 관리하기 위한 자료구조로 매 수행마다 최소 가중치를 갖고 있는 간선을 찾아야 하기 때문에 Heap중에서도 MinHeap이 필요하다.

MinHeap은 vector로 관리하며 vector의 원소는 pair로 조형물의 번호와 가격이 저장되어 있다.



- adjacency list representation

![image](https://user-images.githubusercontent.com/84285337/142722601-e7aa8a98-6202-4b17-b46c-38a04bc55ae1.png)

index는 시작점이고 vector가 담고 있는 정보는 시작점과 이어진 종점과 산책로 디자인 비용이다.



- Tree set을 저장하는 배열

![image](https://user-images.githubusercontent.com/84285337/142722651-2998a099-6dea-484b-a590-76272b698465.png)

정점을 방문했는지(Tree set인지) 저장하기 위한 배열이다. 1이면 선택된 정점이고, 0이면 선택되지 않은 정점이다.



##### 2) 기능

- swap

- insert
- Upheap : 추가의 sub procedure
- pop
- Downheap : 삭제의 sub procedure
- top
- isEmpty



### 3. 기능별 알고리즘 명세

##### 1)  swap

- 배열의 인덱스 두 개를 인자로 받아 두 위치에 있는 값을 바꿔준다. 이 때 MinHeap의 0번 인덱스는 사용하지 않기 때문에 0번 인덱스를 이용하여 바꾼다.

 -> 두 위치의 값 교체 : O(1)

##### 2) insert

- 새로운 pair객체를 입력받아 MinHeap에 삽입한다. 삽입하는 과정에서 sub procedure인 upheap을 재귀적으로 사용한다.

-> Upheap의 시간 복잡도와 동일 : O(log(n))

##### 3) Upheap

- insert의 sub procedure로 새로 삽입한 원소의 값과 부모의 값을 비교하여 MinHeap의 특성을 만족할 때까지 위치를 바꿔주며 재귀적으로 호출한다.

-> 최악의 경우 root까지 진행된다. : O(log(n))

##### 4) pop

- top에 있는 원소를 삭제한다. 삭제하는 과정에서 sub procedure인 downheap을 재귀적으로 사용한다.

-> downheap의 시간 복잡도와 동일 : O(log(n))

##### 5) downheap

- pop의 sub procedure로 top자리에 가장 마지막에 있는 원소를 넣어주고 해당 원소가 알맞은 자리를 찾을 때까지 자식과 위치를 바꿔가며 재귀적으로 호출한다.

-> 최악의 경우 root에서 leaf까지 진행된다. : O(log(n))

##### 6) top

- top에 있는 원소를 pair객체로 반환한다.

-> top원소 반환 : O(1)

##### 7) isEmpty

- heap size를 확인하여 0이라면 true를 0이 아니라면 false를 리턴한다.

-> heap size확인 : O(1)



### 4. 인터페이스 및 사용법

##### 1) swap

- ![image](https://user-images.githubusercontent.com/84285337/142722791-a9a92260-3437-4b75-ac88-6786625717a9.png)	

  - 배열의 idx1과 idx2의 값의 위치를 바꾼다.



##### 2) insert

- ![image-20211120192231194](C:\Users\seokjinkang\AppData\Roaming\Typora\typora-user-images\image-20211120192231194.png)	

- 외부에서 정점의 번호와 가격을 입력 받으면 pair로 만들어 MinHeap에 추가한다.



##### 3) UpHeap

- ![image](https://user-images.githubusercontent.com/84285337/142722959-19e64062-2ddc-4011-9788-15b9f1ef2a65.png)	

- insert의 sub procedure다.
- 부모와의 값을 비교하여 MinHeap의 특성을 만족하지 못하면 부모와 자리를 바꾸어 나가며 MinHeap의 특성을 만족하도록 만든다.



##### 4) pop

- ![image](https://user-images.githubusercontent.com/84285337/142722981-75444648-f288-4c57-adef-5379a8881af7.png)	
- MinHeap에 있는 top원소를 삭제한다.



##### 5) DownHeap

- ![image](https://user-images.githubusercontent.com/84285337/142722999-46305332-1d5f-4492-9ff8-1e6e93da8a1f.png)	
- pop의 sub procedure다.
- 자식과의 값을 비교하여 MinHeap의 특성을 만족하지 못하면 자식과 자리를 바꾸어 나가며 MinHeap의 특성을 만족하도록 만든다.



##### 6) isEmpty

- ![image](https://user-images.githubusercontent.com/84285337/142817743-b7be85c6-9456-4110-b812-b260924cc49a.png)		
- MinHeap이 비어있는지를 bool 타입으로 리턴해준다.



##### 7) top

- ![image](https://user-images.githubusercontent.com/84285337/142817787-de163979-1311-4400-a519-ca4edf63b964.png)		
- MinHeap의 top에 있는 원소를 pair객체로 리턴해준다.



### **5. Prim 알고리즘 설명**

프림 알고리즘은 무향 연결 그래프에서 Minimum Spaning Tree를 찾기 위한 알고리즘이다. 시작 정점을 Tree set으로 만들어둔 후 시작한다. 시작 정점으로부터 연결된 간선들을 Priority Queue로 만들어진 Fringe set에 넣어주고 최소 가중치를 가진 간선을 꺼내 연결된 정점을 Tree set에 넣어준다. 이 때 넣어준 정점에 대해 연결된 모든 간선들을 Fringe set에 추가한다. 위와 같은 과정을 지속적으로 진행하다 모든 정점이 Tree set에 들어간다면 알고리즘은 종료되고 Minimum Spanning Tree를 찾을 수 있다.



Tree set을 관리하기 위해 bool타입 배열 visit을 만들어두었다. index는 해당 정점의 번호이고 1이라면 Tree set에 포함된 상태, 0이라면 Tree set에 포함되지 않은 상태로 구분한다.

시작 정점을 입력 받고 Prim알고리즘을 진행하기 때문에 시작 정점을 Tree set에 추가시켜준다. (visit[index] = true)

Minheap기반의 Priority Queue로 만들어진 Fringe set을 만들어주고, 시작 정점과 연결된 간선들의 도착 정점과 간선의 가중치를 pair객체로 Fringe set에 추가해준다.

Fringe set에 간선 객체가 없을 때까지 다음과 같은 과정을 반복한다.

Fringe set에서 간선의 가중치가 최소인 간선을 꺼냈을 때, 만약 도착 정점이 Tree set이 아닌경우 Tree set에 추가하고 도착 정점과 연결된 간선에 대해 이전과 같이 Fringe set에 추가한다. 이 때 도착 정점과 연결된 간선의 도착 정점이 Tree set이 아닐경우에만 추가해준다. 만약 도착 정점이 Tree set인 경우 아무것도 하지 않고 다른 최소 간선을 뽑는다.


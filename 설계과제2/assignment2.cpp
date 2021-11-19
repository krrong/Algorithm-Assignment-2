#include <iostream>
#include <vector>
#define UNSEEN	0
#define FRINGE	1
#define TREE	2
using namespace std;

int n, m, q;

class Node {
public:
	int prev;	// tree set으로 끌어들인 조형물 번호
	int price;	// 산책로를 놓는데 드는 비용
	int state;	// 노드의 상태정보

	Node() {
		prev = price = state = -1;
	}

	Node(int prev, int price) {
		this->prev = prev;
		this->price = price;
		state = UNSEEN;
	}
};

// 최소 힙 -> fringe set에서 최소 간선을 구하기 위함
class MinHeap {
public:
	vector<Node> v;	
	int heap_size;			// 힙 크기 저장
	int root_index;			// 루트 인덱스 저장

	MinHeap() {
		v.push_back(Node());	// 0번 인덱스는 사용하지 않음
		heap_size = 0;			// 힙 크기
		root_index = 1;			// 루트 인덱스
	}

	void swap(int idx1, int idx2);		// idx1, idx2 노드 교체
	void upheap(int idx);
	void downheap(int idx);
	void insert(Node e);
	bool isEmpty();
	int top();
};

// index는 시작지점, pair<종점, 비용> 저장
vector<pair<int, int>> graph[100001];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m >> q;

	// 무향 그래프 생성
	for (int i = 0; i < m; i++) {
		int x, y, p;
		cin >> x >> y >> p;
		graph[x].push_back(make_pair(y, p));
		graph[y].push_back(make_pair(x, p));
	}

	// 쿼리 입력
	for (int i = 0; i < q; i++) {
		string str;
		int start;
		cin >> str >> start;


		MinHeap fringe;	// fringe set

		// 시작점과 연결된 간선들에 대해서 UNSEEN -> FRINGE로 바꿔줌
		for (int i = 0; i < graph[start].size(); i++) {

		}
	}

	return 0;
}


void MinHeap::swap(int idx1, int idx2) {
	v[0] = v[idx1];
	v[idx1] = v[idx2];
	v[idx2] = v[0];
}

void MinHeap::upheap(int idx) {
	// 루트이면 종료
	if (idx == root_index) {
		return;
	}

	int parent = idx / 2;	// 부모 index
	// 부모의 가격이 더 크면
	if (v[idx].price < v[parent].price) {
		swap(idx, parent);	// 바꿔주고
		upheap(parent);		// upheap 마저 진행
	}
}

void MinHeap::downheap(int idx) {
	int left = idx * 2;			// 왼쪽 자식 인덱스
	int right = idx * 2 + 1;	// 오른쪽 자식 인덱스

	if (right <= heap_size) {
		if (v[left].price <= v[right].price) {
			if (v[left].price < v[idx].price) {
				swap(left, idx);
				downheap(left);
			}
			else return;
		}
		else {
			if (v[right].price < v[idx].price) {
				swap(right, idx);
				downheap(right);
			}
			else return;
		}
	}
	else if (left <= heap_size) {
		if (v[left].price < v[idx].price) {
			swap(left, idx);
			downheap(left);
		}
		else return;
	}
	else return;
}

void MinHeap::insert(Node e) {
	v.push_back(e);
	heap_size++;
	upheap(heap_size);
}

bool MinHeap::isEmpty() {
	return heap_size == 0;
}

int MinHeap::top() {
	if (isEmpty()) {
		return -1;
	}
	else {
		//return v[root_index];
	}
}
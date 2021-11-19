#include <iostream>
#include <vector>
using namespace std;

int n, m, q;
vector<int> order;		// 순서
int answer;				// 총 비용
vector<pair<int, int>> graph[100001];	// index는 시작지점, pair<조형물 번호, 비용> 저장
bool visit[100001];					// 방문했는지 체크

// 최소 힙 -> fringe set에서 최소 간선을 구하기 위함
class MinHeap {
public:
	vector<pair<int, int>> v;	// 조형물의 번호, 가격 저장
	int heap_size;				// 힙 크기 저장
	int root_index;				// 루트 인덱스 저장

	MinHeap() {
		v.push_back(make_pair(0, 0));	// 0번 인덱스는 사용하지 않음
		heap_size = 0;					// 힙 크기
		root_index = 1;					// 루트 인덱스
	}

	void swap(int idx1, int idx2);		// idx1, idx2 노드 교체
	void upheap(int idx);				// 추가시 필요한 upheap
	void downheap(int idx);				// 삭제시 필요한 downheap 
	void insert(pair<int, int> e);		// 새로운 원소 추가
	void pop();							// top원소 삭제
	bool isEmpty();						// 비어있는지 리턴
	pair<int, int> top();				// top원소 리턴(정점 번호, 비용)
};

// prim알고리즘
void prim(int start) {
	MinHeap fringe;			// fringe set

	// 시작점과 연결된 간선들에 대해서 FRINGE set에 추가
	for (int i = 0; i < graph[start].size(); i++) {
		int node = graph[start][i].first;		// 조형물 번호
		int price = graph[start][i].second;		// 산책로 비용

		fringe.insert(make_pair(node, price));	// fringe set에 추가
	}

	visit[start] = true;	// 시작점 선택 체크
	order.push_back(start);

	// fringe가 비어있지 않을동안 반복
	while (!fringe.isEmpty()) {
		int node = fringe.top().first;		// 가장 저렴한 정점의 번호
		int price = fringe.top().second;	// 가장 저렴한 정점
		fringe.pop();						// top원소 삭제

		// 이전에 선택이 안되어 있었다면
		if (visit[node] == false) {
			visit[node] = true;				// 선택 표시
			answer = answer + price;			// 총 비용 갱신
			order.push_back(node);				// 순서대로 삽입

			// 지금 선택한 조형물과 연결된 다리를 fringe set에 추가
			for (int i = 0; i < graph[node].size(); i++) {
				int node2 = graph[node][i].first;		// 지금 선택한 조형물과 연결된 조형물의 번호
				int price2 = graph[node][i].second;		// 지금 선택한 조형물과의 산책로 비용

				// 이전에 선택이 되지 않았을 경우만 fringe set에 추가함
				if (visit[node2] == false) {
					fringe.insert(make_pair(node2, price2));
				}
			}
		}

	}

}

// 초기화 함수 -> 프림알고리즘 사용 후 선택 배열과 순서벡터를 초기화
void reset() {
	for (int i = 0; i < 100001; i++) {
		visit[i] = false;
	}
	order.clear();
	answer = 0;
}

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
		prim(start);

		cout << answer << ' ';
		for (int i = 0; i < order.size(); i++) {
			cout << order[i] << ' ';
		}
		cout << '\n';
		reset();
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
	if (v[idx].second < v[parent].second) {
		swap(idx, parent);	// 바꿔주고
		upheap(parent);		// upheap 마저 진행
	}
	// 가격이 같다면
	else if (v[idx].second == v[parent].second) {
		// 부모의 번호가 더 크면
		if (v[idx].first < v[parent].first) {
			swap(idx, parent);	// 바꿔주고
			upheap(parent);		// upheap 마저 진행
		}
	}
}

void MinHeap::downheap(int idx) {
	int left = idx * 2;			// 왼쪽 자식 인덱스
	int right = idx * 2 + 1;	// 오른쪽 자식 인덱스

	// 양쪽 자식 모두 값이 있을 때
	if (right <= heap_size) {
		// 왼쪽 자식의 값이 더 작고
		if (v[left].second <= v[right].second) {
			// 부모가 더 크면
			if (v[left].second < v[idx].second) {
				swap(left, idx);	// 바꿔주고
				downheap(left);		// 왼쪽 자식에서 다시 downheap
			}
			else return;
		}
		// 오른쪽 자식의 값이 더 작고
		else {
			// 부모가 더 크면
			if (v[right].second < v[idx].second) {
				swap(right, idx);	// 바꿔주고
				downheap(right);	// 오른쪽 자식에서 다시 downheap
			}
			else return;
		}
	}
	// 왼쪽 자식만 있을 경우
	else if (left <= heap_size) {
		// 부모가 더 크면
		if (v[left].second < v[idx].second) {
			swap(left, idx);	// 바꿔주고
			downheap(left);		// 왼쪽 자식에서 다시 downheap
		}
		else return;
	}
	else return;	// 양쪽 모두 없는 경우 아무일도 일어나지 않음
}

void MinHeap::insert(pair<int, int> e) {
	v.push_back(e);
	heap_size++;
	upheap(heap_size);
}

bool MinHeap::isEmpty() {
	return heap_size == 0;
}

void MinHeap::pop() {
	v[root_index] = v[heap_size];
	v.pop_back();
	heap_size--;
	downheap(root_index);
}

pair<int, int> MinHeap::top() {
	if (isEmpty()) {
		return make_pair(0, 0);
	}
	else {
		return v[root_index];
	}
}
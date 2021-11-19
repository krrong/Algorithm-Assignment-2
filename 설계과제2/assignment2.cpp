#include <iostream>
#include <vector>
#define UNSEEN	0
#define FRINGE	1
#define TREE	2
using namespace std;

int n, m, q;

class Node {
public:
	int prev;	// tree set���� ������� ������ ��ȣ
	int price;	// ��å�θ� ���µ� ��� ���
	int state;	// ����� ��������

	Node() {
		prev = price = state = -1;
	}

	Node(int prev, int price) {
		this->prev = prev;
		this->price = price;
		state = UNSEEN;
	}
};

// �ּ� �� -> fringe set���� �ּ� ������ ���ϱ� ����
class MinHeap {
public:
	vector<Node> v;	
	int heap_size;			// �� ũ�� ����
	int root_index;			// ��Ʈ �ε��� ����

	MinHeap() {
		v.push_back(Node());	// 0�� �ε����� ������� ����
		heap_size = 0;			// �� ũ��
		root_index = 1;			// ��Ʈ �ε���
	}

	void swap(int idx1, int idx2);		// idx1, idx2 ��� ��ü
	void upheap(int idx);
	void downheap(int idx);
	void insert(Node e);
	bool isEmpty();
	int top();
};

// index�� ��������, pair<����, ���> ����
vector<pair<int, int>> graph[100001];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m >> q;

	// ���� �׷��� ����
	for (int i = 0; i < m; i++) {
		int x, y, p;
		cin >> x >> y >> p;
		graph[x].push_back(make_pair(y, p));
		graph[y].push_back(make_pair(x, p));
	}

	// ���� �Է�
	for (int i = 0; i < q; i++) {
		string str;
		int start;
		cin >> str >> start;


		MinHeap fringe;	// fringe set

		// �������� ����� �����鿡 ���ؼ� UNSEEN -> FRINGE�� �ٲ���
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
	// ��Ʈ�̸� ����
	if (idx == root_index) {
		return;
	}

	int parent = idx / 2;	// �θ� index
	// �θ��� ������ �� ũ��
	if (v[idx].price < v[parent].price) {
		swap(idx, parent);	// �ٲ��ְ�
		upheap(parent);		// upheap ���� ����
	}
}

void MinHeap::downheap(int idx) {
	int left = idx * 2;			// ���� �ڽ� �ε���
	int right = idx * 2 + 1;	// ������ �ڽ� �ε���

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
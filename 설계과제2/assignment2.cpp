#include <iostream>
#include <vector>
using namespace std;

int n, m, q;
vector<int> order;		// ����
int answer;				// �� ���
vector<pair<int, int>> graph[100001];	// index�� ��������, pair<������ ��ȣ, ���> ����
bool visit[100001];					// �湮�ߴ��� üũ

// �ּ� �� -> fringe set���� �ּ� ������ ���ϱ� ����
class MinHeap {
public:
	vector<pair<int, int>> v;	// �������� ��ȣ, ���� ����
	int heap_size;				// �� ũ�� ����
	int root_index;				// ��Ʈ �ε��� ����

	MinHeap() {
		v.push_back(make_pair(0, 0));	// 0�� �ε����� ������� ����
		heap_size = 0;					// �� ũ��
		root_index = 1;					// ��Ʈ �ε���
	}

	void swap(int idx1, int idx2);		// idx1, idx2 ��� ��ü
	void upheap(int idx);				// �߰��� �ʿ��� upheap
	void downheap(int idx);				// ������ �ʿ��� downheap 
	void insert(pair<int, int> e);		// ���ο� ���� �߰�
	void pop();							// top���� ����
	bool isEmpty();						// ����ִ��� ����
	pair<int, int> top();				// top���� ����(���� ��ȣ, ���)
};

// prim�˰���
void prim(int start) {
	MinHeap fringe;			// fringe set

	// �������� ����� �����鿡 ���ؼ� FRINGE set�� �߰�
	for (int i = 0; i < graph[start].size(); i++) {
		int node = graph[start][i].first;		// ������ ��ȣ
		int price = graph[start][i].second;		// ��å�� ���

		fringe.insert(make_pair(node, price));	// fringe set�� �߰�
	}

	visit[start] = true;	// ������ ���� üũ
	order.push_back(start);

	// fringe�� ������� �������� �ݺ�
	while (!fringe.isEmpty()) {
		int node = fringe.top().first;		// ���� ������ ������ ��ȣ
		int price = fringe.top().second;	// ���� ������ ����
		fringe.pop();						// top���� ����

		// ������ ������ �ȵǾ� �־��ٸ�
		if (visit[node] == false) {
			visit[node] = true;				// ���� ǥ��
			answer = answer + price;			// �� ��� ����
			order.push_back(node);				// ������� ����

			// ���� ������ �������� ����� �ٸ��� fringe set�� �߰�
			for (int i = 0; i < graph[node].size(); i++) {
				int node2 = graph[node][i].first;		// ���� ������ �������� ����� �������� ��ȣ
				int price2 = graph[node][i].second;		// ���� ������ ���������� ��å�� ���

				// ������ ������ ���� �ʾ��� ��츸 fringe set�� �߰���
				if (visit[node2] == false) {
					fringe.insert(make_pair(node2, price2));
				}
			}
		}

	}

}

// �ʱ�ȭ �Լ� -> �����˰��� ��� �� ���� �迭�� �������͸� �ʱ�ȭ
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
	// ��Ʈ�̸� ����
	if (idx == root_index) {
		return;
	}

	int parent = idx / 2;	// �θ� index
	// �θ��� ������ �� ũ��
	if (v[idx].second < v[parent].second) {
		swap(idx, parent);	// �ٲ��ְ�
		upheap(parent);		// upheap ���� ����
	}
	// ������ ���ٸ�
	else if (v[idx].second == v[parent].second) {
		// �θ��� ��ȣ�� �� ũ��
		if (v[idx].first < v[parent].first) {
			swap(idx, parent);	// �ٲ��ְ�
			upheap(parent);		// upheap ���� ����
		}
	}
}

void MinHeap::downheap(int idx) {
	int left = idx * 2;			// ���� �ڽ� �ε���
	int right = idx * 2 + 1;	// ������ �ڽ� �ε���

	// ���� �ڽ� ��� ���� ���� ��
	if (right <= heap_size) {
		// ���� �ڽ��� ���� �� �۰�
		if (v[left].second <= v[right].second) {
			// �θ� �� ũ��
			if (v[left].second < v[idx].second) {
				swap(left, idx);	// �ٲ��ְ�
				downheap(left);		// ���� �ڽĿ��� �ٽ� downheap
			}
			else return;
		}
		// ������ �ڽ��� ���� �� �۰�
		else {
			// �θ� �� ũ��
			if (v[right].second < v[idx].second) {
				swap(right, idx);	// �ٲ��ְ�
				downheap(right);	// ������ �ڽĿ��� �ٽ� downheap
			}
			else return;
		}
	}
	// ���� �ڽĸ� ���� ���
	else if (left <= heap_size) {
		// �θ� �� ũ��
		if (v[left].second < v[idx].second) {
			swap(left, idx);	// �ٲ��ְ�
			downheap(left);		// ���� �ڽĿ��� �ٽ� downheap
		}
		else return;
	}
	else return;	// ���� ��� ���� ��� �ƹ��ϵ� �Ͼ�� ����
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
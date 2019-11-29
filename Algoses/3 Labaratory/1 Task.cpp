#include <fstream>
#include <vector>

using namespace std;

int left_binary(vector<int>& list, int element) {
	int start = -1;
	int end = list.size();
	int middle;
	while (start < end - 1) {
		middle = (start + end) / 2;
		if (list[middle] < element) {
			start = middle;
		}
		else {
			end = middle;
		}
	}
	if (end >= list.size())
		return -2;
	else if (list.at(end) != element)
		return -2;
	return end;
}

int right_binary(vector<int>& list, int element) {
	int start = -1;
	int end = list.size();
	int middle;
	while (start < end - 1) {
		middle = (start + end) / 2;
		if (list[middle] <= element) {
			start = middle;
		}
		else {
			end = middle;
		}
	}
	if (end < list.size() && list[end] == element)
		return end;
	else if (start > -1 && list[start] == element)
		return start;
	else
		return -2;
}

int main() {
	ifstream in("binsearch.in");
	ofstream out("binsearch.out");
	int n;
	in >> n;
	vector <int> list (n);
	for (int i = 0; i < n; ++i) {
		in >> list.at(i);
	}
	int count;
	in >> count;
	int element, left, right;
	for (int i = 0; i < count; ++i) {
		in >> element;
		left = left_binary(list, element) + 1;
		right = right_binary(list, element) + 1;
		out << left << ' ' << right << '\n';
	}
	in.close();
	out.close();
}

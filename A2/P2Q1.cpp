#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <assert.h>

using namespace std;

struct item {
	int num;
	int weight;
	int value1;
	int value2;
};

// M matrix that is used to store solutions to subproblems
vector<vector<vector<int> > > max_values;

// stores the items stored in the respective knapsack
vector <int> knapsack1;
vector <int> knapsack2;

// array of all items
vector <item> all_items;



int find_weight(int item_num) {
	for (int i = 0; i < all_items.size(); i++) {
		if (item_num == all_items.at(i).num) {
			return all_items.at(i).weight;
		}
	}
	// should not get here:
	return -1;
}

int find_value(int item_num, int v_bag) {
	for (int i = 0; i < all_items.size(); i++) {
		if (item_num == all_items.at(i).num) {
			if (v_bag == 1) {
				return all_items.at(i).value1;
			} else if (v_bag == 2) {
				return all_items.at(i).value2;
			}
		}
	}
	// should not get here:
	return -1;
}

void back_track(int n, int W1, int W2) {
	int i = n;
	int w1 = W1;
	int w2 = W2;
	while(i > 0) {
		if (max_values[i][w1][w2] == max_values[i-1][w1][w2]) {
			// didnt use item i 
			i--;
			continue;
		} 
		if (find_weight(i) <= w1) { 
			if (max_values[i][w1][w2] == find_value(i, 1) + max_values[i-1][w1 - find_weight(i)][w2]) {
				// put item i in bag 1;
				knapsack1.push_back(i);
				w1 = w1 - find_weight(i);
				i--;
				continue;
			}
		}
			// put item i in bag 2
		if (find_weight(i) <= w2) {
			if (max_values[i][w1][w2] == find_value(i, 2) + max_values[i-1][w1][w2 - find_weight(i)]) {
				knapsack2.push_back(i);
				w2 = w2 - find_weight(i);
				i--;
			}
		}
	}
}

// returns the max value, also places values into the max_values matrix:
void find_max_value(int n, int w1, int w2) {
	for (int i = 1; i <= n; i++) {
		for (int l1 = 0; l1 <= w1; l1++) {
			for (int l2 = 0; l2 <= w2; l2++) {
				int X = max_values[i - 1][l1][l2];
				if (find_weight(i) <= l1) {
					if ((find_value(i, 1) + max_values[i-1][l1 - find_weight(i)][l2]) > X) {
						X = find_value(i, 1) + max_values[i-1][l1 - find_weight(i)][l2];
					}
				}
				if (find_weight(i) <= l2) {
					if ((find_value(i,2) + max_values[i-1][l1][l2 - find_weight(i)]) > X) {
						X = find_value(i, 2) + max_values[i-1][l1][l2 - find_weight(i)];
					}
				}
				max_values[i][l1][l2] = X;
			}
		}
	}
}


void matrix_init(int n, int w1, int w2) {
/*	max_values.resize(n + 1);
	for (int i = 0; i < n + 1; ++i) {
		max_values[i].resize(w1 + 1);

		for (int j = 0; j < w1 + 1; ++j) {
			max_values[i][j].resize(w2 + 1);
		}
	}
*/
	max_values.resize(n + 1, vector<vector<int> >(w1 + 1, vector<int>(w2 + 1)));

	for (int l1 = 0; l1 <= w1; l1++) {
		for (int l2 = 0; l2 <= w2; l2++) {
			max_values[0][l1][l2] = 0;
		}
	}

}

void print_output(int n, int weight1, int weight2) {
	cout << max_values[n][weight1][weight2] << endl;
	for (int i = 0; i < knapsack1.size(); i++) {
		if (i == knapsack1.size() - 1) {
			// last item.... should output a new line after
			cout << knapsack1.at(i) << endl;
		} else {
			cout << knapsack1.at(i) << " ";
		}
	}

	for (int i = 0; i < knapsack2.size(); i++) {
		if (i == knapsack2.size() - 1) {
			// last item.... should output a new line after
			cout << knapsack2.at(i) << endl;
		} else {
			cout << knapsack2.at(i) << " ";
		}
	}
}


int main() {
	string input = "";

	// get first line of input
	int total_num_items;
	getline(cin, input);
	stringstream ss_total_num_items(input);
	ss_total_num_items >> total_num_items;


	// get 2nd line of input
	int weight1;
	int weight2;
	getline(cin, input);
	stringstream ss_weights(input);
	ss_weights >> weight1;
	ss_weights >> weight2;

	// now initialize the 3D matrix:
	matrix_init(total_num_items, weight1, weight2);

	// get 3rd line of input
	int item_weight;
	getline(cin, input);
	stringstream ss_item_weight(input);
	for (int i = 1; i <= total_num_items; i++) {
		ss_item_weight >> item_weight;
		struct item newItem;
		newItem.num = i;
		newItem.weight = item_weight;
		all_items.push_back(newItem);
	}

	// get 4th line of input
	int value1;
	getline(cin, input);
	stringstream ss_value1(input);
	for (int i = 0; i < all_items.size(); i++) {
		ss_value1 >> value1;
		all_items.at(i).value1 = value1;
	}

	// get 5th line of input
	int value2;
	getline(cin, input);
	stringstream ss_value2(input);
	for (int i = 0; i < all_items.size(); i++) {
		ss_value2 >> value2;
		all_items.at(i).value2 = value2;
	}

	// now find the max value:
	find_max_value(total_num_items, weight1, weight2);

	// puts into the knapsack vectors the list of items put in each bag
	back_track(total_num_items, weight1, weight2);

	// sort the vectors....
	sort(knapsack1.begin(), knapsack1.end());
	sort(knapsack2.begin(), knapsack2.end());

	// now print
	print_output(total_num_items, weight1, weight2);


}
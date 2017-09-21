#include <iostream>
#include "StatisticMultiset.h"
#include "EmptySet.h"

using namespace std;

int main() {
	myOwnSet::StatisticMultiset<int> multiset;
	//multiset.AddNum(55);
	try {
		cout << multiset.GetAvg() << endl << multiset.GetMax() << endl << multiset.GetMin() << endl;
	}
	catch (const EmptySetException& exc) {
		cerr << exc.what() << endl;
	}
	
	



	system("pause");
	return 0;
}
#pragma once

#include <set>
#include <list>
#include <vector>
#include <limits>
#include <fstream>
#include "EmptySet.h"

namespace myOwnSet {

	template<class T>
	class StatisticMultiset {
	public:
		StatisticMultiset() = default;		
		
		void AddNum(const T&);
		
		void  AddNum(const std::multiset<T>& numbers);
	
		void  AddNum(const std::vector<T>& numbers);
		
		void  AddNum(const std::list<T>& numbers);
		
		void  AddNums(const StatisticMultiset& a_stat_set);

		void  AddNumsFromFile(const char* filename);
		

		T GetMax();
		T GetMin();
		float GetAvg();
		int GetCountUnder(float threshold);
		int GetCountAbove(float threshold);

		private:
			std::multiset<T> data;
			std::pair<float, int> countUnder;
			std::pair<float, int> countAbove;
			bool flags[5] = { 0, 0, 0, 0, 0 };
			mutable T maxValue;
			mutable T minValue;
			mutable float avgValue;
	};		

	template<class T>
	void StatisticMultiset<T>::AddNum(const T & num) {
		data.insert(num);
		for (auto &i : flags) {
			i = 1;
		}
	}

	template<class T>
	inline void StatisticMultiset<T>::AddNum(const std::multiset<T>& numbers) {
		for (const auto &i : numbers) {
			data.insert(i);
		}
	}

	template<class T>
	inline void StatisticMultiset<T>::AddNum(const std::vector<T>& numbers) {
		for (const auto &i : numbers) {
			data.insert(i);
		}
	}

	template<class T>
	inline void StatisticMultiset<T>::AddNum(const std::list<T>& numbers) {
		for (const auto &i : numbers) {
			data.insert(i);
		}
	}

	template<class T>
	inline void StatisticMultiset<T>::AddNums(const StatisticMultiset & a_stat_set) {
		for (const auto &i : a_stat_set.data) {
			data.insert(i);
		}
	}

	template<class T>
	inline void StatisticMultiset<T>::AddNumsFromFile(const char * filename) {
		std::fstream reader(filename, std::ifstream::in);
		float buffer;
		while (reader.good()) {
			reader >> buffer;
			data.insert(buffer);
		}
	}

	template<class T>
	inline T StatisticMultiset<T>::GetMax() {
		if (data.empty()) {
			throw EmptySetException("The multiset is empty now. Fill it first!");
		}
		if (flags[2]) {
			T max = std::numeric_limits<T>::min();
			for (const auto &i : data) {
				if (max < i) {
					max = i;
				}
			}
			flags[2] = 0;
			maxValue = max;
			return maxValue;
		}
		return maxValue;
	}

	template<class T>
	T StatisticMultiset<T>::GetMin() {
		if (data.empty()) {
			throw EmptySetException("The multiset is empty now. Fill it first!");
		}
		if (flags[0]) {
			T min = std::numeric_limits<T>::max();
			for (const auto &i : data) {
				if (min > i) {
					min = i;
				}
			}
			flags[0] = 0;
			minValue = min;
			return minValue;
		}
		return minValue;
	}

	template<class T>
	float StatisticMultiset<T>::GetAvg() {
		if (data.empty()) {
			throw EmptySetException("The multiset is empty now. Fill it first!");
		}
		if (flags[1]) {
			float avg = 0.0f;
			for (const auto &i : data) {
				avg += i;
			}
			flags[1] = 0;
			avgValue = avg;
			return avgValue / data.size();
		}
		return avgValue;
	}

	template<class T>
	int StatisticMultiset<T>::GetCountUnder(float threshold) {
		if (data.empty()) {
			throw EmptySetException("The multiset is empty now. Fill it first!");
		}
		if (flags[3] || threshold != countUnder.first) {
			int counter = 0;
			for (const auto &i : data) {
				if (i < threshold) {
					count++;
				}
			}
			flags[3] = 0;
			countUnder = make_pair<float, int>(threshold, count);
			return count;
		}
		return countUnder.second;
	}

	template<class T>
	int StatisticMultiset<T>::GetCountAbove(float threshold) {
		if (data.empty()) {
			throw EmptySetException("The multiset is empty now. Fill it first!");
		}
		if (flags[4] || threshold != countAbove.first) {
			int counter = 0;
			for (const auto &i : data) {
				if (i > threshold) {
					count++;
				}
			}
			flags[4] = 0;
			countAbove = make_pair<float, int>(threshold, count);
			return count;
		}
		return countAbove.second;
	}
}

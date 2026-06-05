#include <bits/stdc++.h>
using namespace std;

void run_dijkstra_typical(vector<vector<pair<int,long long>>>& adj, vector<long long>& result,
	int v, int end = -1) {
	using pr = pair<int, long long>;

	auto cmp_pair = [](const pr& a, const pr& b) {
		return a.second > b.second;
	};

	priority_queue<pr, vector<pr>, decltype(cmp_pair)> pq(cmp_pair);
	pq.push(make_pair(v, result[v] = 0));

	while(!pq.empty()) {
		auto [currV, currDist] = pq.top();
		pq.pop();
		if(currDist != result[currV]) continue;
		if(currV == end) return;

		for(auto [nextV, weight] : adj[currV]) {
			long long newDist = currDist + weight;
			if(newDist < result[nextV]) {
				pq.push(make_pair(nextV, result[nextV] = newDist));
			}
		}
	}
}


template <typename DIST = long long, typename WEIGHT = long long>
void run_dijkstra(vector<vector<pair<int,WEIGHT>>>& adj, vector<DIST>& result,
	int v, DIST start,
	int end = -1,
	auto dijkstra_cmp_pq_dist = less<>(),
	auto dijkstra_combine = [](const DIST& a, const WEIGHT& b) {
		return a + b;
	}) {


	using pr = pair<int, DIST>;

	auto cmp_pair = [&dijkstra_cmp_pq_dist](const pr& a, const pr& b) {
		// reversed because c++ pq is like that
		return !dijkstra_cmp_pq_dist(a.second, b.second);
	};

	priority_queue<pr, vector<pr>, decltype(cmp_pair)> pq(cmp_pair);
	pq.push(make_pair(v, result[v] = start));

	while(!pq.empty()) {
		auto [currV, currDist] = pq.top();
		pq.pop();
		if(currDist != result[currV]) continue;
		if(currV == end) return;

		for(auto [nextV, weight] : adj[currV]) {
			DIST newDist = dijkstra_combine(currDist, weight);
			if(dijkstra_cmp_pq_dist(newDist, result[nextV])) {
				pq.push(make_pair(nextV, result[nextV] = newDist));
			}
		}
	}
}
template <typename DIST = long long, typename WEIGHT = long long, typename V = int>
void run_dijkstra_custom_v(vector<vector<pair<int,WEIGHT>>>& adj, auto& result,
	V vertex, DIST start, V end,
	auto dijkstra_cmp_pq_dist = less<>(),
	auto dijkstra_combine = [](const DIST& a, const WEIGHT& b) {
		return a + b;
	}) {


	using pr = pair<V, DIST>;

	auto cmp_pair = [&dijkstra_cmp_pq_dist](const pr& a, const pr& b) {
		// reversed because c++ pq is like that
		return !dijkstra_cmp_pq_dist(a.second, b.second);
	};

	priority_queue<pr, vector<pr>, decltype(cmp_pair)> pq(cmp_pair);
	pq.push(make_pair(vertex, result(vertex) = start));

	while(!pq.empty()) {
		auto [currV, currDist] = pq.top();
		pq.pop();
		if(currDist != result(currV)) continue;
		if(currV == end) return;

		for(auto [nextV, weight] : adj[currV]) {
			DIST newDist = dijkstra_combine(currDist, weight);
			if(dijkstra_cmp_pq_dist(newDist, result(nextV))) {
				pq.push(make_pair(nextV, result(nextV) = newDist));
			}
		}
	}
}

template <typename DIST = long long, typename WEIGHT = long long, typename V = int>
void run_dijkstra_custom_adj(auto& edges, auto& result,
	V vertex, DIST start, V end,
	auto dijkstra_cmp_pq_dist = less<>(),
	auto dijkstra_combine = [](const DIST& a, const WEIGHT& b) {
		return a + b;
	}) {


	using pr = pair<int, DIST>;

	auto cmp_pair = [&dijkstra_cmp_pq_dist](const pr& a, const pr& b) {
		// reversed because c++ pq is like that
		return !dijkstra_cmp_pq_dist(a.second, b.second);
	};

	priority_queue<pr, vector<pr>, decltype(cmp_pair)> pq(cmp_pair);
	pq.push(make_pair(vertex, result(vertex) = start));

	while(!pq.empty()) {
		auto [currV, currDist] = pq.top();
		pq.pop();
		if(currDist != result(currV)) continue;
		if(currV == end) return;

		for(auto [nextV, weight] : edges(currV)) {
			DIST newDist = dijkstra_combine(currDist, weight);
			if(dijkstra_cmp_pq_dist(newDist, result(nextV))) {
				pq.push(make_pair(nextV, result(nextV) = newDist));
			}
		}
	}
}
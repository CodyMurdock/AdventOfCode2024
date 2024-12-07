#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <set>

using namespace std;

typedef pair<int, int> pii;

pii north = { -1, 0 };

pii padd(pii a, pii b) {
	return { a.first + b.first, a.second + b.second };
}

pii turn_right(pii dir) {
	if (dir == north) return { 0, 1 }; // east
	if (dir == make_pair(0, 1)) return { 1, 0 }; // south
	if (dir == make_pair(1, 0)) return { 0, -1 }; // west
	return north; // north
}

fstream get_input() {
	return fstream("input.txt");
}

bool in_bounds(vector<string>& grid, pii& coords)
{
	if (coords.first >= 0 && coords.first < grid.size())
	{
		if (coords.second >= 0 && coords.second < grid[coords.first].length())
		{
			return true;
		}
	}
	
	return false;
}

// simulate the remaining steps assuming we have a new blockade
bool simulate(vector<string> grid, pii start, pii dir, map<pair<pii, pii>, bool> visited, pii extra_blockade = {-1, -1})
{
	if (in_bounds(grid, extra_blockade))
	{
		grid[extra_blockade.first][extra_blockade.second] = '#';
	}

	pii curr = start;
	bool oob = false;
	while (!oob)
	{
		visited[{curr, dir}] = true;

		pii next = padd(curr, dir);
		if (!in_bounds(grid, next))
		{
			oob = true;
			break;
		}

		while (grid[next.first][next.second] == '#')
		{
			dir = turn_right(dir);
			next = padd(curr, dir);
		}

		curr = next;

		if (visited[{curr, dir}])
		{
			return true;
		}
	}

	return false;
}

int main()
{
	fstream f = get_input();
	string ln;
	
	vector<string> grid;
	map<pair<pii, pii>, bool> visited;
	set<pii> tried;
	pii dir = north;
	pii start = { 0, 0 };
	int r = 0;
	while (getline(f, ln))
	{
		grid.push_back(ln);
		for (int c = 0; c < ln.length(); c++)
		{
			if (ln[c] == '^')
			{
				start = { r, c };
				break;
			}
		}
		r++;
	}

	bool oob = false;
	pii curr = start;
	long options = 0;
	while (!oob)
	{
		visited[{curr, dir}] = true;

		pii next = padd(curr, dir);
		if (!in_bounds(grid, next))
		{
			oob = true;
			break;
		}

		while (grid[next.first][next.second] == '#')
		{
			dir = turn_right(dir);
			next = padd(curr, dir);
		}

		if (tried.find(next) == tried.end())
		{
			if (simulate(grid, curr, dir, visited, next))
			{
				options++;
			}

			tried.insert(next);
		}

		curr = next;
	}
	
	cout << "P2: " << options << endl;
}
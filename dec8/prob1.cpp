#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <utility>

bool within_bound(std::pair<int, int>& p, std::set<std::pair<int, int>>& unique_antinodes, int nrows, int ncols, int x, int y){
    int nx = p.first + x;
    int ny = p.second + y;
    std::pair<int, int> t= std::make_pair(nx, ny);
    if(nx >= 0 && nx < nrows && ny >= 0 && ny < ncols){
        unique_antinodes.insert(t);
        return true;
    }
    return false;
}
int main()
{
    std::ifstream inp_file;
    inp_file.open("input.txt");
    if(inp_file.is_open()){
        std::string line;
        int n;
        std::unordered_map<char, std::vector<std::pair<int, int>>> antennas;
        int line_count = 0;
        while(std::getline(inp_file, line)){
            n = line.size();
            for(int i = 0; i < n; i++){
                if(line[i] != '.' && line[i] != '#')
                    antennas[line[i]].push_back(std::make_pair(line_count, i));
            }
            line_count++;
        }
        int nrows = line_count;
        int ncols = n;
        int antenna_count = 0;
        std::set<std::pair<int, int>> unique_antinodesp1, unique_antinodesp2;

        for(auto& x: antennas){
            std::vector<std::pair<int, int>>& temp = x.second;
            for(int i = 0; i < temp.size(); i++){
                for(int j = i + 1; j < temp.size(); j++){
                    int xd = temp[j].first - temp[i].first;
                    int yd = temp[j].second - temp[i].second;
                    bool v1 = true;
                    bool v2 = true;

                    //part 1
                    within_bound(temp[j], unique_antinodesp1, nrows, ncols, xd, yd);
                    within_bound(temp[i], unique_antinodesp1, nrows, ncols, -xd, -yd);

                    //part 2
                    for(int k = 1; v1 || v2 == true; k++){
                        v1 = within_bound(temp[j], unique_antinodesp2, nrows, ncols, xd * k, yd * k);
                        v2 = within_bound(temp[i], unique_antinodesp2, nrows, ncols, -xd * k, -yd * k);
                    }
                }
            }
            antenna_count += temp.size();
        }
        for (auto& x: unique_antinodesp2){
            bool f = false;
            for(auto& y: antennas){
                for(int i = 0; i < y.second.size() && !f; i++){
                    if(y.second[i] == x){
                        f = true;
                        antenna_count--;
                    }
                }
                if(f == true)
                    break;
            }
        }
        std::cout << unique_antinodesp1.size() << std::endl;
        std::cout << unique_antinodesp2.size() + antenna_count << std::endl;
    }
    inp_file.close();
}

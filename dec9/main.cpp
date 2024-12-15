#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>

unsigned long long int file_sum(int a, int n, int block_id){
    unsigned long long int s = (((2 * a) + n - 1) * n) / 2;
    return s * block_id;
}
int main()
{
    std::ifstream inp_file;
    inp_file.open("input.txt");
    if(inp_file.is_open()){
        std::string line;
        std::getline(inp_file, line);
        std::string cline = line;
        int n = line.size();
        int last_block_ptr = n % 2 == 0 ? n - 2 : n - 1;
        int ptr, block_id, block_ind;
        ptr = block_id = block_ind = 0;

        //part 1
        unsigned long long int checksum1 = 0;
        while(ptr <= last_block_ptr){
            if(ptr % 2 == 0){
                checksum1 += file_sum(block_ind, line[ptr] - '0', ptr/2);
                block_ind += (line[ptr] - '0');
                ptr++;
            } else {
                int t = std::min(line[ptr] - '0', line[last_block_ptr] - '0');
                checksum1 += file_sum(block_ind, t, last_block_ptr/2);

                line[ptr] -= t;
                line[last_block_ptr] -= t;
                block_ind += t;

                if(line[ptr] == '0')
                    ptr++;
                if(line[last_block_ptr] == '0'){
                    last_block_ptr -= 2;
                }
            }
        }
        std::cout << checksum1 << std::endl;

        //part 2
        unsigned long long int checksum2 = 0;
        std::vector<std::queue<int>> files_by_size(10);
        std::unordered_map<int, char> moved;
        last_block_ptr = n % 2 == 0 ? n - 2 : n - 1;
        block_ind = 0;
        for(int i = last_block_ptr; i >= 0; i-=2){
            files_by_size[cline[i] - '0'].push(i);
        }
        for(ptr = 0; ptr < n; ){
            if(ptr % 2 == 0){
                if(moved.find(ptr) == moved.end()){
                    checksum2 += file_sum(block_ind, cline[ptr] - '0', ptr/2);
                    block_ind += (cline[ptr] - '0');
                } else {
                    block_ind += (moved[ptr] - '0');
                }
                ptr++;
            } else {
                int cur_space = cline[ptr] - '0';
                int max_ind = -1;
                int vec_ind = -1;
                for(int j = 1; j <= cur_space; j++){
                    std::queue<int>& temp = files_by_size[j];
                    if(!temp.empty() && (max_ind < temp.front()) && temp.front() > ptr){
                        max_ind = temp.front();
                        vec_ind = j;
                    }
                }
                if(max_ind == -1){
                    ptr++;
                    block_ind += cur_space;
                    continue;
                }

                cur_space = cline[max_ind] - '0';
                checksum2 += file_sum(block_ind, cur_space, max_ind/2);
                files_by_size[vec_ind].pop();

                moved[max_ind] = cline[max_ind];
                block_ind += cur_space;
                cline[max_ind] = '0';
                cline[ptr] -= cur_space;

                if(cline[ptr] == '0')
                    ptr++;
            }
        }
        std::cout << checksum2 << std::endl;
    }
    inp_file.close();
    return 0;
}

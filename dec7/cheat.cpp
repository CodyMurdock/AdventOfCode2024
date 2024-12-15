#include <fstream>
#include <string>
#include <vector>
#include <iostream>

std::vector<long int> tokenize(std::string s)
{
    std::vector<long int > tokens;
    long int num = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == ' ' || s[i] == ':'){
            if(i - 1 >= 0 && s[i - 1] != ':'){
                tokens.push_back(num);
                num = 0;
            }
        }
        else
            num = num * 10 + (s[i] - '0');
    }
    tokens.push_back(num);
    return tokens;
}

long int concatenate(long int a, long int b)
{
    int count = 0;
    long int x = b;
    while(b > 0){
        count++;
        b /= 10;
    }
    for(int i = 0; i < count; i++)
        a *= 10;
    return a + x;
}

bool evaluate_tokens(std::vector<long int>& tokens, int ptr, long int sum, bool part)
{
    if(sum == tokens[0] && ptr == tokens.size())
        return true;
    if(ptr >= tokens.size() || sum > tokens[0])
        return false;

    if(evaluate_tokens(tokens, ptr + 1, sum + tokens[ptr], part))
        return true;
    if(evaluate_tokens(tokens, ptr + 1, sum * tokens[ptr], part))
        return true;

    if(part && evaluate_tokens(tokens, ptr + 1, concatenate(sum, tokens[ptr]), part))
        return true;

    return false;
}

int main()
{
    std::ifstream inp_file;
    inp_file.open("input.txt");
    long int sum1, sum2;
    sum1 = sum2 = 0;
    if(inp_file.is_open()){
        std::string line;
        while(std::getline(inp_file, line)){
            std::vector<long int> tokens = tokenize(line);
            //part 1
            if(evaluate_tokens(tokens, 2, tokens[1], false))
                sum1 += tokens[0];
            //part 2
            if(evaluate_tokens(tokens, 2, tokens[1], true))
                sum2 += tokens[0];
        }
    }
    std::cout << sum1 << std::endl;
    std::cout << sum2 << std::endl;
    return 0;
}

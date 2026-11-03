#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Assessment 01 Q4; see 题面.pdf.
namespace aim::q4 {
struct CommandResult { long long value; int accepted; int rejected; };

// BEGIN IMPLEMENTATION
CommandResult execute(const std::vector<std::string>& lines) {
    using  namespace std;
    //初始化返回值
    long long value = 0;
    int accepted = 0;
    int rejected = 0;
    //逐条读取命令
    for (const auto& line : lines) {
        istringstream input(line);
        string command;
        //处理空字符串或只有空格的行
        if (!(input >> command)) {
            rejected++;
            continue;
        }
        bool valid = false;
        long long candidate =  value;
        string extra;
        //识别命令名称并处理
        if (command == "ADD" or command == "SET"){
            long long x;
            //尝试读取参数x，并检查尾部是否有多余内容
            if ((input) >> x && !(input >> extra)){
                //检查参数x的范围
                if(x >= -1000000 && x <= 1000000){
                    if (command == "ADD"){
                        candidate += x;
                    }
                    else{
                        candidate = x;
                    }
                    //检查计算后的最终值是否在范围内
                    if(candidate >= -1000000 && candidate <= 1000000){
                        valid = true;
                    }       
                }
                    
            }
      
        }
        else if (command == "RESET"){
            //RESET命令不允许有参数，检查是否还能读取到其他内容
            if (!(input >> extra)){
                candidate = 0;
                valid = true;
            }
        }
        if (valid){
            value = candidate;
            accepted++;
        }
        else{
            rejected++;
        }

        
    }
    return {value, accepted, rejected};
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q4;
int main() {
    try {
        { aim::q4::CommandResult r=execute({"ADD 5","SET 8 x","RESET","ADD -2"}); CHECK(r.value==-2 && r.accepted==3 && r.rejected==1); }
        { aim::q4::CommandResult r=execute({}); CHECK(r.value==0 && r.accepted==0 && r.rejected==0); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}

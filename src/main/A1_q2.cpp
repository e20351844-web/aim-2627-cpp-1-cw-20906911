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

// Assessment 01 Q2; see 题面.pdf.
namespace aim::q2 {
struct LabelEdit { std::string from; std::string to; };

// BEGIN IMPLEMENTATION
using namespace std;
std::string edit_labels(std::string labels, const std::vector<LabelEdit>& edits) {
    vector<string> vec;
    //开始切割原始字符串
    if (!labels.empty()){
        stringstream ss(labels);
        string str;
        while (getline(ss,str,',')){
            vec.push_back(str);
        }
    }
    //按照edits挨个执行操作
    for (const auto& edit:edits){
        //情况一：from为空，to不为空，追加
        if (edit.from.empty() && !edit.to.empty()){
            //追加
            vec.push_back(edit.to);
        }
        //情况二：from不为空，to为空，删除
        else if(!edit.from.empty()){
            //查找删除和替换
            for (auto it = vec.begin(); it != vec.end();++it){
                if (*it ==edit.from){
                    if (edit.to.empty()){
                        vec.erase(it);
                    }
                    else{
                        *it = edit.to;
                    }
                    break;
                }
            }
        }
        //情况三：from和to都为空，什么都不做
        else{
        
        }
    }
        //把数组重新拼接成字符串
        string result = "";
        for (size_t i = 0; i < vec.size(); ++i){
            if (i != 0){
                result += ",";
            }
            result += vec[i];
        }
        return result; 
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q2;
int main() {
    try {
        { CHECK(edit_labels("cam,imu,radar",{{"imu","gyro"},{"cam",""},{"","lidar"}})=="gyro,radar,lidar"); }
        { CHECK(edit_labels("cam,cam2,cam",{{"cam","camera"},{"cam",""}})=="camera,cam2"); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}

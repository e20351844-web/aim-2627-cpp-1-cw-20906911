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

// Assessment 01 Q8; see 题面.pdf.
namespace aim::q8 {
struct Telemetry { int id; int hp; };
struct Summary { int valid; int duplicate; int invalid; long long total_hp; std::vector<int> ids; };

// BEGIN IMPLEMENTATION
Summary summarize(const std::vector<Telemetry>& frames) {
    Summary res{0, 0, 0, 0, {}};
    std::vector<bool> seen(10000, false);//记录编号是否已出现过
    for (const auto& frame : frames) {
        //范围验证：id必须在0-9999之间，hp必须在-1000到1000之间
        //只要有一个不符合要求，就算作invalid
        if (frame.id < 0 || frame.id > 9999 || frame.hp < -1000 || frame.hp > 1000) {
            ++res.invalid;
            continue;
        } 
        //判断重复，完全合法后才去查标记表
        if (seen[frame.id]){
            res.duplicate++;
            continue;
        }
        //首次处理合法记录
        res.valid++;
        seen[frame.id] = true;
        int clamped_hp = std::max(0, std::min(100, frame.hp)); //将hp限制在0-100之间
        res.total_hp += clamped_hp;
    }
    for (int i = 0; i <= 9999;++i){
        if (seen[i]){
            res.ids.push_back(i);
        }
    }
    return res;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q8;
int main() {
    try {
        { aim::q8::Summary r=summarize({{2,200},{1,-5},{2,10},{-1,30}}); CHECK(r.valid==2 && r.duplicate==1 && r.invalid==1 && r.total_hp==100 && (r.ids==std::vector<int>{1,2})); }
        { aim::q8::Summary r=summarize({{1,-1001},{1,30},{1,1001}}); CHECK(r.valid==1 && r.duplicate==0 && r.invalid==2 && r.total_hp==30 && (r.ids==std::vector<int>{1})); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}

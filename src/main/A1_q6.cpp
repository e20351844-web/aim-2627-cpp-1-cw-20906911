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

// Assessment 01 Q6; see 题面.pdf.
namespace aim::q6 {
struct Target { int id; int x; int y; int hp; bool visible; };

// BEGIN IMPLEMENTATION
int select_target(const std::vector<Target>& targets, int max_range) {
    using namespace std;
    using WideInt = long long;
    if (max_range < 0 || targets.empty()) {
        return -1;
    }
    const WideInt range_squared =
    static_cast<WideInt>(max_range) *
    static_cast<WideInt>(max_range);
    //保存当前最佳目标
    bool found_target = false;
    int best_id = -1;
    int best_hp = 0;
    WideInt best_distance_squared = 0;
    //遍历检查目标
    for (const Target& target : targets) {
        const WideInt x = target.x;
        const WideInt y = target.y;
        const WideInt distance_squared = x * x + y * y;
        if (target.visible == true && target.hp > 0 && distance_squared <= range_squared){
            best_id = target.id;
            best_hp = target.hp;
        }else {
            continue;
        }
        if (target.hp < best_hp) {
            best_id = target.id;
            best_hp = target.hp;
        } else if (target.hp == best_hp && distance_squared < best_distance_squared) {
            best_id = target.id;
            best_distance_squared = distance_squared;
        }else if (target.hp == best_hp && distance_squared == best_distance_squared && target.id < best_id) {
            best_id = target.id;
        }
    }
    return best_id;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q6;
int main() {
    try {
        { CHECK(select_target({{7,3,4,20,true},{2,0,5,20,true}},5)==2); }
        { CHECK(select_target({},5)==-1); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}

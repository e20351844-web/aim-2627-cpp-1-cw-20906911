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

// Assessment 01 Q1; see 题面.pdf.
namespace aim::q1 {


// BEGIN IMPLEMENTATION
//分两步，写两个函数，ratio先写，后面判断状态能用
long long ratio(long long hp, long long max_hp) {
    if (max_hp <= 0){
        return -1;
    }
    if (hp < 0){
        hp =0;//健康值限制不能直接 return
    }
    else if (hp > max_hp){
        hp = max_hp;
    }
    return hp * 100 / max_hp;//百分比要先乘再除，否则 2 / 3 会先变成 0
}
using namespace std;
std::string report(int id, long long hp, long long max_hp, int battery) {
    long long hp_ratio = ratio(hp, max_hp);
    string hp_str;
    if (hp_ratio == -1){
        hp_str = "INVALID";
    }
    else {
        hp_str = to_string(hp_ratio);
    }
    if (battery < 0){
        battery = 0;
    }
    else if (battery > 100){
        battery = 100;
    }
    string state;
    if (battery >=60){
        state = "OK";
    }
    else if (battery >= 20){
        state = "WARNING";
    }
    else {
        state = "LOW";
    }
    return "ID=" + to_string(id) + ";HP=" + hp_str + ";BAT=" + to_string(battery) + ";STATE=" + state;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q1;
int main() {
    try {
        { CHECK(ratio(2,3)==66); }
        { CHECK(report(7,2,3,20)=="ID=7;HP=66;BAT=20;STATE=WARNING"); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}

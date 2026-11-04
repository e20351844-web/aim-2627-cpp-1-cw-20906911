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

// Assessment 01 Q5; see 题面.pdf.
namespace aim::q5 {


// BEGIN IMPLEMENTATION
std::vector<std::vector<int>> risk(const std::vector<std::string>& grid) {
    using namespace std;
    using RiskMatrix = vector<std::vector<int>>;
    //地图基本尺寸
    const size_t row_count = grid.size();
    size_t column_count = 0;
    //处理空地图
    //grid为空时直接返回空矩阵
    if (row_count == 0) {
        return {};
    }
    //读取列数
    //使用第一行长度作为column_count
    column_count = grid[0].size();
    //验证地图
    //检查
    //column_count不能为0
    if (column_count == 0) {
        throw invalid_argument("Zero columns are not allowed");
    }
    //检查每行长度是否一致
    //每个字符必须是'.'或'#'
    for (size_t r = 0; r < row_count; ++r) {
        if (grid[r].size() != column_count) {
            throw invalid_argument("Inconsistent row length");
        }
        for (char ch : grid[r]) {
            if (ch != '.' && ch != '#') {
                throw invalid_argument("Invalid character in grid");
            }
        }
    }
    //创建和输入地图同样大小的结果的矩阵
    RiskMatrix result(row_count, vector<int>(column_count, 0)); 
    //四邻域方向：上下左右
    constexpr int direction_count = 4;
    const array<int,direction_count> row_offset = {-1, 1, 0, 0};
    const array<int,direction_count> column_offset = {0, 0, -1, 1};
    //计算风险值
    //遍历每一行，每一列
    for (size_t r = 0; r < row_count; ++r) {
        for (size_t c = 0; c < column_count; ++c) {
            //如果当前格子是#，结果写入-1
            if (grid[r][c] == '#') {
                result[r][c] = -1;
            }
            else{
                //如果当前格子是.初始化adjacent_obstacles = 0
                int adjacent_obstacles = 0;
                //检查四个方向
                for (int i =0; i < direction_count; ++i) {
                    int nr = static_cast<int>(r) + row_offset[i];
                    int nc = static_cast<int>(c) + column_offset[i];
                    //邻居在边界内且为#时，风险加一
                    if (nr >= 0 && nr < static_cast<int>(row_count) &&
                        nc >= 0 && nc < static_cast<int>(column_count) && (grid[nr][nc] == '#')){
                            ++adjacent_obstacles;
                    }
                }
                result[r][c] = adjacent_obstacles;

            }
            
        }
    }
    return result;

}


// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q5;
int main() {
    try {
        { CHECK((risk({".#",".."})==std::vector<std::vector<int>>{{1,-1},{0,1}})); }
        { CHECK(risk({}).empty()); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}

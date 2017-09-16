#ifndef CAFETERIA_H
#define CAFETERIA_H

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <queue>
#include <iterator>

using std::string;
using std::map;
using std::queue;
using std::vector;
using std::pair;

/*枚举类型
 * Type：菜品类型（无类型，主食，热菜，凉菜，饮品）
 * State:餐桌状态（空闲，无服务员，点菜中，点菜完毕，厨师做菜，上菜完毕）
*/
//enum Type{noType,stapleFood,hotDishes,coldDishes,drink};
enum State{unoccupied,nowaiter,order,orderfinish,prepare,ready};

#endif // CAFETERIA_H

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
 * State:餐桌状态（空闲，点菜中，点菜完毕，厨师做菜，上菜完毕）
*/
enum State{unoccupied,order,orderfinish,ready};

#endif // CAFETERIA_H

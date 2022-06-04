#ifndef Q1_H
#define Q1_H
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

namespace q1 {
    template <typename T, typename F>
    T gradient_descent(T initial_value, T step, F function = F())
    {
        double now_pos{initial_value};
        while (true) {
            double new_pos{0};
            if(function(now_pos - step)<function(now_pos)){
                new_pos=now_pos - step;
            }else{
                new_pos=now_pos; 
            }
            if(function(now_pos + step)<function(new_pos)){
                new_pos=now_pos + step;
            }
            if(new_pos==now_pos){
                return now_pos;
            }
            now_pos=new_pos;
        }
    }
}
#endif //Q1_H
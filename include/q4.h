#ifndef Q4_H
#define Q4_H
namespace q4 {

struct Vector2D {
    Vector2D() = default;
    Vector2D(double _x, double _y)
        : x(_x)
        , y(_y) {};

    double x {};
    double y {};
};

struct Sensor {
    Sensor(q4::Vector2D _pos, double _accuracy)
        : pos(_pos)
        , accuracy(_accuracy) {};

    Vector2D pos;
    double accuracy;
};


inline double cal_sum(std::vector<Sensor>::iterator it ,std::vector<Sensor>::iterator end,std::string option){
    if(it==end){
        return 0;
    }
    if(option=="y"){
        return it->pos.y * it->accuracy + cal_sum(++it,end,option);
    }
    if(option=="x"){
        return it->pos.x * it->accuracy + cal_sum(++it,end,option);
    }
    if(option=="acc"){
        return  it->accuracy + cal_sum(++it,end,option);
    }
    return 0;
}

inline q4::Vector2D kalman_filter(std::vector<Sensor> sensors)
{
    double size { cal_sum(sensors.begin(), sensors.end(),"acc") };
    double weighted_sum_x = cal_sum(sensors.begin(), sensors.end(),"x") / size;
    double weighted_sum_y = cal_sum(sensors.begin(), sensors.end(),"y") / size;
    q4::Vector2D v(weighted_sum_x, weighted_sum_y);
    return v;
}
}
#endif //Q4_H
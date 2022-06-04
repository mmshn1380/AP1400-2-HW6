#ifndef Q3_H
#define Q3_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <regex>
#include <sstream>
#include <string>

namespace q3 {

struct Flight {
    Flight(std::string _flight_number, size_t _duration, size_t _connections, size_t _connection_times, size_t _price)
        : flight_number { _flight_number }
        , duration { _duration }
        , connections { _connections }
        , connection_times { _connection_times }
        , price { _price }
    {
    }
    std::string flight_number;
    size_t duration;
    size_t connections;
    size_t connection_times;
    size_t price;
};
struct comp {
    bool operator()(const Flight& F1, const Flight& F2)
    {
        return (F1.duration) + (F1.connection_times) + 3 * (F1.price) > (F2.duration) + (F2.connection_times) + 3 * (F2.price);
    }
};

inline std::vector<std::string> split(std::string str,char c){
    std::vector<std::string> v;
    std::stringstream s(str);
    std::string word;
    while (getline(s, word, c)) {
        while(word.back()==' '){
            word.pop_back();
        }
        while(word[0]==' '){
            word.erase(word.begin());
        }
        v.push_back(word);
    }
    return v;
}
inline int calc_time(std::string t){
    int dur_h=0,dur_m=0;
    if(t.find("h")!=std::string::npos){
        dur_h=stoi(split(t,'h')[0]);
        if(t.find("m")!=std::string::npos){
            std::string buf { split(t,'h')[1]};
            buf.pop_back();
            dur_m=stoi(buf);
        }
    }else{
        t.pop_back();
        dur_m=stoi(t);
    }
    return dur_h*60+dur_m;
}
inline std::priority_queue<Flight, std::vector<Flight>, comp> gather_flights(std::string filename)
{
    // reading file
    std::priority_queue<Flight, std::vector<Flight>, comp> F {};
    std::fstream fin;
    fin.open(filename, std::ios::in);
    std::vector<std::string> row;
    std::string line, word;
    while (getline(fin, line)) {
        auto base_param=split(line,'-');
        std::string flight_number =split(base_param[1],':')[1];
        std::string duration =split(base_param[2],':')[1];
        int dur=calc_time(duration);
        int connections =stoi(split(base_param[3],':')[1]);
        std::string connection_times =split(base_param[4],':')[1];
        int price {stoi(split(base_param[5],':')[1])};
        int connection_time{0};
        int x=connections;
        while(x--){
            connection_time+=calc_time(split(connection_times,',')[x]);
        }
        F.push(Flight(flight_number, dur, connections, connection_time , price));
    }
    return F;
}
}

#endif //Q3_H
#ifndef Q2_H
#define Q2_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace q2 {

struct Patient {
    Patient(std::string _name, size_t _age, size_t _smokes, size_t _area_q, size_t _alkhol)
        : name { _name }
        , age { _age }
        , smokes { _smokes }
        , area_q { _area_q }
        , alkhol { _alkhol }
    {
    }

    std::string name;
    size_t age;
    size_t smokes;
    size_t area_q;
    size_t alkhol;
};

inline std::vector<Patient> read_file(std::string filename)
{
    std::vector<Patient> P {};
    std::fstream fin;
    fin.open(filename, std::ios::in);
    std::vector<std::string> row;
    std::string line, word;
    while (getline(fin, line)) {
        row.clear();
        std::stringstream s(line);
        while (getline(s, word, ',')) {
            row.push_back(word);
        }
        if(row.size()<5 || row[0]=="Name"){
            continue;
        }
        if(row[0].back()!=' '){
            row[0].append(" ");
        }
        P.push_back(Patient(row[0] + row[1], stoi(row[2]), stoi(row[3]), 
        stoi(row[4]),stoi(row[5])));
    }
    return P;
}

inline bool comp(const Patient& P1, const Patient& P2)
{
    size_t x { 3 * (P1.age) + 5 * (P1.smokes) + 2 * (P1.area_q) + 4 * (P1.alkhol) };
    size_t y { 3 * (P2.age) + 5 * (P2.smokes) + 2 * (P2.area_q) + 4 * (P2.alkhol) };
    return x > y;
}

inline void sort(std::vector<Patient>& P)
{
    std::sort(P.begin(), P.end(), comp);
}
}
#endif //Q2_H
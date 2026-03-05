#pragma once
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <string_view>
#include <string>
#include "geo.h"

struct Bus {
    std::string name;
    std::unordered_set<std::string_view> route;
    bool circle = false;

};

struct Stop{
    std::string name;
    Coordinates coordinates;
};

//using Bus =  std::unordered_map<std::strig,std::unordered_set<string_view>>;
//using Stop = std::unordered_map<std::string, std::pair<std::string,std::string>>;

class TransportCatalogue {
	// Реализуйте класс самостоятельно
public:
    void AddBusRoute(Bus bus);
    void AddBusStop(Stop stop);
    const Bus* FindRouteByName(std::string_view name) const;
    const Stop* FindBusStopByName(std::string_view name) const;
    void GetRouteInfo(std::string_view request) const;
    static void TrimStr(std::string &str){
        size_t begin = str.find_first_not_of(' ');
        size_t end = str.find_last_not_of(' ')+1;
        str = str.substr(begin,end-begin);
    }

private:
    std::unordered_map<std::string_view,const Stop *> stop_indexes_;
    std::unordered_map<std::string_view,const Bus *> bus_indexes_;
    std::deque<Stop> stops_;
    std::deque<Bus> buses_;

};


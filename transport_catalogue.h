#pragma once
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <string_view>
#include <vector>
#include <string>
#include "geo.h"

struct Bus {
    std::string name;
    std::vector<std::string_view> route;
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
    double GetDistance(std::pair<Stop *, Stop *>);

private:
    std::unordered_map<std::string_view,const Stop *> stop_indexes_;
    std::unordered_map<std::string_view,const Bus *> bus_indexes_;
    std::deque<Stop> stops_;
    std::deque<Bus> buses_;

};


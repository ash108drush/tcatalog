#include "transport_catalogue.h"
#include <iostream>
#include <cmath>

void TransportCatalogue::AddBusRoute(Bus bus){
    auto pos = buses_.insert(buses_.end(),bus);
    bus_indexes_.insert({pos->name,&(*pos)});

}
void TransportCatalogue::AddBusStop(Stop stop){

   auto pos=  stops_.insert(stops_.end(),stop);
   stop_indexes_.insert({pos->name,&(*pos)});

}
const Bus* TransportCatalogue::FindRouteByName(std::string_view name) const{

    return bus_indexes_.at(name);
}

const Stop* TransportCatalogue::FindBusStopByName(std::string_view name) const
{
    return stop_indexes_.at(name);

}

void TransportCatalogue::GetRouteInfo(std::string_view request) const
{
    const Bus* bus = FindRouteByName(request);
    std::cout << bus->route.size() << "circle" << bus->circle << std::endl;
    int stops_on_route = bus->route.size();
    std::unordered_set<std::string_view> bus_set;
    for(std::string_view stop_name : bus->route){
        bus_set.insert(stop_name);

    }
    int uniq_stops = bus_set.size();
    if(bus->circle) ++stops_on_route;



}

double TransportCatalogue::GetDistance(std::pair<Stop *, Stop *> point)
{
    point.first->coordinates.lat
        point.second->coordinates.lat
            point.first->coordinates.lng
                point.second->coordinates.lng
    double distance = 0;
    return distance;
}



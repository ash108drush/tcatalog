#include "transport_catalogue.h"
#include <iostream>

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
    int uniq_stops = bus->route.size();
    if(bus->circle) ++stops_on_route;



}



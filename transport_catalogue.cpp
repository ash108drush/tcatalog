#include "transport_catalogue.h"
#include <iostream>
#include "geo.h"

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
    const Stop * stop1;// = FindBusStopByName(stop_name);
    const Stop * stop2;// = FindBusStopByName(stop_name);
    bool flagfirst= true;
    double route_distance=0;
    double stop_distance=0;

    for(std::string_view stop_name : bus->route){
        bus_set.insert(stop_name);
        stop1 = stop2;
        stop2 = FindBusStopByName(stop_name);
        if(flagfirst){
            flagfirst=false;
            continue;
        }
       // stop_distance= ComputeDistance(stop1->coordinates, stop2->coordinates);
        route_distance+=stop_distance;

    }
    /*
    int uniq_stops = bus_set.size();
    if(!bus->circle){
        route_distance*=2;
    }

    std::cout << "stops" << stops_on_route << "uniq" << uniq_stops << "distance" << route_distance << std::endl;

*/


}

double TransportCatalogue::GetDistance(std::pair<Stop *, Stop *> point)
{
    return ComputeDistance(point.first->coordinates,point.second->coordinates);

}



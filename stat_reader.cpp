#include "stat_reader.h"
#include <iostream>
#include <iomanip>
void ParseAndPrintStat(const TransportCatalogue& transport_catalogue, std::string_view request,
                       std::ostream& output) {
    // Реализуйте самостоятельно
    //request = "256";
    transport_catalogue.GetRouteInfo(request);
    std::setprecision(6);
    output <<"printstat: "  << request << std::endl;
}

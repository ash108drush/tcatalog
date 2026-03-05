#include "stat_reader.h"
#include <iostream>
void ParseAndPrintStat(const TransportCatalogue& transport_catalogue, std::string_view request,
                       std::ostream& output) {
    // Реализуйте самостоятельно
    request = "256";
    transport_catalogue.GetRouteInfo(request);
    output <<"printstat: "  << request << std::endl;
}

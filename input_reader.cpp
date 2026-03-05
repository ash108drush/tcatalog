#include "input_reader.h"

#include <algorithm>
#include <cassert>
#include <iterator>
#include <iostream>
#include <array>
#include<string>

using namespace std;
/**
 * Парсит строку вида "10.123,  -30.1837" и возвращает пару координат (широта, долгота)
 */
Coordinates ParseCoordinates(std::string_view str) {
    static const double nan = std::nan("");

    auto not_space = str.find_first_not_of(' ');
    auto comma = str.find(',');

    if (comma == str.npos) {
        return {nan, nan};
    }

    auto not_space2 = str.find_first_not_of(' ', comma + 1);

    double lat = std::stod(std::string(str.substr(not_space, comma - not_space)));
    double lng = std::stod(std::string(str.substr(not_space2)));

    return {lat, lng};
}

/**
 * Удаляет пробелы в начале и конце строки
 */
std::string_view Trim(std::string_view string) {
    const auto start = string.find_first_not_of(' ');
    if (start == string.npos) {
        return {};
    }
    return string.substr(start, string.find_last_not_of(' ') + 1 - start);
}

/**
 * Разбивает строку string на n строк, с помощью указанного символа-разделителя delim
 */
std::vector<std::string_view> Split(std::string_view string, char delim) {
    std::vector<std::string_view> result;

    size_t pos = 0;
    while ((pos = string.find_first_not_of(' ', pos)) < string.length()) {
        auto delim_pos = string.find(delim, pos);
        if (delim_pos == string.npos) {
            delim_pos = string.size();
        }
        if (auto substr = Trim(string.substr(pos, delim_pos - pos)); !substr.empty()) {
            result.push_back(substr);
        }
        pos = delim_pos + 1;
    }

    return result;
}

/**
 * Парсит маршрут.
 * Для кольцевого маршрута (A>B>C>A) возвращает массив названий остановок [A,B,C,A]
 * Для некольцевого маршрута (A-B-C-D) возвращает массив названий остановок [A,B,C,D,C,B,A]
 */
std::vector<std::string_view> ParseRoute(std::string_view route) {
    if (route.find('>') != route.npos) {
        return Split(route, '>');
    }

    auto stops = Split(route, '-');
    std::vector<std::string_view> results(stops.begin(), stops.end());
    results.insert(results.end(), std::next(stops.rbegin()), stops.rend());

    return results;
}

CommandDescription ParseCommandDescription(std::string_view line) {
    auto colon_pos = line.find(':');
    if (colon_pos == line.npos) {
        return {};
    }

    auto space_pos = line.find(' ');
    if (space_pos >= colon_pos) {
        return {};
    }

    auto not_space = line.find_first_not_of(' ', space_pos);
    if (not_space >= colon_pos) {
        return {};
    }

    return {std::string(line.substr(0, space_pos)),
            std::string(line.substr(not_space, colon_pos - not_space)),
            std::string(line.substr(colon_pos + 1))};
}

void InputReader::ParseLine(std::string_view line) {
    auto command_description = ParseCommandDescription(line);
    if (command_description) {
        commands_.push_back(std::move(command_description));
    }
}

void InputReader::ApplyCommands([[maybe_unused]] TransportCatalogue& catalogue) const {
    // Реализуйте метод самостоятельно
    for(auto &[command, id, description] : commands_){
        if(command == "Stop"){
            std::string name = move(id);
            size_t pos = description.find(',');
            std::string pos_x = description.substr(1,pos-1);
            std::string pos_y = description.substr(pos+2, description.size() - pos -1);
            //cout <<"#" << pos_x << "#" << pos_y <<"#"<< std::endl;
            //auto coord[2] = description.split(',');
            // double latitude = 0;
            //double x = to_double(pos_x);
            //double longitude = 0; //double(pos_y);
            //cout << latitude << "y: " << longitude << std::endl;
            catalogue.AddBusStop(move(Stop{name,{std::stold(pos_x),std::stold(pos_y)}}));
            //cout << "Name: "<< id << " coords: "<< description << endl;
        }

    }

    for(auto &[command, id, description] : commands_){
        if(command == "Bus") {
            std::string name = move(id);
            size_t pos = 0;
            bool circle = true;
            char divider = '>';
            size_t f_pos = description.find( divider);
            if(f_pos == std::string::npos){
                divider = '-';
                f_pos = description.find( divider);
                circle = false;
            }
            std::string stop_name="";
            const Stop *stop;
            std::unordered_set<std::string_view> route;
            while(f_pos != std::string::npos){

                stop_name = description.substr(pos+1, f_pos - pos -2);
                stop = catalogue.FindBusStopByName(stop_name);
                //std::cout << "smth:" << stop->name << endl;
                route.insert(stop->name);
                pos=f_pos+1;
                f_pos=description.find(divider,pos);
            }
            stop_name = description.substr(pos+1, description.size() - pos);
            stop = catalogue.FindBusStopByName(stop_name);
            route.insert(stop->name);

            catalogue.AddBusRoute(Bus{id,route,circle});
            //cout << " id: "<< id << " Route: "<< description << endl;
        }else{
            assert("Command not found");
            //cout << "c: " << command << " id: "<< id << " d: "<< description << endl;

        }
    }

}

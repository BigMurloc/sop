#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

struct Czas {
    using value_type = unsigned int;
    value_type  godzina;
    value_type  minuta;
    value_type sekunda;

    Czas(value_type, value_type, value_type);
    auto to_string() const -> std::string;
    auto next_hour() -> void;
    auto next_minute() -> void;
    auto next_second() -> void; 
}; 

Czas::Czas(value_type g, value_type m, value_type s)
    : godzina{g}
    , minuta{m}
    , sekunda{s}
{} 

auto Czas::to_string() const -> std::string {
    std::ostringstream out;
    out << std::setw(2) << std::setfill('0') << godzina << ":";
    out << std::setw(2) << std::setfill('0') << minuta << ":";
    out << std::setw(2) << std::setfill('0') << sekunda;
    return out.str();
}

auto Czas::next_hour() -> void {
    godzina++;
    if(godzina == 24){
        godzina = 0;
    }
}

auto Czas::next_minute() -> void {
    minuta++;
    if(minuta == 60){
        minuta = 0;
        next_hour();
    }
}

auto Czas::next_second() -> void {
    sekunda++;
    if(sekunda == 60){
        sekunda = 0;
        next_minute();
    }   
}

auto main() -> int  {
    auto czas = Czas(23, 59, 59);
    czas.next_second();
    std::cout << czas.to_string() << "\n";
    czas.next_hour();
    std::cout << czas.to_string() << "\n";
    czas.next_minute();
    std::cout << czas.to_string() << "\n";
    czas.next_second();
    std::cout << czas.to_string() << "\n";
    return 0;
}

#include "date.hpp"

void Date::validate(string date) {
    int pos1 = date.find('/');
    if(pos1 == string::npos) {
        throw invalid_argument("Invalid format");
}

    int pos2 = date.find('/', pos1 + 1);
    if(pos2 == string::npos) {
        throw invalid_argument("Invalid format");
}

    if (pos1 != 1 && pos1 != 2){
        throw invalid_argument("Invalid format");
    }
    int day = stoi(date.substr(0, pos1));

    if((pos2 - pos1 - 1) != 2){ 
        throw invalid_argument("Invalid format");
    }
    int month = stoi(date.substr(pos1 + 1, pos2 - pos1 - 1));
    
    if((date.size() - pos2 - 1) != 4) {
        throw invalid_argument("invalid format");
    }
    int year = stoi(date.substr(pos2 + 1));


    if (year < 2000 || year > 2999) {
        throw invalid_argument("Invalid year");
    }
    if (month < 1 || month > 12) {
        throw invalid_argument("Invalid month");
    }

    int maxDay;

    if (month == 4 || month == 6 || month == 9 || month == 11){
        maxDay = 30;
    } else if((month == 2 && year%4 == 0 && year%100 == 0 && year%400 == 0) || (month == 2 && year%4 == 0 && year%100 != 0)) { 
        maxDay = 29;
    } else if((month == 2 && year%4 != 0) || (month == 2 && year%4 == 0 && year%100 == 0 && year%400 != 0)) {
        maxDay = 28;
    } else {
        maxDay = 31;
    }

    if (day < 1 || day > maxDay) {
        throw invalid_argument("Invalid day");
    }
}

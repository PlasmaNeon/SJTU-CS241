#include "AnalogClock.h"
#include <chrono>

void AnalogClock::getTime() {
    auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    auto local = localtime(&now);
    h = local->tm_hour;
    m = local->tm_min;
    s = local->tm_sec;
    year = local->tm_year;
    month = local->tm_mon;
    day = local->tm_mday;
}

void AnalogClock::updateDigital() {
    string ss;
    ss = to_string(h) +':' + to_string(m) + ':' +to_string(s);
    digital_time.set_label(ss);
    string d = to_string(year + 1900) + '/' + to_string(month) + '/' + to_string(day);
    digital_date.set_label(d);
}

void AnalogClock::updateHand() {
    double h_angle = ((h % 12) + m /60.0 + s / 3600.0 ) / 12.0 * 2 * pi;
    double m_angle = (m + s / 60.0) / 60.0 * 2 * pi;
    double s_angle = s / 60.0 * 2 * pi;
    h_hand.updateEnd(h_angle - pi / 2);
    m_hand.updateEnd(m_angle - pi / 2);
    s_hand.updateEnd(s_angle - pi / 2);
}




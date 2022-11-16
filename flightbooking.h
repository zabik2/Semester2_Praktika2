#ifndef FLIGHTBOOKING_H
#define FLIGHTBOOKING_H

#include "booking.h"

class FlightBooking : public Booking
{
public:
    FlightBooking();
    void showDetails(FlightBooking* x);
    //void showDetails(FlightBooking *x);
    virtual ~FlightBooking();
    void setFromDestination(const std::string &newFromDestination);

    void setToDestination(const std::string &newToDestination);

    void setAirline(const std::string &newAirline);

    const std::string &getFromDestination() const;

    const std::string &getToDestination() const;

    const std::string &getAirline() const;

private:
    std::string fromDestination;
    std::string toDestination;
    std::string airline;
};

#endif // FLIGHTBOOKING_H

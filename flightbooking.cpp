#include "flightbooking.h"

FlightBooking::FlightBooking()
{

}

void FlightBooking::showDetails(FlightBooking *x)
{
    std::cout << "Flugbuchung " << x->getId() << " von " << x->getFromDestination() << " nach " << x->getToDestination() << " mit " << x->getAirline()
              << " am " << x->getFromDate() << ". Preis: " << x->getPrice() << " Euro " << std::endl;
}

FlightBooking::~FlightBooking()
{

}




void FlightBooking::setFromDestination(const std::string &newFromDestination)
{
    fromDestination = newFromDestination;
}

void FlightBooking::setToDestination(const std::string &newToDestination)
{
    toDestination = newToDestination;
}

void FlightBooking::setAirline(const std::string &newAirline)
{
    airline = newAirline;
}

const std::string &FlightBooking::getFromDestination() const
{
    return fromDestination;
}

const std::string &FlightBooking::getToDestination() const
{
    return toDestination;
}

const std::string &FlightBooking::getAirline() const
{
    return airline;
}



#ifndef TRAVELAGENCY_H
#define TRAVELAGENCY_H

#include "booking.h"
#include "flightbooking.h"
#include "hotelbooking.h"
#include "rentalcarreservation.h"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>

class TravelAgency
{
public:
    TravelAgency();
    void readFile(std::string FileName);
    void readBinaryFile();
    ~TravelAgency();

    std::vector<FlightBooking*> FlightsList;
    std::vector<HotelBooking*> HotelList;
    std::vector<RentalCarReservation*> RentalCarList;
    std::vector<Booking*> BookingList;

private:
};

#endif // TRAVELAGENCY_H

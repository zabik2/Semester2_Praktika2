#ifndef HOTELBOOKING_H
#define HOTELBOOKING_H

#include "booking.h"

class HotelBooking : public Booking
{
public:
    HotelBooking();
    void showDetails(HotelBooking *x);
    virtual ~HotelBooking();
    void setHotel(const std::string &newHotel);

    void setTown(const std::string &newTown);

    const std::string &getHotel() const;

    const std::string &getTown() const;

private:
    std::string Hotel;
    std::string Town;
};

#endif // HOTELBOOKING_H

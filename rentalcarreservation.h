#ifndef RENTALCARRESERVATION_H
#define RENTALCARRESERVATION_H

#include "booking.h"

class RentalCarReservation : public Booking
{
public:
    RentalCarReservation();
    void showDetails(RentalCarReservation *x);
    virtual ~RentalCarReservation();
    void setPickupLocation(const std::string &newPickupLocation);

    void setReturnLocation(const std::string &newReturnLocation);

    void setCompany(const std::string &newCompany);

    const std::string &getCompany() const;

    const std::string &getPickupLocation() const;

    const std::string &getReturnLocation() const;

private:
    std::string pickupLocation;
    std::string returnLocation;
    std::string company;

};

#endif // RENTALCARRESERVATION_H

#include "rentalcarreservation.h"

RentalCarReservation::RentalCarReservation()
{

}

void RentalCarReservation::showDetails(RentalCarReservation *x)
{
    std::cout << "Mietwagenreservierung " << x->getId() << " mit " << x->getCompany() << ". Abholung am " << x->getFromDate() << " in " << x->getPickupLocation()
              << ". Rueckgabe am " << x->getToDate() << " in " << x->getReturnLocation() << ". Preis: " << x->getPrice() << " Euro " << std::endl;
}

RentalCarReservation::~RentalCarReservation()
{

}

void RentalCarReservation::setPickupLocation(const std::string &newPickupLocation)
{
    pickupLocation = newPickupLocation;
}

void RentalCarReservation::setReturnLocation(const std::string &newReturnLocation)
{
    returnLocation = newReturnLocation;
}

void RentalCarReservation::setCompany(const std::string &newCompany)
{
    company = newCompany;
}

const std::string &RentalCarReservation::getCompany() const
{
    return company;
}

const std::string &RentalCarReservation::getPickupLocation() const
{
    return pickupLocation;
}

const std::string &RentalCarReservation::getReturnLocation() const
{
    return returnLocation;
}

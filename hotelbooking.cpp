#include "hotelbooking.h"

HotelBooking::HotelBooking()
{

}

void HotelBooking::showDetails(HotelBooking *x)
{
    std::cout << "Hotelreservierung " << x->getId() << " im " << x->getHotel() << " in " << x->getTown() << " vom " << x->getFromDate()
              << " bis zum " << x->getToDate() << ". Preis: " << x->getPrice() << " Euro " << std::endl;
}

HotelBooking::~HotelBooking()
{

}

void HotelBooking::setHotel(const std::string &newHotel)
{
    Hotel = newHotel;
}

void HotelBooking::setTown(const std::string &newTown)
{
    Town = newTown;
}

const std::string &HotelBooking::getHotel() const
{
    return Hotel;
}

const std::string &HotelBooking::getTown() const
{
    return Town;
}

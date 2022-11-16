#include "booking.h"

Booking::Booking()
{

}

Booking::Booking(int id, double price, const std::string &fromDate, const std::string &toDate) : id(id),
    price(price),
    fromDate(fromDate),
    toDate(toDate)
{}

void Booking::showDetails(Booking *x)
{

}

Booking::~Booking()
{

}

void Booking::setId(int newId)
{
    id = newId;
}

void Booking::setPrice(double newPrice)
{
    price = newPrice;
}

void Booking::setFromDate(const std::string &newFromDate)
{
    fromDate = newFromDate;
}

void Booking::setToDate(const std::string &newToDate)
{
    toDate = newToDate;
}

double Booking::getPrice() const
{
    return price;
}

int Booking::getId() const
{
    return id;
}

const std::string &Booking::getFromDate() const
{
    return fromDate;
}

const std::string &Booking::getToDate() const
{
    return toDate;
}

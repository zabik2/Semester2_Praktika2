#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <vector>
#include <iostream>

class Booking
{
public:
    Booking();
    Booking(int id, double price, const std::string &fromDate, const std::string &toDate);
    virtual void showDetails(Booking* x);
    virtual ~Booking();
    void setId(int newId);

    void setPrice(double newPrice);

    void setFromDate(const std::string &newFromDate);

    void setToDate(const std::string &newToDate);

    double getPrice() const;

    int getId() const;

    const std::string &getFromDate() const;

    const std::string &getToDate() const;

protected:
    int id;
    double price;
    std::string fromDate;
    std::string toDate;
};

#endif // BOOKING_H

#include "travelagency.h"
#include "flightbooking.h"
#include "hotelbooking.h"
#include "rentalcarreservation.h"
#include <iostream>
#include <QMessageBox>
#include <QWidget>
#include <QFileDialog>
#include <QMainWindow>
#include <QLabel>
#include <sstream>

void Search (std::ifstream& x, char y, std::string &z); // avoids repeats in search for chars in txt

TravelAgency::TravelAgency()
{

}

void  TravelAgency::readFile(std::string FileName)
{
    float FlightNum = 0, FlightCost = 0, CarNum = 0, CarCost = 0, HotelNum = 0, HotelCost = 0;
    char c = '\0';
    std::string CurrentID;
    std::ifstream quelle;
    quelle.open(FileName, std::ios::in);

    if (!quelle) { // Fehlerabfrage
        std::cerr    << "Datei kann nicht geoeffnet werden!\n";
        exit(-1);
    }
    int Zeile = 0;
    char Error = 'e';
    short PreisError = 0;
    bool MultipleErrors = true;

    while (MultipleErrors == true){
    try {
            Zeile = 0;      // Reset Zeile, for multiple mistakes
            MultipleErrors = false;     //If no Error catched, the loop will be left
        while (quelle.eof() != true){ // Loopt durch File
            int CounterAttribute;
            int CounterFlugHafenKrz = 0;


            quelle.get(c);

            if (c == 'F'){      // Falls Typ "Flug"
                CounterAttribute = 0;
                while (quelle.eof() != true){       //Falls nicht Ende der Datei
                    if (c == '\n')              // Falls letztes Char, weiter mit Hauptloop
                        break;
                    else if (c != '\n'){        // Ansonsten suche anzahl von "|" um die Attribute zu zählen
                        quelle.get(c);
                        if (c == '|'){
                            CounterAttribute++;
                        }
                        if (CounterAttribute == 2){ // Check ob Zahlen nach dem zweiten "|"
                            if (c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9' && c != '.' && c != '|')
                                throw (PreisError);
                        }
                        if (CounterAttribute == 5 or CounterAttribute == 6){       //Counter für Zeichenanzahl für Flughafenabkürzung 3+3+2x"|"
                            CounterFlugHafenKrz++;
                        }
                        if (CounterFlugHafenKrz > 8)
                            throw (Error);
                }

                }
                if (CounterAttribute != 7){     // Falls falsche Anzahl an Attributen, error
                    throw Zeile;
                }
                Zeile++;
            }

            if (c == 'R'){      // gleiches für Car
                CounterAttribute = 0;
                while (c != '\n'){
                    quelle.get(c);
                    if (c == '|')
                        CounterAttribute++;
                    if (CounterAttribute == 2){
                        if (c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9' && c != '.' && c != '|')
                            throw (PreisError);
                    }
                }
                if (CounterAttribute != 7){
                    throw Zeile;
                }
                Zeile++;
            }
            if (c == 'H'){      // gleiches für Hotels
                CounterAttribute = 0;
                while (c != '\n'){
                    quelle.get(c);
                    if (c == '|')
                        CounterAttribute++;
                    if (CounterAttribute == 2){
                        if (c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9' && c != '.' && c != '|')
                            throw (PreisError);
                    }
                }
                if (CounterAttribute != 6){
                    throw Zeile;
                }
                Zeile++;
            }
        }
    } catch (int AttributenError) {
        quelle.close();
        MultipleErrors = true;

        std::ostringstream streamObj;
        streamObj<<std::fixed;
        streamObj<<std::setprecision(0);
        streamObj<<Zeile+1;
        std::string ZeileStr = streamObj.str();

        std::string FehlerImPopUp = "In der Zeile " + ZeileStr + " gibt es unagemessene Anzahl der Attributen.";
        std::string FehlerImPopUpDetailiert = "Wenn Sie die Datei bereits korrigiert haben, wählen Sie 'Wiederholen'. 'Continue' wird versuchen das Programm trotzdem ausführen.";

        QMessageBox msgBox(QMessageBox::Warning, QObject::tr("QMessageBox::warning()"),
                           QObject::tr(FehlerImPopUp.c_str()), { }, NULL);
        msgBox.setDetailedText(QString::fromStdString(FehlerImPopUpDetailiert));
        msgBox.addButton(QObject::tr("Wiederholen"), QMessageBox::AcceptRole);
        msgBox.addButton(QObject::tr("&Continue"), QMessageBox::RejectRole);
        if(msgBox.exec() == QMessageBox::AcceptRole){
            quelle.open(FileName, std::ios::in);
        }
        else
            break;

    }
    catch (short PreisError){
        quelle.close();
        MultipleErrors = true;

        std::ostringstream streamObj;
        streamObj<<std::fixed;
        streamObj<<std::setprecision(0);
        streamObj<<Zeile+1;
        std::string ZeileStr = streamObj.str();

        std::string FehlerImPopUp = "In der Zeile " + ZeileStr + " gibt es falsche Eingabe fuer den Preis.";
        std::string FehlerImPopUpDetailiert = "Wenn Sie die Datei bereits korrigiert haben, wählen Sie 'Wiederholen'. 'Continue' wird versuchen das Programm trotzdem ausführen.";

        QMessageBox msgBox(QMessageBox::Warning, QObject::tr("QMessageBox::warning()"),
                           QObject::tr(FehlerImPopUp.c_str()), { }, NULL);
        msgBox.setDetailedText(QString::fromStdString(FehlerImPopUpDetailiert));
        msgBox.addButton(QObject::tr("Wiederholen"), QMessageBox::AcceptRole);
        msgBox.addButton(QObject::tr("&Continue"), QMessageBox::RejectRole);
        if(msgBox.exec() == QMessageBox::AcceptRole){
            quelle.open(FileName, std::ios::in);
        }
        else
            break;
    }
    catch (char FlughafenKuerzelError){
        quelle.close();
        MultipleErrors = true;

        std::ostringstream streamObj;
        streamObj<<std::fixed;
        streamObj<<std::setprecision(0);
        streamObj<<Zeile+1;
        std::string ZeileStr = streamObj.str();

        std::string FehlerImPopUp = "In der Zeile " + ZeileStr + " gibt es falsche Eingabe fuer die Flughafenkürzel.";
        std::string FehlerImPopUpDetailiert = "Wenn Sie die Datei bereits korrigiert haben, wählen Sie 'Wiederholen'. 'Continue' wird versuchen das Programm trotzdem ausführen.";

        QMessageBox msgBox(QMessageBox::Warning, QObject::tr("QMessageBox::warning()"),
                           QObject::tr(FehlerImPopUp.c_str()), { }, NULL);
        msgBox.setDetailedText(QString::fromStdString(FehlerImPopUpDetailiert));
        msgBox.addButton(QObject::tr("Wiederholen"), QMessageBox::AcceptRole);
        msgBox.addButton(QObject::tr("&Continue"), QMessageBox::RejectRole);
        if(msgBox.exec() == QMessageBox::AcceptRole){
            quelle.open(FileName, std::ios::in);
        }
        else
            break;

    }
    }

    quelle.close();
    quelle.open(FileName, std::ios::in);      //Alternativ "go to 0 char"

    while (quelle.eof() != true){
        quelle.get(c);

        if (c == 'F'){ // new FlightBooking

            FlightBooking *p = new FlightBooking;   // new Flightbooking in heap
            quelle.get(c); // is a |

            Search (quelle, c, CurrentID);  // call for Function to search through next sequences of chars
            p->setId(stoi (CurrentID));     // Those chars are set as an attribute for our new object
            CurrentID.clear();

            Search (quelle, c, CurrentID);      // Repeat for all next attributes
            p->setPrice(stof (CurrentID));
            CurrentID.clear();

            Search (quelle, c, CurrentID);
            p->setFromDate(CurrentID);
            CurrentID.clear();

            Search (quelle, c, CurrentID);
            p->setToDate(CurrentID);
            CurrentID.clear();

            Search (quelle, c, CurrentID);
            p->setFromDestination(CurrentID);
            CurrentID.clear();

            Search (quelle, c, CurrentID);
            p->setToDestination(CurrentID);
            CurrentID.clear();

            quelle.get(c); // next after |
            while (quelle.eof() != true){
                if (c != '\n'){
                CurrentID.push_back(c);
                quelle.get(c);
                }
                else
                    break;
            }
            p->setAirline(CurrentID);
            CurrentID.clear();

            p->showDetails(p); // zeigt die Infos über den Flug

            (BookingList).push_back(p);
            (FlightsList).push_back(p);
            FlightNum++;
            FlightCost += p->getPrice();    // Save total price for flights

        }

        if (c == 'R'){ // same for rental cars
            RentalCarReservation *p = new RentalCarReservation;
            quelle.get(c); // is a |

            Search (quelle, c, CurrentID);
            p->setId(stoi (CurrentID));
            CurrentID.clear();

            Search (quelle, c, CurrentID);
            p->setPrice(stof (CurrentID));
            CurrentID.clear();

            Search (quelle, c, CurrentID);
            p->setFromDate(CurrentID);
            CurrentID.clear();

            Search (quelle, c, CurrentID);
            p->setToDate(CurrentID);
            CurrentID.clear();

            Search (quelle, c, CurrentID);
            p->setPickupLocation(CurrentID);
            CurrentID.clear();

            Search (quelle, c, CurrentID);
            p->setReturnLocation(CurrentID);
            CurrentID.clear();

            quelle.get(c); // next after |
            while (quelle.eof() != true){
                if (c != '\n'){
                CurrentID.push_back(c);
                quelle.get(c);
                }
                else
                    break;
            }
            p->setCompany(CurrentID);
            CurrentID.clear();

            p->showDetails(p); // zeigt die Infos über den Mietwagen


            (BookingList).push_back(p);
            (RentalCarList).push_back(p);
            CarNum++;
            CarCost += p->getPrice();
        }

        if (c == 'H'){ // same for new Hotels
            HotelBooking *p = new HotelBooking;
            quelle.get(c); // is a |

            Search (quelle, c, CurrentID);
            p->setId(stoi (CurrentID));
            CurrentID.clear();

            Search (quelle, c, CurrentID);
            p->setPrice(stof (CurrentID));
            CurrentID.clear();

            Search (quelle, c, CurrentID);
            p->setFromDate(CurrentID);
            CurrentID.clear();

            Search (quelle, c, CurrentID);
            p->setToDate(CurrentID);
            CurrentID.clear();

            Search (quelle, c, CurrentID);
            p->setHotel(CurrentID);
            CurrentID.clear();

            quelle.get(c); // next after |
            while (quelle.eof() != true){
                if (c != '\n'){
                CurrentID.push_back(c);
                quelle.get(c);
                }
                else
                    break;
            }
            p->setTown(CurrentID);
            CurrentID.clear();

            p->showDetails(p); // zeigt die Infos über das Hotel

            (BookingList).push_back(p);
            (HotelList).push_back(p);
                HotelNum++;
                HotelCost += p->getPrice();
        }


    }

    quelle.close();

    std::cout << std::endl << std::endl << std::endl;
    std::cout << "Es wurden " << FlightNum << " Fluege gebucht zum Preis von " << FlightCost << std::endl;
    std::cout << "Es wurden " << CarNum << " Autos gemietet zum Preis von " << CarCost << std::endl;
    std::cout << "Es wurden " << HotelNum << " Hotels gebucht zum Preis von " << HotelCost << std::endl;

    /*for (Booking* obj : BookingList)        // delete objects in heap
        delete obj;
    BookingList.clear();*/
}

void TravelAgency::readBinaryFile()
{

    std::string inputFileName = "bookingsBinary.bin";
    std::ifstream inputFileStream;

    inputFileStream.open(inputFileName.c_str(),std::ifstream::binary | std::ifstream::in);
    if (!inputFileStream) {
        std::cerr << inputFileName << " kann nicht geoeffnet werden!\n";
        exit(-1);
    }

    long IdBin;
    double PreisBin;
    char AirPortBin[3];
    char LongNamesBin[15];
    char TypeReservationBin;
    char DatumBin[8];

    do{
        inputFileStream.read(reinterpret_cast<char*>(&TypeReservationBin),sizeof (TypeReservationBin));

        if (TypeReservationBin == 'F'){ // if first char is F, go through attributes of F in bin format
            FlightBooking *p = new FlightBooking;
            inputFileStream.read(reinterpret_cast<char*>(&IdBin),sizeof (IdBin));
            p->setId(IdBin);

            inputFileStream.read(reinterpret_cast<char*>(&PreisBin),sizeof (PreisBin));
            p->setPrice(PreisBin);

            inputFileStream.read(reinterpret_cast<char*>(&DatumBin),sizeof (DatumBin));
            std::string tmp;
            for (int i = 0; i < 8; i++)
                tmp.push_back(DatumBin[i]);
            p->setFromDate(tmp);
            tmp.clear();

            inputFileStream.read(reinterpret_cast<char*>(&DatumBin),sizeof (DatumBin));
            for (int i = 0; i < 8; i++)
                tmp.push_back(DatumBin[i]);
            p->setToDate(tmp);
            tmp.clear();

            inputFileStream.read(reinterpret_cast<char*>(&AirPortBin),sizeof (AirPortBin));
            for (int i = 0; i < 3; i++)
                tmp.push_back(AirPortBin[i]);
            p->setFromDestination(tmp);
            tmp.clear();

            inputFileStream.read(reinterpret_cast<char*>(&AirPortBin),sizeof (AirPortBin));
            for (int i = 0; i < 3; i++)
                tmp.push_back(AirPortBin[i]);
            p->setToDestination(tmp);
            tmp.clear();

            inputFileStream.read(reinterpret_cast<char*>(&LongNamesBin),sizeof (LongNamesBin));
            for (int i = 0; i < 15; i++)
                if (LongNamesBin[i] != ' ')
                tmp.push_back(LongNamesBin[i]);
            p->setAirline(tmp);
            tmp.clear();

            p->showDetails(p); // zeigt die Infos über den Flug

            (BookingList).push_back(p);
            (FlightsList).push_back(p);
        }

        if (TypeReservationBin == 'R'){ // same for cars
            RentalCarReservation *p = new RentalCarReservation;

            inputFileStream.read(reinterpret_cast<char*>(&IdBin),sizeof IdBin);
            p->setId(IdBin);

            inputFileStream.read(reinterpret_cast<char*>(&PreisBin),sizeof PreisBin);
            p->setPrice(PreisBin);

            inputFileStream.read(reinterpret_cast<char*>(&DatumBin),sizeof DatumBin);
            std::string tmp;
            for (int i = 0; i < 8; i++)
                tmp.push_back(DatumBin[i]);
            p->setFromDate(tmp);
            tmp.clear();

            inputFileStream.read(reinterpret_cast<char*>(&DatumBin),sizeof DatumBin);
            for (int i = 0; i < 8; i++)
                tmp.push_back(DatumBin[i]);
            p->setToDate(tmp);
            tmp.clear();

            inputFileStream.read(reinterpret_cast<char*>(&LongNamesBin),sizeof LongNamesBin);
            for (int i = 0; i < 15; i++)
                if (LongNamesBin[i] != ' ')
                tmp.push_back(LongNamesBin[i]);
            p->setPickupLocation(tmp);
            tmp.clear();

            inputFileStream.read(reinterpret_cast<char*>(&LongNamesBin),sizeof LongNamesBin);
            for (int i = 0; i < 15; i++)
                if (LongNamesBin[i] != ' ')
                tmp.push_back(LongNamesBin[i]);
            p->setReturnLocation(tmp);
            tmp.clear();

            inputFileStream.read(reinterpret_cast<char*>(&LongNamesBin),sizeof LongNamesBin);
            for (int i = 0; i < 15; i++)
                if (LongNamesBin[i] != ' ')
                tmp.push_back(LongNamesBin[i]);
            p->setCompany(tmp);
            tmp.clear();

            p->showDetails(p); // zeigt die Infos über den Mietwagen

            (BookingList).push_back(p);
            (RentalCarList).push_back(p);
        }

        if (TypeReservationBin == 'H'){ // same for Hotels
            HotelBooking *p = new HotelBooking;

            inputFileStream.read(reinterpret_cast<char*>(&IdBin),sizeof IdBin);
            p->setId(IdBin);

            inputFileStream.read(reinterpret_cast<char*>(&PreisBin),sizeof PreisBin);
            p->setPrice(PreisBin);

            inputFileStream.read(reinterpret_cast<char*>(&DatumBin),sizeof DatumBin);
            std::string tmp;
            for (int i = 0; i < 8; i++)
                tmp.push_back(DatumBin[i]);
            p->setFromDate(tmp);
            tmp.clear();

            inputFileStream.read(reinterpret_cast<char*>(&DatumBin),sizeof DatumBin);
            for (int i = 0; i < 8; i++)
                tmp.push_back(DatumBin[i]);
            p->setToDate(tmp);
            tmp.clear();

            inputFileStream.read(reinterpret_cast<char*>(&LongNamesBin),sizeof LongNamesBin);
            for (int i = 0; i < 15; i++)
                if (LongNamesBin[i] != ' ')
                tmp.push_back(LongNamesBin[i]);
            p->setHotel(tmp);
            tmp.clear();

            inputFileStream.read(reinterpret_cast<char*>(&LongNamesBin),sizeof LongNamesBin);
            for (int i = 0; i < 15; i++)
                if (LongNamesBin[i] != ' ')
                tmp.push_back(LongNamesBin[i]);
            p->setTown(tmp);
            tmp.clear();

            p->showDetails(p); // zeigt die Infos über das Hotel

            (BookingList).push_back(p);
            (HotelList).push_back(p);
        }
    }while (inputFileStream.eof() != true);

    inputFileStream.close();

    std::cout << std::endl << std::endl << "File was closed. And now to the most expensive bookings:" << std::endl << std::endl;

    float Compare = 0;
    int VectorPosition = 0;

    for (int i = 0; i < (int)FlightsList.size(); i++){ // Go through the vector, to find out the most expensive trip
        if (Compare < FlightsList[i]->getPrice()){
            Compare = FlightsList[i]->getPrice();
            VectorPosition = i;
        }
    }
    FlightsList[VectorPosition]->showDetails(FlightsList[VectorPosition]);

    Compare = 0;
    VectorPosition = 0;

    for (int i = 0; i < (int)RentalCarList.size(); i++){    // same for cars
        if (Compare < RentalCarList[i]->getPrice()){
            Compare = RentalCarList[i]->getPrice();
            VectorPosition = i;
        }
    }
    RentalCarList[VectorPosition]->showDetails(RentalCarList[VectorPosition]);

    Compare = 0;
    VectorPosition = 0;

    for (int i = 0; i < (int)HotelList.size(); i++){        // same for Hotels
        if (Compare < HotelList[i]->getPrice()){
            Compare = HotelList[i]->getPrice();
            VectorPosition = i;
        }
    }
    HotelList[VectorPosition]->showDetails(HotelList[VectorPosition]);

    for (Booking* obj : BookingList)        // clean our heap
        delete obj;
    BookingList.clear();

    for (FlightBooking* obj : FlightsList)
        delete obj;
    FlightsList.clear();

    for (HotelBooking* obj : HotelList)
        delete obj;
    HotelList.clear();

    for (RentalCarReservation* obj : RentalCarList)
        delete obj;
    RentalCarList.clear();
}

TravelAgency::~TravelAgency()
{

}

void Search(std::ifstream &x, char y, std::string &z){
    x.get(y); // next after |
    while (y != '|'){
        z.push_back(y);
        x.get(y);
    }
}

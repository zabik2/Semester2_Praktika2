#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QDate>
#include <QDateEdit>
#include <QListWidgetItem>
#include "json.hpp"
#include <iostream>
#include <fstream>

using namespace nlohmann;

TravelAgency TravelAgency1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionEinlesen_triggered()
{
    for (FlightBooking* obj : TravelAgency1.FlightsList)
        delete obj;
    TravelAgency1.FlightsList.clear();

    for (HotelBooking* obj : TravelAgency1.HotelList)
        delete obj;
    TravelAgency1.HotelList.clear();

    for (RentalCarReservation* obj : TravelAgency1.RentalCarList)
        delete obj;
    TravelAgency1.RentalCarList.clear(); // clean heap, for multiple file loads

    QString fileName = QFileDialog::getOpenFileName(this, "Select a file to open...", QDir::currentPath()); // Öffne File in der lokalen Verzeichniss

    TravelAgency1.readFile(fileName.toStdString());

    float FlightNum = 0, FlightCost = 0, CarNum = 0, CarCost = 0, HotelNum = 0, HotelCost = 0;

    for (int i = 0; i < (int)TravelAgency1.FlightsList.size(); i++){        // Gets total cost
            FlightCost += TravelAgency1.FlightsList[i]->getPrice();
            FlightNum++;
        }
    for (int i = 0; i < (int)TravelAgency1.RentalCarList.size(); i++){
            CarCost += TravelAgency1.RentalCarList[i]->getPrice();
            CarNum++;
        }
    for (int i = 0; i < (int)TravelAgency1.HotelList.size(); i++){
            HotelCost += TravelAgency1.HotelList[i]->getPrice();
            HotelNum++;
        }

    std::ostringstream streamObjFK; // Convert double to string with precission (required to avoid extra digits)
    streamObjFK<<std::fixed;
    streamObjFK<<std::setprecision(2);
    streamObjFK<<FlightCost;
    std::string FlightKostenStr = streamObjFK.str();

    std::ostringstream streamObjFA;
    streamObjFA<<std::fixed;
    streamObjFA<<std::setprecision(0);
    streamObjFA<<FlightNum;
    std::string FlightNumStr = streamObjFA.str();

    std::ostringstream streamObjCK;
    streamObjCK<<std::fixed;
    streamObjCK<<std::setprecision(2);
    streamObjCK<<CarCost;
    std::string CarKostemStr = streamObjCK.str();

    std::ostringstream streamObjCA;
    streamObjCA<<std::fixed;
    streamObjCA<<std::setprecision(0);
    streamObjCA<<CarNum;
    std::string CarNumStr = streamObjCA.str();

    std::ostringstream streamObjHK;
    streamObjHK<<std::fixed;
    streamObjHK<<std::setprecision(1);
    streamObjHK<<HotelCost;
    std::string HotelKostenStr = streamObjHK.str();

    std::ostringstream streamObjHA;
    streamObjHA<<std::fixed;
    streamObjHA<<std::setprecision(0);
    streamObjHA<<HotelNum;
    std::string HotelNumStr = streamObjHA.str();

    std::string BuchungenImPopUp = "Es wurden " + FlightNumStr + " Fluege gebucht. Diese kosten " + FlightKostenStr +
            ". Es wurden " + CarNumStr + " Autos gemietet. Diese kosten " + CarKostemStr +
            ". Es wurden " + HotelNumStr + " Hotels gebucht. Diese Kosten " + HotelKostenStr + ".";


    QMessageBox::information(this, QObject::tr("QMessageBox::information()"), QObject::tr(BuchungenImPopUp.c_str()));       // Pop up für alle Buchungen


    for (int i = 0; i < (int)TravelAgency1.BookingList.size(); i++){
        for (int j = 0; j < (int)TravelAgency1.FlightsList.size(); j++){
        if (TravelAgency1.BookingList[i]->getId() == TravelAgency1.FlightsList[j]->getId()){
            int FoundFlightsID =TravelAgency1.FlightsList[j]->getId();
            int FoundFlightsPrice = TravelAgency1.FlightsList[j]->getPrice();

            std::ostringstream PreciseID;
            PreciseID<<std::setprecision(0);
            PreciseID<<FoundFlightsID;
            std::string FoundFlightsIDStr = PreciseID.str();

            std::ostringstream PrecisePreis;
            PrecisePreis<<std::fixed;
            PrecisePreis<<std::setprecision(2);
            PrecisePreis<<FoundFlightsPrice;
            std::string FoundFlightsPriceStr = PrecisePreis.str();

            std::string AusgabeList = "Flugbuchung " + FoundFlightsIDStr + " von " + TravelAgency1.FlightsList[j]->getFromDestination() +
                    " nach " + TravelAgency1.FlightsList[j]->getToDestination() + " mit " + TravelAgency1.FlightsList[j]->getAirline() +
                    " am " + TravelAgency1.FlightsList[j]->getFromDate() + ". Preis: " + FoundFlightsPriceStr + " Euro ";

            QString QstringListAusgabe = QString::fromStdString(AusgabeList);
            ui->listWidget->addItem(QstringListAusgabe);                        // adds items to our list widget
                   }
        }
        for (int j = 0; j < (int)TravelAgency1.RentalCarList.size(); j++){

        if (TravelAgency1.BookingList[i]->getId() == TravelAgency1.RentalCarList[j]->getId()){
            int FoundFlightsID =TravelAgency1.RentalCarList[j]->getId();
            int FoundFlightsPrice = TravelAgency1.RentalCarList[j]->getPrice();

            std::ostringstream PreciseID;
            PreciseID<<std::setprecision(0);
            PreciseID<<FoundFlightsID;
            std::string FoundFlightsIDStr = PreciseID.str();

            std::ostringstream PrecisePreis;
            PrecisePreis<<std::fixed;
            PrecisePreis<<std::setprecision(2);
            PrecisePreis<<FoundFlightsPrice;
            std::string FoundFlightsPriceStr = PrecisePreis.str();

            std::string AusgabeList = "Mietwagenreservierung " + FoundFlightsIDStr + " von " + TravelAgency1.RentalCarList[j]->getPickupLocation() +
                    " nach " + TravelAgency1.RentalCarList[j]->getReturnLocation() + " mit " + TravelAgency1.RentalCarList[j]->getCompany() +
                    " Abholung am " + TravelAgency1.RentalCarList[j]->getFromDate() + "Rückgabe am " + TravelAgency1.RentalCarList[j]->getToDate() + ". Preis: "
                    + FoundFlightsPriceStr + " Euro ";

            QString QstringListAusgabe = QString::fromStdString(AusgabeList);
            ui->listWidget->addItem(QstringListAusgabe);
                   }
        }

        for (int j = 0; j < (int)TravelAgency1.HotelList.size(); j++){
        if (TravelAgency1.BookingList[i]->getId() == TravelAgency1.HotelList[j]->getId()){
            int FoundFlightsID =TravelAgency1.HotelList[j]->getId();
            int FoundFlightsPrice = TravelAgency1.HotelList[j]->getPrice();

            std::ostringstream PreciseID;
            PreciseID<<std::setprecision(0);
            PreciseID<<FoundFlightsID;
            std::string FoundFlightsIDStr = PreciseID.str();

            std::ostringstream PrecisePreis;
            PrecisePreis<<std::fixed;
            PrecisePreis<<std::setprecision(2);
            PrecisePreis<<FoundFlightsPrice;
            std::string FoundFlightsPriceStr = PrecisePreis.str();

            std::string AusgabeList = "Hotelreservierung " + FoundFlightsIDStr + " im " + TravelAgency1.HotelList[j]->getHotel() +
                    " in " + TravelAgency1.HotelList[j]->getTown() + " vom " + TravelAgency1.HotelList[j]->getFromDate() +
                    " bis zum " + TravelAgency1.HotelList[j]->getToDate() + ". Preis: " + FoundFlightsPriceStr + " Euro ";


            QString QstringListAusgabe = QString::fromStdString(AusgabeList);
            ui->listWidget->addItem(QstringListAusgabe);
                   }
        }


    }

}


void MainWindow::on_actionAusw_hlen_triggered()
{
    //QString fileName = QFileDialog::getOpenFileName(this, "Select a file to open...", QDir::currentPath()); // Öffne File in der lokalen Verzeichniss

//    TravelAgency1.readFile(fileName.toStdString());

    QDate QDateInstance;    //QDAte.tostring funktioniert nur mit einer Instanz :(

    bool ok, Found = false;
    int SearchedBooking = QInputDialog::getInt(this, tr("QInputDialog::getInt()"),      // default value, min, max, increment
                                 tr("Percentage:"), 25, 0, 100, 1, &ok);

    if(ok){
        for (int i = 0; i < (int)TravelAgency1.FlightsList.size(); i++){
            if (SearchedBooking == TravelAgency1.FlightsList[i]->getId()){
                ui->ID_Output->setText(QString::number(TravelAgency1.FlightsList[i]->getId()));
                QDateInstance = QDateInstance.fromString(QString::fromStdString(TravelAgency1.FlightsList[i]->getFromDate()),"yyyyMMdd");
                ui->StartD_Output->setText(QDateInstance.toString());
                QDateInstance = QDateInstance.fromString(QString::fromStdString(TravelAgency1.FlightsList[i]->getToDate()), "yyyyMMdd");
                ui->EndD_Output->setText(QDateInstance.toString());
                ui->StartFlugH_Output->setText(QString::fromStdString(TravelAgency1.FlightsList[i]->getFromDestination()));
                ui->ZielflugH_Output->setText(QString::fromStdString(TravelAgency1.FlightsList[i]->getToDestination()));
                ui->Fluggesellschaft_Output->setText(QString::fromStdString(TravelAgency1.FlightsList[i]->getAirline()));
                ui->Preis_Output->setText(QString::number(TravelAgency1.FlightsList[i]->getPrice()));

                ui->tabWidget->setCurrentIndex(0);      // Go to Tabwidget 0
                Found = true;
                break;
            }
        }

            for (int i = 0; i < (int)TravelAgency1.RentalCarList.size(); i++){
                if (SearchedBooking == TravelAgency1.RentalCarList[i]->getId()){
                    ui->ID_Car_Output->setText(QString::number(TravelAgency1.RentalCarList[i]->getId()));
                    QDateInstance = QDateInstance.fromString(QString::fromStdString(TravelAgency1.RentalCarList[i]->getFromDate()),"yyyyMMdd");
                    ui->StartDatum_Car_output->setText(QDateInstance.toString());
                    QDateInstance = QDateInstance.fromString(QString::fromStdString(TravelAgency1.RentalCarList[i]->getToDate()), "yyyyMMdd");
                    ui->EndDatum_Car_Output->setText(QDateInstance.toString());
                    ui->Preis_Car_Output->setText(QString::number(TravelAgency1.RentalCarList[i]->getPrice()));
                    ui->AbholOrt_Car_Output->setText(QString::fromStdString(TravelAgency1.RentalCarList[i]->getPickupLocation()));
                    ui->ZielOrt_Car_Output->setText(QString::fromStdString(TravelAgency1.RentalCarList[i]->getReturnLocation()));
                    ui->Firma_Car_Output->setText(QString::fromStdString(TravelAgency1.RentalCarList[i]->getCompany()));
                    ui->tabWidget->setCurrentIndex(1);      // Go to Tabwidget 1
                    Found = true;
                    break;
                }
        }

            for (int i = 0; i < (int)TravelAgency1.HotelList.size(); i++){
                if (SearchedBooking == TravelAgency1.HotelList[i]->getId()){
                    ui->ID_Hotel_Output->setText(QString::number(TravelAgency1.HotelList[i]->getId()));
                    QDateInstance = QDateInstance.fromString(QString::fromStdString(TravelAgency1.HotelList[i]->getFromDate()),"yyyyMMdd");
                    ui->StartDatum_Hotel_Output->setText(QDateInstance.toString());
                    QDateInstance = QDateInstance.fromString(QString::fromStdString(TravelAgency1.HotelList[i]->getToDate()), "yyyyMMdd");
                    ui->EndDatum_Hotel_Output->setText(QDateInstance.toString());
                    ui->Preis_Hotel_Output->setText(QString::number(TravelAgency1.HotelList[i]->getPrice()));
                    ui->HotelName_Output->setText(QString::fromStdString(TravelAgency1.HotelList[i]->getHotel()));
                    ui->HotelStadt_Output->setText(QString::fromStdString(TravelAgency1.HotelList[i]->getTown()));                    
                    ui->tabWidget->setCurrentIndex(2);
                    Found = true;
                    break;
                }
            }
            if (Found == false){
                QMessageBox::information(this, QObject::tr("QMessageBox::information()"), QObject::tr("Keine Buchung mit so einer ID"));
            }
    }

}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    std::string str = item->text().toStdString();// gets a Qstring

    std::string IDFromClick;
    int IdTotalFound;

    if(str[0] == 'F'){
        IDFromClick.push_back(str[12]);
        IDFromClick.push_back(str[13]);
    }

    if(str[0] == 'M'){
        IDFromClick.push_back(str[22]);
        IDFromClick.push_back(str[23]);
    }

    if(str[0] == 'H'){
        IDFromClick.push_back(str[18]);
        IDFromClick.push_back(str[19]);
    }
    IdTotalFound = stoi(IDFromClick);
    IDFromClick.clear();


    QDate QDateInstance;    //QDAte.tostring funktioniert nur mit einer Instanz :(

    for (int i = 0; i < (int)TravelAgency1.FlightsList.size(); i++){
        if (IdTotalFound == TravelAgency1.FlightsList[i]->getId()){
            ui->ID_Output->setText(QString::number(TravelAgency1.FlightsList[i]->getId()));
            QDateInstance = QDateInstance.fromString(QString::fromStdString(TravelAgency1.FlightsList[i]->getFromDate()),"yyyyMMdd");
            ui->StartD_Output->setText(QDateInstance.toString());
            QDateInstance = QDateInstance.fromString(QString::fromStdString(TravelAgency1.FlightsList[i]->getToDate()), "yyyyMMdd");
            ui->EndD_Output->setText(QDateInstance.toString());
            ui->StartFlugH_Output->setText(QString::fromStdString(TravelAgency1.FlightsList[i]->getFromDestination()));
            ui->ZielflugH_Output->setText(QString::fromStdString(TravelAgency1.FlightsList[i]->getToDestination()));
            ui->Fluggesellschaft_Output->setText(QString::fromStdString(TravelAgency1.FlightsList[i]->getAirline()));
            ui->Preis_Output->setText(QString::number(TravelAgency1.FlightsList[i]->getPrice()));
            ui->tabWidget->setCurrentIndex(0);
            break;
        }
    }

        for (int i = 0; i < (int)TravelAgency1.RentalCarList.size(); i++){
            if (IdTotalFound == TravelAgency1.RentalCarList[i]->getId()){
                ui->ID_Car_Output->setText(QString::number(TravelAgency1.RentalCarList[i]->getId()));
                QDateInstance = QDateInstance.fromString(QString::fromStdString(TravelAgency1.RentalCarList[i]->getFromDate()),"yyyyMMdd");
                ui->StartDatum_Car_output->setText(QDateInstance.toString());
                QDateInstance = QDateInstance.fromString(QString::fromStdString(TravelAgency1.RentalCarList[i]->getToDate()), "yyyyMMdd");
                ui->EndDatum_Car_Output->setText(QDateInstance.toString());
                ui->Preis_Car_Output->setText(QString::number(TravelAgency1.RentalCarList[i]->getPrice()));
                ui->AbholOrt_Car_Output->setText(QString::fromStdString(TravelAgency1.RentalCarList[i]->getPickupLocation()));
                ui->ZielOrt_Car_Output->setText(QString::fromStdString(TravelAgency1.RentalCarList[i]->getReturnLocation()));
                ui->Firma_Car_Output->setText(QString::fromStdString(TravelAgency1.RentalCarList[i]->getCompany()));
                ui->tabWidget->setCurrentIndex(1);
                break;
            }
    }

        for (int i = 0; i < (int)TravelAgency1.HotelList.size(); i++){
            if (IdTotalFound == TravelAgency1.HotelList[i]->getId()){
                ui->ID_Hotel_Output->setText(QString::number(TravelAgency1.HotelList[i]->getId()));
                QDateInstance = QDateInstance.fromString(QString::fromStdString(TravelAgency1.HotelList[i]->getFromDate()),"yyyyMMdd");
                ui->StartDatum_Hotel_Output->setText(QDateInstance.toString());
                QDateInstance = QDateInstance.fromString(QString::fromStdString(TravelAgency1.HotelList[i]->getToDate()), "yyyyMMdd");
                ui->EndDatum_Hotel_Output->setText(QDateInstance.toString());
                ui->Preis_Hotel_Output->setText(QString::number(TravelAgency1.HotelList[i]->getPrice()));
                ui->HotelName_Output->setText(QString::fromStdString(TravelAgency1.HotelList[i]->getHotel()));
                ui->HotelStadt_Output->setText(QString::fromStdString(TravelAgency1.HotelList[i]->getTown()));
                ui->tabWidget->setCurrentIndex(2);
                break;
            }
        }
}


void MainWindow::on_actionJson_triggered()
{
//QString fileName = QFileDialog::getSaveFileName(this, "Select a file to open...", QDir::currentPath()); // Öffne File in der lokalen Verzeichniss

QFileDialog dialog(this, "Save someting", QString(),
                   "json File (*.json)");
dialog.setDefaultSuffix(".json");
dialog.setAcceptMode(QFileDialog::AcceptSave);
if (dialog.exec()) {
    const auto fn = dialog.selectedFiles().front();      // a QStringList is returned but it always contains a single file

    json Flugbuchungen;
    json FlugArray;

    json CarBuchungen;
    json CarArray;

    json HotelsBuchungen;
    json HotelsArray;

    json gesamteDatei;




    for (auto Flights:TravelAgency1.FlightsList){
        json FlightsJson;       // Lowest Json level
            FlightsJson["airline"] = Flights->getAirline();
            FlightsJson["fromDate"] = Flights->getFromDate();
            FlightsJson["fromDest"] = Flights->getFromDestination();
            FlightsJson["id"] = Flights->getId();
            FlightsJson["price"] = Flights->getPrice();
            FlightsJson["toDate"] = Flights->getToDate();
            FlightsJson["toDest"] = Flights->getToDestination();
            FlugArray.push_back(FlightsJson);   // pushback to create new level
            Flugbuchungen["Fluege"] = FlugArray;    // higher Json level
    }
    gesamteDatei.push_back(Flugbuchungen);  // get all the data into file

    for (auto Cars:TravelAgency1.RentalCarList){
         json CarsJson;
            CarsJson["Company"] = Cars->getCompany();
            CarsJson["fromDate"] = Cars->getFromDate();
            CarsJson["id"] = Cars->getId();
            CarsJson["fromDest"] = Cars->getPickupLocation();
            CarsJson["price"] = Cars->getPrice();
            CarsJson["toDest"] = Cars->getReturnLocation();
            CarsJson["toDate"] = Cars->getToDate();
            CarArray.push_back(CarsJson);
            CarBuchungen["Mietwagenreservierungen"] = CarArray;
    }
    gesamteDatei.push_back(CarBuchungen);

    for (auto Hotels:TravelAgency1.HotelList){
         json HotelsJson;
            HotelsJson["fromDate"] = Hotels->getFromDate();
            HotelsJson["fromDest"] = Hotels->getHotel();
            HotelsJson["id"] = Hotels->getId();
            HotelsJson["toDate"] = Hotels->getToDate();
            HotelsJson["price"] = Hotels->getPrice();
            HotelsJson["toDate"] = Hotels->getTown();
            HotelsArray.push_back(HotelsJson);
            HotelsBuchungen["Hotelreservierungen"] = HotelsArray;
    }
    gesamteDatei.push_back(HotelsBuchungen);

    std::ofstream outputStream(fn.toStdString());
    if (!outputStream) std::cerr << "JSON Datei konnte nicht geoeffnet werden";
    outputStream << gesamteDatei.dump(4);       // dump is for distance between levels
    outputStream.close();

}
}


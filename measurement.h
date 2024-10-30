#ifndef __MEASUREMENT_H__
#define __MEASUREMENT_H__

#include <TObject.h>

class Measurement : public TObject {

    public:
    Measurement(); // default constructor
    Measurement(Int_t y, Int_t m, Int_t d, Int_t h, Int_t min, Int_t sec, Double_t temp, Char_t airQ); 
    virtual ~Measurement(); // destructor

    // Getter methods to access private members
    Int_t Gety() const { return y; }
    Int_t Getm() const { return m; }
    Int_t Getd() const { return d; }

    Int_t Geth() const { return h; }
    Int_t Getmin() const { return min; }
    Int_t Getsec() const { return sec; }

    Double_t Gettemp() const { return temp; }
    Char_t GetairQ() const { return airQ; }

    // Setter methods to modify private members
    void SetYear(Int_t y) { this->y = y; }
    void SetMonth(Int_t m) { this->m = m; }
    void SetDay(Int_t d) { this->d = d; }

    void SetHour(Int_t h) { this->h = h; }
    void SetMinute(Int_t min) { this->min = min; }
    void SetSecond(Int_t sec) { this->sec = sec; }

    void SetTemperature(Double_t temp) { this->temp = temp; }
    void SetAirQuality(Char_t airQ) { this->airQ = airQ; }
    
    private:
    Int_t y;
    Int_t m;
    Int_t d;

    Int_t h;
    Int_t min;
    Int_t sec;

    Double_t temp;
    Char_t airQ;


    ClassDef(Measurement, 1); // measurement
};

#endif // This is for MEASUREMENT_H
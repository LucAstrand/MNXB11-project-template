#include "../include/measurement.h"

// default constructor - ROOT needs the default one where everything is set to 0
Measurement::Measurement() :
y{0}, 
m{0}, 
d{0}, 
h{0}, 
min{0}, 
sec{0},
temp{0}, 
airQ{0}
{

}
// another constructor
Measurement::Measurement(Int_t y, Int_t m, Int_t d, Int_t h, Int_t min, Int_t sec, Double_t temp, Char_t airQ) :  
y{y}, 
m{m}, 
d{d}, 
h{h}, 
min{min}, 
sec{sec},
temp{temp}, 
airQ{airQ}
{

}
// destructor
Measurement::~Measurement(){
// right now I'm empty

}


ClassImp(Measurement)
#include <iostream>
#include <TCanvas.h>
#include <TH1F.h>

int main() {
    TCanvas *c = new TCanvas("c", "Canvas", 800, 600);
    TH1F *h = new TH1F("h", "Test Histogram", 100, -4, 4);
    h->FillRandom("gaus", 10000);
    h->Draw();
    c->SaveAs("histogram.png");
    std::cout << "Histogram saved as histogram.png" << std::endl;
    return 0;
}
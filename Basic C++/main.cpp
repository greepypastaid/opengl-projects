#include "Burung.hpp"
#include "Merak.hpp"
int main() {
    Burung* twety = new Burung();
    twety->setKaki(1);
    cout << twety->GetKaki() <<"\n";
    twety->CekHidup();
    delete twety;
    
    Merak* iwan = new Merak();
    iwan->warna = "warna warni";
    iwan->setKaki(3);
    cout<< iwan->warna <<"\n";
    cout << iwan->GetKaki() <<"\n";
    iwan->CekHidup();
    
    delete iwan;
    
    return 0;
}



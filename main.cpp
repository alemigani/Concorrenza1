#include <iostream>
#include <chrono>
#include <thread>
#include <sys/sysinfo.h>

using namespace std;

void estrai (int quanti, string chiamante){
    auto inizio = chrono::high_resolution_clock::now();
    for (int i = 0; i<quanti; i++){
        rand();
    }
    auto fine = chrono::high_resolution_clock::now();
    auto duratataMillisec = chrono::duration_cast <chrono::milliseconds>(fine - inizio).count();
    cout << "Tempo impiegato " << chiamante << ": " << duratataMillisec << endl;
}

int main(){

    const int QUANTI = 4000000;

    thread t1{estrai, QUANTI, "thread"};
    thread t2{estrai, QUANTI*100, "thread1"};
    t2.detach(); // non mette in pausa main finchè t2 non ha finito
    
    estrai(QUANTI, "funzione main");
    t1.join(); // mette in pausa main finché t1 non ha finito

    struct sysinfo info;
    if(sysinfo(&info) == 0){
        cout << "Totale Memoria RAM: " << info.totalram << endl;
        cout << "Memoria RAM Libera: " << info.freeram << endl;
    }

    return 0;
}
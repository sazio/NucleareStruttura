//
//  Conteggi_Corrente30kV.cpp
//  
//
//  Created by Simone Azeglio on 06/03/17.
//
//
//


#include <iostream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include "TVirtualFitter.h"   // ci serve come supporto per i fit
#include <iomanip>            // ci serve per manipolare l'output a video
#include <math.h>

using namespace std;

void Rate_Corrente_Macchina1_30kV(){
    
    
    //numero misure
    const int nmisure = 18 ;
    
    
    // numero misure senza doppi
    const int nmisure2= 9;
    //----- DATI ------
    
    
    
    
    //Salita
    
    float Conteggi[]  = {20693, 21548, 25250, 25134, 30789, 29702 ,  31746, 30820, 32666, 33639 ,  33307, 33007, 31273, 31185, 32454, 32179, 33233, 33038  };
    
    cout << "Misure Conteggi: " << sizeof(Conteggi)/4 << endl;
    
    
    float Corrente[]  = {11.6, 11.6, 12, 12, 12.5, 12.5,  13.6, 13.6,  15.4, 15.4,  16.9, 16.9, 21.5, 21.5, 26.4, 26.4, 30.6, 30.6  };
    
    
    cout << "Misure Corrente:  " << sizeof(Corrente)/4 << endl;
    
    
    // Calcolo effettivi con medie di valori doppi
    
    float Conteggi2[nmisure2] ;
    float sConteggi2[nmisure2];
    float Corrente2[nmisure2] ;
    float sCorrente2[nmisure2] ;
    
    float Secondi2[nmisure2] ;
    float sSecondi2[nmisure2];
    
    float Conteggi_Secondi2[nmisure2];
    float sConteggi_Secondi2[nmisure2];
    
    
    for( int j = 0 , i = 0  ; i < nmisure && j < nmisure2 ; i++, j++)
    { if(Corrente[i] == Corrente[i+1]){
        Corrente2[j]= Corrente[i] ;
        cout << "Corrente" << j <<" : "  <<  Corrente2[j] << endl ;
        Conteggi2[j] = (Conteggi[i]+Conteggi[i+1])/2 ;
        cout << "Conteggi" << j <<" : "  <<  Conteggi2[j] << endl ;
        i = i + 1 ;
    }
    else { Corrente2[j] = Corrente[i];
        Conteggi2[j] = Conteggi[i];
        
        
    }
        
    }
    
    
    for(int i = 0 ; i < nmisure2 ; i++){
        sConteggi2[i] = 1 ;
        Secondi2[i] = 20 ;
        sSecondi2[i] = 0.001;
        sCorrente2[i] = 0;
        
        Conteggi_Secondi2[i] = Conteggi2[i]/Secondi2[i];
        sConteggi_Secondi2[i] = sqrt(((sConteggi2[i]/Secondi2[i])*(sConteggi2[i]/Secondi2[i])) + ((Conteggi2[i]*sSecondi2[i]/Secondi2[i])*(Conteggi2[i]*sSecondi2[i]/Secondi2[i])));
        
    }
    
    
    
    
    
    
    
    
    
    
    //--------------- FIT Dati -------- //
    
    TCanvas *cConteggiCorrente = new TCanvas("cConteggiCorrente ","Conteggi/s(Corrente)",200,10,600,400);
    
    
    TGraphErrors *gConteggiCorrente = new TGraphErrors(nmisure2 , Corrente2 ,Conteggi_Secondi2 ,sCorrente2, sConteggi_Secondi2);
    
    
    
    
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gConteggiCorrente->SetMarkerSize(0.6);
    gConteggiCorrente->SetMarkerStyle(21);
    gConteggiCorrente->SetTitle("Conteggi/Secondi(Corrente)");
    
    gConteggiCorrente->GetXaxis()->SetTitle("Corrente [microA]");
    gConteggiCorrente->GetYaxis()->SetTitle("Conteggi/Secondi [1/s] ");
    
    
    
    
    gConteggiCorrente->Draw("AP");
    
    
    
    
    
    
    
    
}


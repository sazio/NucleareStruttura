//
//  Rate_Tensione_Macchina2_30kV.cpp
//  
// Cambio Macchina --- Ultimo giorno di laboratorio
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

void Rate_Tensione_Macchina2_30kV(){
    
    
    //numero misure
    const int nmisure = 72  ;
    
    
    // numero misure senza doppi
    const int nmisure2= 36;
    //----- DATI ------
    
    
    
    
    //Salita
    
    float Conteggi[] = {3, 5, 145, 126, 494, 476, 844, 784, 984, 1001,
                        1001, 1141, 1211, 1227, 1385, 1345, 1460, 1458, 1564, 1547,
                        1646, 1612, 1738, 1837, 1848, 1877, 2003, 2015, 2260, 2154,
    
                        2275, 2599, 2484, 2471, 2638, 2621, 2814, 2859, 2864, 2894,
                        2796, 2916, 2923, 2858, 2994, 2967, 2981, 2852, 2948, 2936,
                        2925, 2932, 2964, 2963, 2889, 2948, 2956, 2911, 3019, 2888,
        
                        2854, 2967, 3008, 2965, 2905, 2912, 2945, 2929, 2892, 2954,
                        2977, 2998
                        };
    
    cout << "Misure Conteggi: " << sizeof(Conteggi)/4 << endl;
    
    
    float Tensione[] = {380, 380, 383, 383, 385, 385, 387, 387, 390, 390,
                        392, 392, 394, 394, 397, 397, 399, 399, 402, 402,
                        404, 404, 406, 406, 409, 409, 411, 411, 413, 413,
        
                        416, 416, 418, 418, 421, 421, 423, 423, 425, 425,
                        428, 428, 430, 430, 432, 432, 435, 435, 437, 437,
                        440, 440, 442, 442, 444, 444, 447, 447, 449, 449,
    
                        454, 454, 459, 459, 463, 463, 468, 468, 473, 473,
                        478, 478};
    
    
    cout << "Misure Tensione:  " << sizeof(Tensione)/4 << endl;
    
    
    // Calcolo effettivi con medie di valori doppi
    
    float Conteggi2[nmisure2] ;
    float sConteggi2[nmisure2];
    float Tensione2[nmisure2] ;
    float sTensione2[nmisure2] ;
    
    float Secondi2[nmisure2] ;
    float sSecondi2[nmisure2];
    
    float Conteggi_Secondi2[nmisure2];
    float sConteggi_Secondi2[nmisure2];
    
    
    for( int j = 0 , i = 0  ; i < nmisure && j < nmisure2 ; i++, j++)
    { if(Tensione[i] == Tensione[i+1]){
        Tensione2[j]= Tensione[i] ;
        cout << "Tensione" << j <<" : "  <<  Tensione2[j] << endl ;
        Conteggi2[j] = (Conteggi[i]+Conteggi[i+1])/2 ;
        cout << "Conteggi" << j <<" : "  <<  Conteggi2[j] << endl ;
        i = i + 1 ;
    }
    else { Tensione2[j] = Tensione[i];
        Conteggi2[j] = Conteggi[i];
        
        
    }
        
    }
    
    
    for(int i = 0 ; i < nmisure2 ; i++){
        sConteggi2[i] = 1 ;
        Secondi2[i] = 20 ;
        sSecondi2[i] = 0.001;
        sTensione2[i] = 0;
        
        Conteggi_Secondi2[i] = Conteggi2[i]/Secondi2[i];
        sConteggi_Secondi2[i] = sqrt(((sConteggi2[i]/Secondi2[i])*(sConteggi2[i]/Secondi2[i])) + ((Conteggi2[i]*sSecondi2[i]/Secondi2[i])*(Conteggi2[i]*sSecondi2[i]/Secondi2[i])));
        
    }
    
    
    
    
    
    
    
    
    
    
    //--------------- FIT Dati -------- //
    
    TCanvas *cConteggiTensione = new TCanvas("cConteggiTensione ","Conteggi/s(Tensione)",200,10,600,400);
    
    
    TGraphErrors *gConteggiTensione = new TGraphErrors(nmisure2 , Tensione2 ,Conteggi_Secondi2 ,sTensione2, sConteggi_Secondi2);
    
    
    
    
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gConteggiTensione->SetMarkerSize(0.6);
    gConteggiTensione->SetMarkerStyle(21);
    gConteggiTensione->SetTitle("Conteggi/Secondi(Tensione)");
    
    gConteggiTensione->GetXaxis()->SetTitle("Tensione [microA]");
    gConteggiTensione->GetYaxis()->SetTitle("Conteggi/Secondi [1/s] ");
    
    
    
    
    gConteggiTensione->Draw("AP");
    
    
    
    
    
    
    
    
}

//
//  Planck_NaCl_30kV.cpp
//  
//
//  Created by Simone Azeglio on 09/03/17.
//
// thetamin =  circa 12.6°
//

#include <iostream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include "TVirtualFitter.h"   // ci serve come supporto per i fit
#include <iomanip>            // ci serve per manipolare l'output a video
#include <math.h>

void Planck_NaCl_30kV(){
    
    
    //numero misure
    const int nmisure =  26;
    
    
    // numero misure senza doppi
    const int nmisure2= 13;
    //----- DATI ------
    
    
    
    
    //Salita
    
    float Conteggi[] = {738, 719, 755, 719, 730, 701, 767, 776, 744, 723,
                        744, 749, 792, 719, 828, 760, 756, 800, 747, 748,
                        779, 812, 828, 765, 770, 769
    };
    
    cout << "Misure Conteggi: " << sizeof(Conteggi)/4 << endl;
    
    
    float ThetaX2[]  = {11.5, 11.5, 11.67, 11.67, 11.83, 11.83, 12, 12, 12.167, 12.167,
                        12.33, 12.33, 12.5, 12.5, 12.67, 12.67, 12.83, 12.83, 13, 13,
                        13.167, 13.167, 13.33, 13.33, 13.5, 13.5
        
        
    };
    
    
    cout << "Misure ThetaX2:  " << sizeof(ThetaX2)/4 << endl;
    
    
    // Calcolo effettivi con medie di valori doppi
    
    float Conteggi2[nmisure2] ;
    float sConteggi2[nmisure2];
    float ThetaX22[nmisure2] ;
    float sThetaX22[nmisure2] ;
    
    float Secondi2[nmisure2] ;
    float sSecondi2[nmisure2];
    
    float Conteggi_Secondi2[nmisure2];
    float sConteggi_Secondi2[nmisure2];
    
    
    for( int j = 0 , i = 0  ; i < nmisure && j < nmisure2 ; i++, j++)
    { if(ThetaX2[i] == ThetaX2[i+1]){
        ThetaX22[j]= ThetaX2[i] ;
        cout << "ThetaX2" << j <<" : "  <<  ThetaX22[j] << endl ;
        Conteggi2[j] = (Conteggi[i]+Conteggi[i+1])/2 ;
        cout << "Conteggi" << j <<" : "  <<  Conteggi2[j] << endl ;
        i = i + 1 ;
    }
    else { ThetaX22[j] = ThetaX2[i];
        Conteggi2[j] = Conteggi[i];
        
        
    }
        
    }
    
    
    for(int i = 0 ; i < nmisure2 ; i++){
        sConteggi2[i] = 1 ;
        Secondi2[i] = 20 ;
        sSecondi2[i] = 0.01;
        sThetaX22[i] = 0.0;
        
        Conteggi_Secondi2[i] = Conteggi2[i]/Secondi2[i];
        sConteggi_Secondi2[i] = sqrt(((sConteggi2[i]/Secondi2[i])*(sConteggi2[i]/Secondi2[i])) + ((Conteggi2[i]*sSecondi2[i]/Secondi2[i])*(Conteggi2[i]*sSecondi2[i]/Secondi2[i])));
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    //--------------- FIT Dati -------- //
    
    
    //--------------- FIT Dati -------- //
    
    TCanvas *cThetaX2Conteggi = new TCanvas("cThetaX2Conteggi ","Conteggi(ThetaX2)",700,100,800,500);
    
    
    TGraphErrors *gThetaX2Conteggi = new TGraphErrors(nmisure2 , ThetaX22 ,Conteggi_Secondi2 ,sThetaX22, sConteggi_Secondi2);
    
    
    
    
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gThetaX2Conteggi->SetMarkerSize(0.6);
    gThetaX2Conteggi->SetMarkerStyle(21);
    gThetaX2Conteggi->SetTitle("Rate(ThetaX2)");
    
    gThetaX2Conteggi->GetXaxis()->SetTitle("ThetaX2[gradi]");
    gThetaX2Conteggi->GetYaxis()->SetTitle("Rate [1/s] ");
    
    
    
    
    gThetaX2Conteggi->Draw("AP");
    
}

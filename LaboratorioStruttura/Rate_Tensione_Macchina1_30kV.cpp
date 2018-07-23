//
//  ConteggiS_30kV.cpp
//  
//
//  Created by Simone Azeglio on 06/03/17.
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

void Rate_Tensione_Macchina1_30kV(){
    
    
    //numero misure
    const int nmisure = 59 ;
  
    
    // numero misure senza doppi
    const int nmisure2= 33 ;
    //----- DATI ------
    
    
    
    
    //Salita
   
    float Conteggi[]  = {0, 0, 0, 16, 13, 69, 76, 16, 14, 36, 50 ,109, 95, 334, 278, 800, 534, 1063, 1020, 1950, 1819, 2731, 2629, 3428, 3525, 4415, 4276, 4910, 4823, 6017, 5964, 6805, 6763, 7319, 7300, 7783, 7575,8732, 8787, 9519, 9227, 10686, 10242, 12095, 11405, 13341, 11831, 12054, 12064, 13534, 14835, 12891, 11231, 11029, 10706, 10906, 15289, 10776, 11425 };
    
   cout << "Misure Conteggi: " << sizeof(Conteggi)/4 << endl;
    
    
    float Tensione[]  = {380, 383, 385, 387, 390, 392, 394, 397, 397, 399, 399, 402, 402, 404, 404, 406, 406, 409, 409, 411, 411, 413, 413, 416, 416, 418, 418, 421, 421, 423, 423, 425, 425 , 428, 428, 430, 430, 432, 432, 435, 435, 437, 437, 440, 440, 442, 442, 444, 444, 447, 447, 449, 449, 451, 451, 454, 454, 456, 456, };

    
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
    
    gConteggiTensione->GetXaxis()->SetTitle("Tensione [V]");
    gConteggiTensione->GetYaxis()->SetTitle("Conteggi/Secondi [1/s] ");
    
gConteggiTensione->Draw("AP");
    
    
    cout << "\n\n --- Sigmoide--- \n" <<endl;
    
    TF1 *sigmoid= new TF1("sigmoid","[0]*(1/(1+exp(-x+[1])))");
    
    
    

    sigmoid->SetParameter(0, 700);
    sigmoid->GetParError(0);
    

    sigmoid->GetParameter(1);
    sigmoid->GetParError(1);
    
    
    sigmoid->SetLineColor(9);
    
    
    
    
    gConteggiTensione->Fit(sigmoid,"R+");
    
    cout << "Chi^2:" << sigmoid->GetChisquare() << ", number of DoF: " << sigmoid->GetNDF() << " (Probability: " << sigmoid->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    

    
  
    
    
    
    
    
    
}

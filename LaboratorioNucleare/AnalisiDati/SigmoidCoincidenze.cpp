//Introduzione alla Fisica Nucleare con Laboratorio
//Esperienza 3 - Raggi Cosmici
//
//@Simone Azeglio --> simone.azeglio@edu.unito.it 
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

void SigmoidCoincidenze()

{
    
    // Misura della curva di coincidenza
    
    
    
     // --------------------------- DATI ------------------------------- //
    
    // Dati presi in laboratorio: deltaT = ritardo relativo  , sdeltaT  = incertezza ritardo relativo, Rmis =  rate di coincidenze , sRmis = incertezza rate di coincidenze
    
    
   float deltaT_tot[] = { -34.5 , -34, -33.5, -33, -32.5, -32, -31.5 , -31 , -30.5,  -30, -29 , -28 ,-26 , -24, -23 ,-22,-20 , -16 , -12, -8 , -4, 0, 4, 8, 12, 16, 20, 22, 23, 24, 24.5, 25, 25.5, 26, 26.5, 27, 27.5, 28 , 28.5, 29, 29.5, 30};
    float sdeltaT_tot[] = {0.5, 0.5, 0.5,  0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 , 0.5,  0.5 ,0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,  0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
    float Rmis_tot[]  = { 0.69 , 0.79 , 1.18, 1.42 , 1.705, 2.365, 4.35, 5.15, 6.54 , 7.91, 9.59, 10.99, 11.70, 11.57 ,12.18, 12.40, 12.10, 11.35, 12.05 , 11.53, 12.40 ,11.54, 12.21, 12.00, 11.70, 12.29, 11.96, 10.87,  9.46 , 7.72, 8.84, 6.933, 6.15, 4.595, 3.8, 2.66, 1.862 , 1.262, 0.95, 0.772, 0.527 , 0.502} ;
    float sRmis_tot[] = {0.048, 0.051, 0.062 , 0.068 , 0.092, 0.109,0.149, 0.162, 0.213, 0.292 ,0.324,  0.349 , 0.361, 0.359,0.369 , 0.373, 0.368, 0.355, 0.367 ,0.359, 0.373 ,0.369474,  0.3701, 0.366 , 0.361509, 0.369474,0.365,  0.347, 0.258, 0.2499, 0.2199, 0.2057 , 0.1780,  0.1533, 0.1242, 0.094, 0.068, 0.056, 0.048, 0.043, 0.036 , 0.035};
    

     int nmisure_tot = 42 ;
    
    
    
    
    
    
    // Punti coincidenze
    
    // Creo il canvas (la tela) su cui disegnare il grafico. "cCoin_Tot" è il il suo nome in memoria
    TCanvas *cCoin_Tot = new TCanvas("cCoin_Tot ","Curva di coincidenza",200,10,600,400);
    // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
    cCoin_Tot ->SetFillColor(0);
    // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
    cCoin_Tot->cd();
    // Istanzio il grafico. Il costruttore che noi usiamo prende come argomenti:
    // il numero di misure da disegnare, l'array di misure x (=V), l'array di misure y (=i), e gli
    // array delle  rispettive incertezze
    TGraphErrors *gCoin_Tot = new TGraphErrors(nmisure_tot,deltaT_tot,Rmis_tot,sdeltaT_tot,sRmis_tot);
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gCoin_Tot ->SetMarkerSize(0.6);
    gCoin_Tot ->SetMarkerStyle(21);
    // Facile, titolo del grafico
    gCoin_Tot ->SetTitle("R(t)");
    // Titoli degli assi
    gCoin_Tot ->GetXaxis()->SetTitle("t [ns]");
    gCoin_Tot->GetYaxis()->SetTitle(" R[Hz]");
    // Do istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd()
    // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
    // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)
    gCoin_Tot ->Draw("AP");
    // ----------------------------------------------------------------- //
    

    
    
    
    
    
        // ----------------------------------------------------------------- //
    
    

    

    
    
        //// -_- - - - - - --  - -   Fit Doppia Sigmoide - - - - -  - -  - --- -  //
  
    
    cout << "\n\n --- Doppia Sigmoide--- \n" <<endl;
    
    TF1 *sigmoid= new TF1("sigmoid","[0]*((1/(1+exp(-x+[1])))*(1/(1+exp(x+[2]))))");
    
   
    
     //sigmoid->GetParameter(0);
    //sigmoid->SetParLimits(0, 11.50, 12.70 );
    sigmoid->SetParameter(0, 11.78);
    sigmoid->GetParError(0);
    
    // sigmoid->GetParameter(1);
    sigmoid->SetParameter(1, -31.03);
    sigmoid->GetParError(1);

     //sigmoid->GetParameter(2);
    sigmoid->SetParameter(2,-25.78);
    //sigmoid->SetParLimits(2, )
    sigmoid->GetParError(2);
    
    
    
   
    
    
    
    
    
    
    
    sigmoid->SetLineColor(9);
    

    
    
    gCoin_Tot->Fit(sigmoid,"M+");
    
    cout << "Chi^2:" << sigmoid->GetChisquare() << ", number of DoF: " << sigmoid->GetNDF() << " (Probability: " << sigmoid->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    
 
   }









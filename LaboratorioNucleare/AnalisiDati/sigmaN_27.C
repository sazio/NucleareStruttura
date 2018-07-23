

//    sigma in funzione di N
//  Created by MarcicraM  on 20/02/17.
//
//

#include <stdio.h>
#include <iostream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include "TVirtualFitter.h"   // ci serve come supporto per i fit
#include <iomanip>            // ci serve per manipolare l'output a video
#include <math.h>

using namespace std;

void sigmaN_27(){

    
    //DATI
     int nmisure1 = 6;
    //Salita
  float ssigma[nmisure1];
  float N[]  = { 0,1,2,3,4,5 };
    float sN[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    float sigma[]  = {34,41,47,56,72,86};
    float sFWHM[] = {2,2.0,4.0,4.0,8.0,12.0};

//Numero Misure
   

    for(int i=0;i<nmisure1;i++){
      ssigma[i]=2*(sFWHM[i]/2.355)*sigma[i];
      sigma[i]=sigma[i]*sigma[i];
      //N[i]=N[i];
    }

   
    //--------------- FIT Dati -------- //
    
    
    

    TGraphErrors *gNsigma = new TGraphErrors(nmisure1,N,sigma,sN,ssigma);
   



   // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
 gNsigma->SetMarkerSize(0.6);
   gNsigma->SetMarkerStyle(21);

   gNsigma->GetXaxis()->SetTitle("N ");
   gNsigma->GetYaxis()->SetTitle("sigma quadro");

    
    //// -_- - - - - - --  - -   Fit Lineare Salita - - - - -  - -  - --- -  //
    
     TCanvas *cNsigma = new TCanvas("cNsigma","Fit Lineari ",200,10,600,400);
    cNsigma->SetFillColor(0);
  // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
  cNsigma->cd();
    TF1 *LinearSalita = new TF1("LinearSalita", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
gNsigma ->Fit(LinearSalita);
    cout << "Angular coefficient: " << LinearSalita->GetParameter(1) << " +- " << LinearSalita->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
   cout << "Chi^2:" << LinearSalita->GetChisquare() << ", number of DoF: " << LinearSalita->GetNDF() << " (Probability: " << LinearSalita->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
  
    
    
   gNsigma->Draw("AP");
    

    
    


}

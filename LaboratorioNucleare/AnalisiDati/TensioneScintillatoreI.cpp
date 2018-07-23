//
//  TensioneScintillatoreI.cpp
//  
//
//  Created by Simone Azeglio on 18/02/17.
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

void TensioneScintillatoreI(){
    
    //Impostazioni della HV di alimentazione e delle soglie dei discriminatori
    
    
    
    // --------------------------- DATI ------------------------------- //
    
    // Dati presi in laboratorio: HV = tensione di lavoro , sHV = incertezza tensione, LogN =  logaritmo dei conteggi , sLogN = incertezza logaritmo dei conteggi
    // tutti gli scintillatori sono stati divisi in due parti per fare un fit con due rette, in modo da trovare il "ginocchio " che identifica il punto di lavoro}
    
    
    const int nmisure0_I1 =5 ;
    const int nmisure0_I2 =6 ;
    
    //Prima Parte
    
    float HV_I1[]  = {1396, 1436, 1476, 1515, 1556};
    float sHV_I1[] = {1, 1, 1, 1, 1};
    
    
    float N_I1[] = {177, 372, 727, 1260, 2012} ;
    
    
    float LogN_I1[nmisure0_I1] ;
    for(int i = 0 ; i <nmisure0_I1; i++)
        LogN_I1[i] =  log10(N_I1[i]) ;
    
    float sLogN_I1[nmisure0_I1] ;
    for(int i = 0 ; i <nmisure0_I1; i++)
        sLogN_I1[i] = sqrt(N_I1[i])/N_I1[i] ;
    
    //Seconda Parte
    
    
    float HV_I2[]  = { 1596, 1637, 1676, 1716, 1757, 1797};
    float sHV_I2[] = { 1, 1, 1, 1, 1, 1};
    
    
    float N_I2[] = { 3241, 5047, 7333, 10536, 15107, 24400} ;
    
    
    float LogN_I2[nmisure0_I2] ;
    for(int i = 0 ; i <nmisure0_I2; i++)
        LogN_I2[i] =  log10(N_I2[i]) ;
    
    float sLogN_I2[nmisure0_I2] ;
    for(int i = 0 ; i <nmisure0_I2; i++)
        sLogN_I2[i] = sqrt(N_I2[i])/N_I2[i] ;
    
    
    
    // --------------------- Grafico LogN(HV) - Logaritmo conteggi in funzione di tensione di lavoro ------------------------------ //
    
    
    // Scintillatore I1
    
    
    TGraphErrors *gHV_LogN_I1 = new TGraphErrors(nmisure0_I1,HV_I1,LogN_I1,sHV_I1,sLogN_I1);
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gHV_LogN_I1->SetMarkerSize(0.6);
    gHV_LogN_I1->SetMarkerStyle(21);
    
    // Scintillatore I2
    
    
    TGraphErrors *gHV_LogN_I2 = new TGraphErrors(nmisure0_I2,HV_I2,LogN_I2,sHV_I2,sLogN_I2);
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gHV_LogN_I2->SetMarkerSize(0.6);
    gHV_LogN_I2->SetMarkerStyle(21);
    
/*
 
 // Scintillatore I
 
 // Creo il canvas (la tela) su cui disegnare il grafico. "cHV" è il il suo nome in memoria
 TCanvas *cHV_LogN_I = new TCanvas("cHV_LogN_I","LogN(HV)  -- Scintillatore I",200,10,600,400);
 // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
 cHV_LogN_I ->SetFillColor(0);
 // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
 cHV_LogN_I->cd();
 // Istanzio il grafico. Il costruttore che noi usiamo prende come argomenti:
 // il numero di misure da disegnare, l'array di misure x (=V), l'array di misure y (=i), e gli
 // array delle  rispettive incertezze
 TGraphErrors *gHV_LogN_I = new TGraphErrors(nmisure0_I,HV_I,LogN_I,sHV_I,sLogN_I);
 // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
 // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
 gHV_LogN_I ->SetMarkerSize(0.6);
 gHV_LogN_I ->SetMarkerStyle(21);
 // Facile, titolo del grafico
 gHV_LogN_I ->SetTitle("LogN(HV)");
 // Titoli degli assi
 gHV_LogN_I ->GetXaxis()->SetTitle("HV [mV]");
 gHV_LogN_I ->GetYaxis()->SetTitle("LogN []");
 // Do istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd()
 // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
 // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)
 gHV_LogN_I ->Draw("AP");
 // ----------------------------------------------------------------- //
 
 */
    
    
    
    
    //// -_- - - - - - --  - -   Fit  Scintillatore I_1 - - - - -  - -  - --- -  //
    
    TCanvas *cHV_LogN_I = new TCanvas("cHV_LogN_I","LogN(HV) -- Scintillatore I ",200,10,600,400);
    
    TF1 *ScintillatoreI1_Salita = new TF1("ScintillatoreI1_Salita", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gHV_LogN_I1 ->Fit(ScintillatoreI1_Salita);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << ScintillatoreI1_Salita->GetParameter(1) << " +- " << ScintillatoreI1_Salita->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << ScintillatoreI1_Salita->GetChisquare() << ", number of DoF: " << ScintillatoreI1_Salita->GetNDF() << " (Probability: " << ScintillatoreI1_Salita->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    
    
    
    //// -_- - - - - - --  - -  DIOPORCO Fit  Scintillatore I_2 - - - - -  - -  - --- -  //
    
    
    TF1 *ScintillatoreI2_Salita = new TF1("ScintillatoreI2_Salita", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gHV_LogN_I2 ->Fit(ScintillatoreI2_Salita);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << ScintillatoreI2_Salita->GetParameter(1) << " +- " << ScintillatoreI2_Salita->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << ScintillatoreI2_Salita->GetChisquare() << ", number of DoF: " << ScintillatoreI2_Salita->GetNDF() << " (Probability: " << ScintillatoreI2_Salita->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    
    
    // Troviamo intersezione rette utilizzando i parametri forniti dal best fit di root
    cout << "Intersezione rette: " << (ScintillatoreI1_Salita->GetParameter(0)-ScintillatoreI2_Salita->GetParameter(0))/ (ScintillatoreI2_Salita->GetParameter(1)-ScintillatoreI1_Salita->GetParameter(1)) << endl ;
    
    
    
    //---- - -- - - - -  - Unisco i  Grafici
    
    
    TMultiGraph *MergedGraphs4 = new TMultiGraph();
    MergedGraphs4->Add( gHV_LogN_I1);
    MergedGraphs4->Add( gHV_LogN_I2);
   

MergedGraphs4->Draw("AP"); 
    MergedGraphs4->GetXaxis()->SetTitle("HV[V]");
  MergedGraphs4->GetYaxis()->SetTitle("Log(N)");

gPad->Modified();
    
    


}

//
//  TensioneScintillatoreM.cpp
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

void TensioneScintillatoreM()
{


    //Impostazioni della HV di alimentazione e delle soglie dei discriminatori
    
    
     
     // --------------------------- DATI ------------------------------- //
     
     // Dati presi in laboratorio: HV = tensione di lavoro , sHV = incertezza tensione, LogN =  logaritmo dei conteggi , sLogN = incertezza logaritmo dei conteggi
     // tutti gli scintillatori sono stati divisi in due parti per fare un fit con due rette, in modo da trovare il "ginocchio " che identifica il punto di lavoro}
    
    

//Scintillatore M

const int nmisure0_M1 = 5;
const int nmisure0_M2 = 6;



// Prima Parte

float HV_M1[]  = {1295, 1335, 1375, 1415, 1455};
float sHV_M1[] = {1, 1, 1, 1, 1};


float N_M1[] = {122, 234, 498, 847, 1387};


float LogN_M1[nmisure0_M1] ;
for(int i = 0 ; i <nmisure0_M1; i++)
LogN_M1[i] =  log10(LogN_M1[i]) ;

float sLogN_M1[nmisure0_M1] ;
for(int i = 0 ; i <nmisure0_M1; i++)
sLogN_M1[i] = sqrt(N_M1[i])/N_M1[i] ;

// Seconda Parte

float HV_M2[]  = { 1496, 1536, 1576, 1616, 1656, 1696};
float sHV_M2[] = { 1, 1, 1, 1, 1, 1};


float N_M2[] = { 2364, 4193, 6320, 9482, 13796, 21873} ;


float LogN_M2[nmisure0_M2] ;
for(int i = 0 ; i <nmisure0_M2; i++)
LogN_M2[i] =  log10(N_M2[i]) ;

float sLogN_M2[nmisure0_M2] ;
for(int i = 0 ; i <nmisure0_M2; i++)
sLogN_M2[i] = sqrt(N_M2[i])/N_M2[i] ;

    
    
    // --------------------- Grafico LogN(HV) - Logaritmo conteggi in funzione di tensione di lavoro ------------------------------ //
    
    
    
    // Scintillatore N1
    
    
    TGraphErrors *gHV_LogN_M1 = new TGraphErrors(nmisure0_M1,HV_M1,LogN_M1,sHV_M1,sLogN_M1);
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gHV_LogN_M1->SetMarkerSize(0.6);
    gHV_LogN_M1->SetMarkerStyle(21);
    
    // Scintillatore N2
    
    
    TGraphErrors *gHV_LogN_M2 = new TGraphErrors(nmisure0_M2,HV_M2,LogN_M2,sHV_M2,sLogN_M2);
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gHV_LogN_M2->SetMarkerSize(0.6);
    gHV_LogN_M2->SetMarkerStyle(21);
    
    
    
 /*
    
  // Modelli per il fit non TMultigraph --- Eventualmente da utilizzare per polinomio
  
  
    // Scintillatore M
    
    // Creo il canvas (la tela) su cui disegnare il grafico. "cHV" è il il suo nome in memoria
    TCanvas *cHV_LogN_M = new TCanvas("cHV_LogN_M","LogN(HV)  -- Scintillatore M",200,10,600,400);
    // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
    cHV_LogN_M->SetFillColor(0);
    // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
    cHV_LogN_M->cd();
    // Istanzio il grafico. Il costruttore che noi usiamo prende come argomenti:
    // il numero di misure da disegnare, l'array di misure x (=V), l'array di misure y (=i), e gli
    // array delle  rispettive incertezze
    TGraphErrors *gHV_LogN_M = new TGraphErrors(nmisure0_M,HV_M,LogN_M,sHV_M,sLogN_M);
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gHV_LogN_M ->SetMarkerSize(0.6);
    gHV_LogN_M ->SetMarkerStyle(21);
    // Facile, titolo del grafico
    gHV_LogN_M ->SetTitle("LogN(HV)");
    // Titoli degli assi
    gHV_LogN_M ->GetXaxis()->SetTitle("HV [mV]");
    gHV_LogN_M ->GetYaxis()->SetTitle("LogN []");
    // Do istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd()
    // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
    // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)
    gHV_LogN_M ->Draw("AP");
    // ----------------------------------------------------------------- //
    
    */
    
    
    //--------------- FIT Dati -------- //
    
    
    TCanvas *cHV_LogN_M = new TCanvas("cHV_LogN_M","LogN(HV) -- Scintillatore M ",200,20,600,400);
    
    //// -_- - - - - - --  - -   Fit  Scintillatore M_1 - - - - -  - -  - --- -  //
    
    
    TF1 *ScintillatoreM1_Salita = new TF1("ScintillatoreM1_Salita", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gHV_LogN_M1 ->Fit(ScintillatoreM1_Salita);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << ScintillatoreM1_Salita->GetParameter(1) << " +- " << ScintillatoreM1_Salita->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << ScintillatoreM1_Salita->GetChisquare() << ", number of DoF: " << ScintillatoreM1_Salita->GetNDF() << " (Probability: " << ScintillatoreM1_Salita->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    
    
    
    //// -_- - - - - - --  - -   Fit  Scintillatore M_2 - - - - -  - -  - --- -  //
    
    
    TF1 *ScintillatoreM2_Salita = new TF1("ScintillatoreM2_Salita", "[1] * x + [0]");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gHV_LogN_M2 ->Fit(ScintillatoreM2_Salita);
    // Stampa a video il valore del coefficiente angolare e dell'incertezza su di esso
    cout << "Angular coefficient: " << ScintillatoreM2_Salita->GetParameter(1) << " +- " << ScintillatoreM2_Salita->GetParError(1) << endl;
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << ScintillatoreM2_Salita->GetChisquare() << ", number of DoF: " << ScintillatoreM2_Salita->GetNDF() << " (Probability: " << ScintillatoreM2_Salita->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    
    // Troviamo intersezione rette utilizzando i parametri forniti dal best fit di root
    cout << "Intersezione rette: " << (ScintillatoreM1_Salita->GetParameter(0)-ScintillatoreM2_Salita->GetParameter(0))/ (ScintillatoreM2_Salita->GetParameter(1)-ScintillatoreM1_Salita->GetParameter(1)) << endl ;
    
    //---- - -- - - - -  - Unisco i  Grafici
    
    
    
    
    TMultiGraph *MergedGraphs = new TMultiGraph();
    MergedGraphs->Add( gHV_LogN_M1);
    MergedGraphs->Add(  gHV_LogN_M2);
    
    
    
    
    MergedGraphs->Draw("AP");
    MergedGraphs->GetXaxis()->SetTitle("HV[V]");
  MergedGraphs->GetYaxis()->SetTitle("Log(N)");

gPad->Modified();
    
    


}

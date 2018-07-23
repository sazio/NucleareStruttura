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

void Parte2()
{
    
    //---------------------------Parte 2 ------------------------//
    
    // Misure Con la Cosmic Box
    
    
   // const double pi = 3.141592654 ;
    //const  double erroreRad = 0.043633;
    
    
    
    // Misura della distribuzione angolare dei raggi cosmici
    
    // --------------------------- DATI ------------------------------- //
    
    // Dati presi in laboratorio: Theta = angolo rispetto allo zenith ( -60° <= Theta <= 60°) , sTheta = incertezza angolo rispetto allo zenith , R = Rate, sR = incertezza Rate
    
    float Theta[]  = {-1.047 , -0.698, -0.349 ,0 , 0.349 , 0.698 , 1.047 };
    float sTheta[] = {0.044, 0.044, 0.044, 0.044, 0.044, 0.044, 0.044};
    float R[]  = {0.097,0.198, 0.298, 0.286, 0.249, 0.197,0.078  };
    float sR[] = {0.005, 0.008, 0.013, 0.009, 0.0144 , 0.007 ,0.004 };
    
    // numero misure
    int nmisure0 = 7  ;
    
    
    // --------------------- Grafico Rate(Theta) - Rate in funzione dell' angolo ------------------------------ //
    
    
    // Creo il canvas (la tela) su cui disegnare il grafico. "cHV" è il il suo nome in memoria
    TCanvas *cTheta_Rate = new TCanvas("cTheta_Rate","Rate(Theta)",200,10,600,400);
    // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
    cTheta_Rate->SetFillColor(0);
    // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
    cTheta_Rate->cd();
    // Istanzio il grafico. Il costruttore che noi usiamo prende come argomenti:
    // il numero di misure da disegnare, l'array di misure x (=V), l'array di misure y (=i), e gli
    // array delle  rispettive incertezze
    TGraphErrors *gTheta_Rate = new TGraphErrors(nmisure0 ,Theta,R, sTheta,sR);
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gTheta_Rate ->SetMarkerSize(0.6);
    gTheta_Rate ->SetMarkerStyle(21);
    // Facile, titolo del grafico
    gTheta_Rate->SetTitle("Rate(Theta)");
    // Titoli degli assi
    gTheta_Rate ->GetXaxis()->SetTitle("Theta [°]");
    gTheta_Rate->GetYaxis()->SetTitle("Rate[]");
    // Do istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd()
    // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
    // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)
    gTheta_Rate ->Draw("AP");
    // ----------------------------------------------------------------- //
    
    
    //--------------- FIT Dati -------- //
    
    
    //// -_- - - - - - --  - -   Fit Distribuzione angolare  - - - - -  - -  - --- -  //
    
    
    TF1 *AngDistribution = new TF1("AngDistribution", "[0]*((cos(x))^[1])");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gTheta_Rate->Fit(AngDistribution);
    //AngDistribution -> SetParameter(0,)
    //AngDistribution -> SetParameter(1,)
    
        // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << AngDistribution->GetChisquare() << ", number of DoF: " << AngDistribution->GetNDF() << " (Probability: " << AngDistribution->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

    
    
    
    
    // OoooooooOOOOOoooooooooO --- OoooooooOOOOOoooooooooO --- OoooooooOOOOOoooooooooO --- OoooooooOOOOOoooooooooO --- OoooooooOOOOOoooooooooO //
    
    // Misura  del flusso di raggi cosmici
    
    // --------------------------- DATI ------------------------------- //
    
    // Dati presi in laboratorio: Spessore = Spessore in cm, sSpessore = Spessore , R_Flusso = Rate , sR_Flusso = incertezza Rate
    
    float Spessore[]  = {0,1.316,3.6};
    float sSpessore[] = {0.011,0.022,0.0088};
    float R_Flusso[]  = {0.5502, 0.3965, 0.2865}; // Tutte con distanza 30 cm tra i moduli della cosmic box
    float sR_Flusso[] = {0.0229, 0.0125, 0.0088};
    
    // numero misure
    int nmisure1 =3 ;
    
    
    // --------------------- Grafico R_Flusso(Spessore) - Rate in funzione dello spessore ------------------------------ //
    
    
    // Creo il canvas (la tela) su cui disegnare il grafico. "cHV" è il il suo nome in memoria
    TCanvas *cSpessore_R_Flusso = new TCanvas("cSpessore_R_Flusso","Rate_Flusso(Spessore)",200,10,600,400);
    // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
    cSpessore_R_Flusso->SetFillColor(0);
    // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
    cSpessore_R_Flusso->cd();
    // Istanzio il grafico. Il costruttore che noi usiamo prende come argomenti:
    // il numero di misure da disegnare, l'array di misure x (=V), l'array di misure y (=i), e gli
    // array delle  rispettive incertezze
    TGraphErrors *gSpessore_R_Flusso = new TGraphErrors(nmisure1 ,Spessore,R_Flusso, sSpessore,sR_Flusso);
    // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
    // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
    gSpessore_R_Flusso ->SetMarkerSize(0.6);
    gSpessore_R_Flusso->SetMarkerStyle(21);
    // Facile, titolo del grafico
    gSpessore_R_Flusso->SetTitle("Rate_Flusso(Spessore)");
    // Titoli degli assi
    gSpessore_R_Flusso ->GetXaxis()->SetTitle("Spessore [cm]");
    gSpessore_R_Flusso->GetYaxis()->SetTitle("Rate_Flusso[]");
    // Do istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd()
    // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
    // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)
    gSpessore_R_Flusso ->Draw("AP");
    // ----------------------------------------------------------------- //
    
    
    //--------------- FIT Dati -------- //
    
    
    //// -_- - - - - - --  - -   Fit Coefficiente di Estinzione  - - - - -  - -  - --- -  //
    
    
    TF1 *ExtinctionCoefficient = new TF1("ExtinctionCoefficient", "[0]*(exp(x*[1]))");
    // Chiedi al grafico di effettuare il fit con la funzione "linear" definita sopra.
    gSpessore_R_Flusso->Fit(ExtinctionCoefficient);
    //ExtinctionCoefficient -> SetParameter(0,)
    //ExtinctionCoefficient -> SetParameter(1,)
    
    
    // Stampa a video i risultati del test di chi2 sulla bontà del fit
    cout << "Chi^2:" << ExtinctionCoefficient->GetChisquare() << ", number of DoF: " << ExtinctionCoefficient->GetNDF() << " (Probability: " <<ExtinctionCoefficient->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    

    
    
    
    }

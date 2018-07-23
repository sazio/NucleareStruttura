//
//  Poisson3.0.cpp
//  
//
//  Created by Simone Azeglio on 20/02/17.
//
//

#include "TH1.h"
#include "TF1.h"
#include "TMath.h"
#include <math.h>
#include  <iostream>

using namespace std ;

void Poisson3_0(){
    
    /*
     
     Valori di riferimento per i range -- Inutili nel codice ma solo come controllo per pescare 
     dal file di importazione i giusti conteggi
     
     double X_g1_Begin =  -212  ;
     double X_g1_End =  283.3;
     
     double X_g2_Begin = 287.170;
     double X_g2_End = 776.175;
     
     double X_g3_Begin = 778.23  ;
     double X_g3_End = 1264.23;
     
     double X_g4_Begin = 1263.5;
     double X_g4_End = 1750.5;
     
     double X_g5_Begin = 1754;
     double X_g5_End = 2234 ;
     
     double X_g6_Begin = 2233;
     double X_g6_End = 2715;
     
     double X_g7_Begin = 2717;
     double X_g7_End = 3195;
     
     
     */
    
    
    
    // Conteggi prima Gaussiana
    
    Float_t Conteggi_1[] = {3, 1, 0, 0, 1, 2, 1, 4, 1, 4, 10, 2, 6, 10, 9, 13, 25, 29, 35, 68, 61, 116, 178, 276, 441, 629, 870, 1071, 1319, 1425, 1672, 1563, 1513, 1357, 1178, 902, 680, 552, 376, 228, 165, 97, 81, 56, 32, 47, 45, 38, 35, 30, 34, 35, 35, 32, 30, 23, 24, 25, 26, 31, 33};
    
    Float_t somma1 = 0  ;
    
    // Calcolo somma dei conteggi nel range della prima Gaussiana in modo da fare
    // un nuovo istogramma
    
    
    // N.B. sizeof() mi da il valore in  bit --> essendo un float tipicamente di 4 bit , per avere
    // il numero di elementi sono costretto a fare sizeof()/4
    for(int index = 0 ; index < sizeof(Conteggi_1)/4; index++){
        somma1 = somma1 + Conteggi_1[index] ;
    }
    
    // Ripeto la procedura per le Gaussiane rimanenti
    
    Float_t Conteggi_2[] = {28, 22, 38, 33, 38, 31, 25, 36, 38, 50, 58, 62, 54, 72, 92, 114, 162, 197, 273, 383, 506, 703, 952, 1263, 1678, 2155, 2491, 2979, 3286, 3502, 3777, 3709, 3480, 3122, 2730, 2308, 1897, 1435, 1117, 835, 611, 476, 308, 310, 233, 229, 224, 205, 212, 252, 224, 218, 238, 239, 222, 245, 232, 256, 221, 263, 237};
    
    Float_t somma2 = 0  ;
    
    for(int index = 0 ; index < sizeof(Conteggi_2)/4 ; index++){
        somma2 = somma2 + Conteggi_2[index] ;
    }
    
    
    Float_t Conteggi_3[] = {263, 260, 246, 232, 252, 248, 262, 296, 279, 290, 326, 326, 359, 375, 435, 470, 507, 654, 782, 950, 1197, 1562, 1947, 2373, 2891, 3458, 3885, 4317, 4790, 4980, 5309, 5214, 5111, 4665, 4220, 3745, 3166, 2671, 2129, 1683, 1332, 1137, 878, 756, 645, 599, 609, 558, 547, 547, 563, 576, 662, 643, 596, 642, 650, 668, 649, 652, 694};
    
    
    Float_t somma3 = 0  ;
    
    for(int index = 0 ; index < sizeof(Conteggi_3)/4 ; index++){
        somma3 = somma3 + Conteggi_3[index] ;
    }
    
    
    Float_t Conteggi_4[] = {665, 715, 758, 739, 703, 783, 769, 759, 791, 886, 928, 874, 975, 987, 1055, 1141, 1272, 1512, 1587, 1817, 2062, 2595, 2957, 3529, 3823, 4430, 4908, 5363, 5643, 5819, 5987, 5908, 5611, 5452, 5100, 4561, 3843, 3315, 2892, 2458, 2090, 1752, 1513, 1361, 1266, 1117, 1086, 1124, 1053, 1107, 1148, 1073, 1150, 1184, 1110, 1192, 1195, 1254, 1218, 1283, 1229};
    
    
    Float_t somma4 = 0  ;
    
    for(int index = 0 ; index < sizeof(Conteggi_4)/4 ; index++){
        somma4 = somma4 + Conteggi_4[index] ;
    }
    
    
    
    Float_t Conteggi_5[] = {1252, 1316, 1359, 1333, 1384, 1397, 1420, 1512, 1481, 1574, 1633, 1537, 1673, 1763, 1901, 2015, 2110, 2403, 2576, 2920, 3099, 3380, 3853, 4037, 4509, 4985, 5252, 5571, 5764, 5790, 5942, 5860, 5621, 5235, 5020, 4704, 4351, 3691, 3423, 2831, 2621, 2257, 2090, 1900, 1695, 1645, 1682, 1611, 1682, 1592, 1670, 1664, 1729, 1683, 1796, 1694, 1877, 1704, 1827, 1971};
    
    
    Float_t somma5 = 0  ;
    
    for(int index = 0 ; index < sizeof(Conteggi_5)/4 ; index++){
        somma5 = somma5 + Conteggi_5[index] ;
    }
    
    
    Float_t Conteggi_6[] = {1958, 1936, 1939, 1922, 1979, 1993, 2064, 2085, 2168, 2114, 2205, 2307, 2266, 2438, 2489, 2577, 2722, 2898, 3103, 3164, 3438, 3607, 3969, 4128, 4412, 4770, 5168, 4987, 5244, 5470, 5389, 5455, 5362, 5245, 4868, 4666, 4393, 3933, 3769, 3406, 3229, 2845, 2621, 2520, 2415, 2271, 2300, 2179, 2061, 2155, 2092, 2156, 2166, 2184, 2201, 2243, 2272, 2278, 2433, 2305};
    
    Float_t somma6 = 0  ;
    
    for(int index = 0 ; index < sizeof(Conteggi_6)/4 ; index++){
        somma6 = somma6 + Conteggi_6[index] ;
    }

    Float_t Conteggi_7[] = {2289, 2399, 2441, 2520, 2545, 2627, 2564, 2523, 2618, 2623, 2754, 2756, 2781, 2977, 2905, 3047, 3115, 3402, 3487, 3769, 3740, 3878, 4043, 4169, 4387, 4406, 4755, 4800, 4843, 4729, 4924, 4772, 4770, 4531, 4275, 4124, 3788, 3759, 3530, 3337, 3114, 3048, 2774, 2779, 2650, 2615, 2508, 2392, 2449, 2407, 2581, 2420, 2556, 2572, 2561, 2577, 2640, 2561, 2617};
    
    Float_t somma7 = 0  ;
    
    for(int index = 0 ; index < sizeof(Conteggi_7)/4 ; index++){
        somma7 = somma7 + Conteggi_7[index] ;
    }

    
    
    // A questo punto definisco il numero di bin per l' istogramma
    // i dati sono le somme dei conteggi per ogni gaussiana
    const Int_t np = 7;
    Float_t x[np] = {somma1, somma2, somma3, somma4, somma5, somma6, somma7};
    
    Float_t x_error[np] ;
    
    for(int i = 0 ; i < np ; i++)
    { x_error[i] = sqrt(x[i]);
    }
    
    
    
    
    // Istanzio l' istogramma
    //
    //CERCARE OPZIONI EDITING IN MODO DA FARLO PIU' CARINO
    
    TH1F *h = new TH1F("h","Poisson",np,0,7);
    h->SetMaximum(300000);
    h->GetXaxis()->SetTitle("X");
    h->GetYaxis()->SetTitle("Y");
    h->Draw();
    
    for (int i=0;i<np;i++) {
        h->SetBinContent(i+1,x[i]);
    }
    
    
    
    
    
    
    
    // Definisco la Distribuzione di Poisson tramite funzione gamma per esprimere l'esponenziale
    
    TF1 *f1 = new TF1("f1","[0]*TMath::Power(([1]/[2]),(x/[2]))*(TMath::Exp(-([1]/[2])))/TMath::Gamma((x/[2])+1)", 0, 7); // "xmin" = 0, "xmax" = 7
    f1->SetParameters(1, 4.533, 1); // you MUST set non-zero initial values for parameters
    h->Fit("f1", "R"); // "R" = fit between "xmin" and "xmax" of the "f1"
    f1 ->SetLineColor(4);
    
    
    
    
    
    
    
    
    
}



//
//  DimensioneAtomica_KCl.cpp
//  
//
//  Created by Simone Azeglio on 08/03/17.
//
//


Double_t MultiGaussianPeaks(Double_t *x, Double_t *par){
    return (par[0] + par[1]*x[0] + par[2]*x[0]*x[0]+ par[3]*x[0]*x[0]*x[0]+
            par[4]*TMath::Exp(-0.5*((x[0]-par[5])*(x[0]-par[5]))/(2*par[6]*par[6])));}



void DimensioneAtomica_KCl(){


//numero misure
const int nmisure =  60 ;


// numero misure senza doppi
const int nmisure2= 30;
//----- DATI ------




//Salita

float Conteggi[] = {22,  36, 31, 39, 31, 35, 38, 31, 34, 35,
                    31, 32, 32, 38, 30, 42, 29, 33, 45, 28,
                    42, 36, 35, 26, 34, 42, 49, 41,
    
                    47, 46, 46, 56, 54, 57, 58, 65, 102, 95,
                    116, 130, 166, 175, 185, 200, 177, 197, 188, 183,
                    168, 138, 107, 117, 70, 71, 43, 40, 32, 31, 38, 40
    
    
    
    
};

cout << "Misure Conteggi: " << sizeof(Conteggi)/4 << endl;


float ThetaX2[]  = {12, 12, 13, 13, 14, 14, 15, 15, 16, 16,
                    17, 17, 18, 18, 19, 19, 20, 20, 21, 21,
                    22, 22, 23, 23, 25, 25, 26, 26,
    
                    26.5, 26.5, 27, 27, 27.167, 27.167, 27.33, 27.33, 27.5, 27.5,
                    27.67, 27.67, 27.83, 27.83, 28, 28, 28.167, 28.167, 28.33, 28.33,
                    28.5, 28.5, 28.67, 28.67, 28.83, 28.83, 29, 29, 30, 30,
                    31, 31
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
    
    
    
    
    
    
    //--
    // create a TF1 with the range from 0 to 3 and 6 parameters
    TF1 *fitFcn = new TF1("fitFcn",MultiGaussianPeaks, 12, 31, 7);
    
    
    
    
    // Polynomial's parameters from background fitting
    
    fitFcn->SetParameter( 0,  6.045);//, 72.5);
    fitFcn->SetParameter( 1,   -3.82880e-02 );//, -0.38);
    fitFcn->SetParameter( 2,   2.16988e-03 );//, 0.000913);
    fitFcn->SetParameter( 3,   -9.45735e-07);//, -1.75e-07);
    
    
    
    
    // Setting MG parameters from par[4] to par[21]
    
    
    fitFcn->SetParameter(4, 11.44); // Constant - pol evaluated in get position x
    fitFcn->SetParameter(5, 27.9 ); // Mean
    
    // fitFcn->SetParameter(7,  5.4 ); // Constant + 7
    //fitFcn->SetParameter(8, 31.47 ); // Mean
    
    
    
    fitFcn->SetParameter(6, 0.57 );//, 32.90); // Width - rough order of mag estimate
    // fitFcn->SetParameter(9, 0.55 );// , 41.44); // Width - rough order of mag estimate
    
    
    
    
    
    
    
    // first try without starting values for the parameters
    // this defaults to 1 for each param.
    gThetaX2Conteggi->Fit(fitFcn,"R+");
    // histo->Fit("background");
    //histo->Fit("MultiGaussianPeaks");
    
    
    cout << "Chi^2:" << fitFcn->GetChisquare() << ", number of DoF: " << fitFcn->GetNDF() << " (Probability: " << fitFcn->GetProb() << ")." << endl;
    
    
    
}


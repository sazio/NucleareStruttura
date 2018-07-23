//
//  DimensioneAtomica_NaCl.cpp
//  
//
//  Created by Simone Azeglio on 08/03/17.
//
//


// Multi Gaussian function
Double_t MultiGaussianPeaks(Double_t *x, Double_t *par) {
    return (par[0] + par[1]*x[0] + par[2]*x[0]*x[0]+ par[3]*x[0]*x[0]*x[0]+
            par[4]*TMath::Exp(-0.5*((x[0]-par[5])*(x[0]-par[5]))/(2*par[6]*par[6]))+
            par[7]*TMath::Exp(-0.5*((x[0]-par[8])*(x[0]-par[8]))/(2*par[9]*par[9]))) ;
}



void DimensioneAtomica_NaCl_GradiNegativi(){



    
    
    
    //numero misure
    const int nmisure =  70 ;
    
    
    // numero misure senza doppi
    const int nmisure2= 35 ;
    //----- DATI ------
    
    
    
    
    //Salita
    
    float Conteggi[] = {420, 396, 397, 378, 374, 350, 308, 330, 259, 287,
                        203, 192, 141, 136, 106, 101, 83, 97, 116, 108,
                        82, 77, 180, 169, 285, 297, 624, 607, 1768, 1756,
        
                        5222, 5228, 7298, 7401, 8367, 8560, 9271, 9344, 9137, 9187,
                        7677, 7496, 4262, 4359, 3089, 3024, 1464, 1407, 924, 860,
                        538, 548, 258, 285, 245, 225, 212, 204, 186, 205,
                        217, 177, 176, 150, 169, 169, 169, 160, 125, 117
    
    
    
    };
    
    cout << "Misure Conteggi: " << sizeof(Conteggi)/4 << endl;
    
    
    float ThetaX2[]  = {-12, -12, -13, -13, -14, -14, -16, -16, -18, -18,
                        -20, -20, -22, -22, -24, -24, -26, -26, -28, -28,
                        -30 , -30, -30.5, -30.5, -30.67, -30.67, -30.87, -30.87, -31, -31,
        
                        -31.167, -31.167, -31.33, -31.33, -31.5, -31.5, -31.67, -31.67, -31.83, -31.83,
                        -32, -32, -32.167, -32.167, -32.33, -32.33, -32.5, -32.5, -32.67, -32.67,
                        -32.83, -32.83, -33, -33, -33.167, -33.167, -33.33, -33.33, -33.5, -33.5,
                        -33.67, -33.67, -33.83, -33.83, -34, -34, -35, -35, -36,  -36
        
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
    
    
    
    //--
    // create a TF1 with the range from 0 to 3 and 6 parameters
    TF1 *fitFcn = new TF1("fitFcn",MultiGaussianPeaks, -12, -33.5, 7);
    
    
    
    
    // Polynomial's parameters from background fitting
    
    fitFcn->SetParameter( 0,  6.045);//, 72.5);
    fitFcn->SetParameter( 1,   -3.82880e-02 );//, -0.38);
    fitFcn->SetParameter( 2,   2.16988e-03 );//, 0.000913);
    fitFcn->SetParameter( 3,   -9.45735e-07);//, -1.75e-07);
    
    
    
    
    // Setting MG parameters from par[4] to par[21]
    
    
    fitFcn->SetParameter(4, 458); // Constant - pol evaluated in get position x
    fitFcn->SetParameter(5, -31.65 ); // Mean
    fitFcn->SetParameter(6, 0.39 ); // Mean

    
    
    
    
    
    
    // first try without starting values for the parameters
    // this defaults to 1 for each param.
    gThetaX2Conteggi->Fit(fitFcn,"R+");
    // histo->Fit("background");
    //histo->Fit("MultiGaussianPeaks");
    
    
    cout << "Chi^2:" << fitFcn->GetChisquare() << ", number of DoF: " << fitFcn->GetNDF() << " (Probability: " << fitFcn->GetProb() << ")." << endl;
    
    
    




}

//////////////////////////// START APLICATIE //////////////////////////////////////

int CVICALLBACK Start_aplicatie (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			//Initializare referinta 
			GetCtrlVal (panelHandle, PANEL_NUMERIC_5, &referinta_1);
			
            //  AFISARE TEXT 
				InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"  HELLO REAL-TIME WORLD!  ");
			
			// SETARE PERIOADA DE ESANTIOANARE
				Te = 0.100;
				selectare_referinta = 0;
				
				
			// INITIALIZARE VARIABILE
				tk_1 = 0; // initializare moment de esantionare anterior
				uk_1=0; // initializare semnal de intare la momentul anterior
			    uk_2=0; // initiliazare semnal de intrare cu doua momente de esantionare in urma
				eroare_1 = 0; // initializare eroare la momentul de esantionare anterior
				eroare_2=0; // initializare eroare cu doua momente de esantioare in urma 
				perturbatiek_1 = 0; // initializare perturbatie la momentul de esantionare anterior
				temperaturak_1 = 0; // initializare temperatura la momentul de esantionare anterior 
				perturbatie2_k_1 = 0;
				temperatura2_k_1 = 0;
				activare_Compensare=0;
				activare_Perturbatie=0;
				activare_Compensare2=0;
				activare_Perturbatie2=0;
				
				// VARIABILE ELEM DE EXECUTIE
				C00 = Te/(Te+0.4);
				C0 = 0.1/(Te+0.4);
				// VARIABILE F.D.T PROCES NEPERTURBAT
 				C1 = Te/(Te+7);  
				C2 = 5/(Te+7);
				C3 = Te/(Te+2);
				// VARIABILE TRADUCTOR PROCES NEPERTURBAT
				C4 = Te/(Te+0.02);
				//C5 = 0.01/(Te+0.2);
				// VARIABILE F.D.T PROCES AFECTAT DE PERTURBATIA 1
				C1_perturbat =  Te/(Te+4); 
				C2_perturbat =  0.1/(Te+4);
				C3_perturbat =  Te/(Te+2);
				C4_perturbat = Te/(Te+1);
				
				// VARIABILE F.D.T PROCES AFECTAT DE PERTURBATIA 2
				C11_perturbat =  Te/(Te+0.2); 
				C22_perturbat =  0.5/(Te+0.2);
				C33_perturbat =  Te/(Te+1.5);
				C44_perturbat = Te/(Te+3);
								
				// VARIABILE TRADUCTOR PROCES AFECTAT DE PERTURBATIA 1
				C1_trad_perturbatie = Te/(Te+0.01);
			//	C2_trad_perturbatie = 0.2/(Te+0.4);
				// VARIABILE TRADUCTOR PROCES AFECTAT DE PERTURBATIA 2
				C11_trad_perturbatie = Te/(Te+0.02);
				
				// VARIABILE COMPENSATOR PROCES AFECTAT DE PERTURBATIA 1
				C1_comp = Te/(Te+5);
				C2_comp = 0.01/(Te+5);
				C3_comp = Te/(Te+4);
				C4_comp = 7/(Te+4);
				C5_comp = Te/(Te+1);
				C6_comp = 0.2/(Te+1);
				
				// VARIABILE COMPENSATOR PROCES AFECTAT DE PERTURBATIA 2
				C11_comp = Te/(Te+1.5);
				C22_comp = 0.5/(Te+1.5);
				C33_comp = Te/(Te+3);
				C44_comp = 7/(Te+3);
				C55_comp = Te/(Te+5);
				C66_comp = 2/(Te+5);
				C77_comp = Te/(Te+0.1);
				C88_comp = 0.02/(Te+0.1);
				
				
				pi=Pi();
				
				yk_1 = referinta_1; //  initilizare f.d.t la momentul de esantionare anterior   prima parte :(5s+1)/(7s+1)
				yk1_1 = referinta_1; // initializare f.d.t la momentul de esantionare anterior  a doua parte: 1/(2s+1)
				yk_perturbata_1 = 0; //  initilizare f.d.t perturbata la momentul de esantionare anterior   prima parte :(8s+1)/(7s+1)
				yk1_perturbata_1 = 0; // initializare f.d.t perturbata la momentul de esantionare anterior  a doua parte: 1/(4s+1)
				yk2_perturbata_1 =0;
				yk_perturbata2_1 = 0; 
				yk1_perturbata2_1 = 0; 
				yk2_perturbata2_1 =0;
				
				
				yk_traductor_1=0; // initializare f.d.t a TRADUCTORULUI la mom de esantionare anterior
				
				yk_traductor_pert_1 = 0; // initializare f.d.t a traductorului pt f.d.t perturbata la mom de esantionare anterior
				yk_traductor2_pert_1 = 0;
				yk_mat_1=0;
				yk_mat_2=0;
				yk_proces_1 = yk1_1 - yk2_perturbata_1 - yk2_perturbata2_1;
				
				PID_1=0; // initializare f.d.t a regulatorului la momentul anterior
				PID_2=0; // initializare f.d.t a regulatorului cu doua momente in urma
				
			// INITIALIZARE VARIABILE PID(regulator)
				GetCtrlVal(panel_PID,PANEL_2_NUMERIC_6,&Kr);
				GetCtrlVal(panel_PID,PANEL_2_NUMERIC_7,&Ti);
				GetCtrlVal(panel_PID,PANEL_2_NUMERIC_8,&Td);
				GetCtrlVal(panel_PID,PANEL_2_NUMERIC_9,&alpha);
				
				p0=Kr*((4/(Te*Te))*(alpha*Td*Ti+Ti*Td) + (2/Te)*(Ti+alpha*Td) + 1);
				p1=Kr*(-(8/(Te*Te))*(alpha*Td*Ti+Td*Ti) + 2);
				p2=Kr*((4/(Te*Te))*(alpha*Td*Ti+Ti*Td) - (2/Te)*(Ti+alpha*Td) + 1);
				
				q0=(4/(Te*Te))*Ti*alpha*Td + (2/Te)*Ti;
				q1=-(8/(Te*Te))*Ti*alpha*Td;
				q2=(4/(Te*Te))*Ti*alpha*Td - (2/Te)*Ti;
				
				a1=q1/q0;
				a2=q2/q0;
				b0=p0/q0;
				b1=p1/q0;
				b2=p2/q0;
				
				// INITIALIZARE ELEM DE EXECUTIE
				yk_elem_ex_1 = 0;
				
				// INITIALIZARE COMPENSATOR PERTURBATIE 1
				yk_comp1_1 = 0; 
				yk_comp2_1 = 0;
				yk_comp3_1 = 0;
				
				// INITIALIZARE COMPENSATOR PERTURBATIE 2
				yk2_comp1_1 = 0; 
				yk2_comp2_1 = 0;
				yk2_comp3_1 = 0;
				yk2_comp4_1 = 0;
				
				comutare_sin =0;
				 
					
			 
			
			// ATRIBUIRE PERIOADA DE ESANTIONARE TIMER-ULUI
				SetCtrlAttribute(panelHandle,PANEL_TIMER,ATTR_INTERVAL,Te);
			// PORNIM TIMER-UL
				SetCtrlAttribute(panelHandle,PANEL_TIMER,ATTR_ENABLED,1);
				
			// DEZACTIVAM BUTONUL DUPA CE ESTE APASAT
				SetCtrlAttribute(panelHandle,PANEL_OkButton,ATTR_DIMMED,1);
			

			break;
	}
	return 0;
}

// ----------------------- MODIFICARE PARAMETRI PID--------------------------------------
int CVICALLBACK seteaza_PID (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			//---------CITIM VALORILE PT KR,TI,TD,ALPHA--------------
			GetCtrlVal (panel_PID,PANEL_2_NUMERIC_6, &Kr); 
			GetCtrlVal (panel_PID,PANEL_2_NUMERIC_7, &Ti); 
			GetCtrlVal (panel_PID,PANEL_2_NUMERIC_8, &Td); 
			GetCtrlVal (panel_PID,PANEL_2_NUMERIC_9, &alpha); 
			
			//--------------- IMPLEMENTARE PID---------------------------	
			p0=Kr*((4/(Te*Te))*(alpha*Td*Ti+Ti*Td)+(2/Te)*(Ti+alpha*Td)+1);
			p1=Kr*(-(8/(Te*Te))*(alpha*Td*Ti+Td*Ti)+2);
			p2=Kr*((4/(Te*Te))*(alpha*Td*Ti+Td*Ti)-(2/Te)*(Ti+alpha*Td)+1);
			q0=(4/(Te*Te))*Ti*alpha*Td+(2/Te)*Ti;
			q1=-(8/(Te*Te))*Ti*alpha*Td;
			q2=(4/(Te*Te))*Ti*alpha*Td-(2/Te)*Ti;
				
				
			a1=q1/q0;
			a2=q2/q0;
			b0=p0/q0;
			b1=p1/q0;  
			b2=p2/q0;
			

			//----------- AFISAM GRAFH-UL PT COMANDA-------------------------
			SetCtrlAttribute (panelHandle, PANEL_GRAPH_2, ATTR_VISIBLE, 1);
			
			

			break;
	}
	return 0;
}

// ----------------------------- FEREASTRA PID BUTTON -----------------------------------
void CVICALLBACK setare_PID (int menuBar, int menuItem, void *callbackData,
							 int panel)
{
	DisplayPanel (panel_PID);
	//ASCUNDEM GRAPH=UL PT COMANDA
	SetCtrlAttribute (panelHandle, PANEL_GRAPH_2, ATTR_VISIBLE, 0);
	
}
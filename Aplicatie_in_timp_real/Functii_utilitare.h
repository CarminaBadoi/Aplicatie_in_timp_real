 

//-------------------------------- QUIT APLICATIE ------------------------------------------

 int CVICALLBACK QuitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

//---------------------------------REFRESH BUTTON -----------------------------------------------
int CVICALLBACK Refresh (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			//stergere grafic 
				
					DeleteGraphPlot (panelHandle, PANEL_GRAPH, -1, VAL_IMMEDIATE_DRAW );
					DeleteGraphPlot (panelHandle, PANEL_GRAPH_2, -1, VAL_IMMEDIATE_DRAW );
					
					
			//Reinitializare timp de afisare
					tk_1=0;
					tk=0;
					 
			
			

			break;
	}
	return 0;
}

// --------------------- COMPENSATOR BUTTON --------------------------------------------------

int CVICALLBACK activare_compensare (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_TOGGLEBUTTON_2, &activare_Compensare);

			break;
	}
	return 0;
}

// --------------------- PERTURBATIE BUTTON --------------------------------------------------
int CVICALLBACK activare_perturbatie (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_TOGGLEBUTTON_3, &activare_Perturbatie);
			

			break;
	}
	return 0;
}

// -------------------------- FEREASTRA PID -------------------------------------------------

int CVICALLBACK ascunde_PID (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel(panel_PID);
			SetCtrlAttribute (panelHandle, PANEL_GRAPH_2, ATTR_VISIBLE, 1);

			break;
	}
	return 0;
}
//----------------------------- COMPENSATOR 2 BUTTON --------------------------------------
int CVICALLBACK activare_compensare_2 (int panel, int control, int event,
									   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_TOGGLEBUTTON_4, &activare_Compensare2);

			break;
	}
	return 0;
}

//----------------------------- PERTURBATIE 2 BUTTON --------------------------------------

int CVICALLBACK activare_perturbatie_2 (int panel, int control, int event,
										void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_TOGGLEBUTTON_5, &activare_Perturbatie2);

			break;
	}
	return 0;
}





//--------------------------- SPLITTERS ----------------------------------


int CVICALLBACK OnPanel (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{  
	
	
	switch (event)
	{	case EVENT_PANEL_RESTORE:
		case EVENT_PANEL_MAXIMIZE:
		case EVENT_PANEL_SIZING: 
				
			
				// Splitter Vertical - Redimensionare fereastra 
				
				GetPanelAttribute(panelHandle,ATTR_WIDTH,&NewWidth);
				OperateSplitter (panelHandle, PANEL_V_SPLITTER, NewWidth-OldWidth);
				OldWidth=NewWidth;
				
				
				// Splitter Orizontal - Redimensionare fereastra 
				
				GetPanelAttribute(panelHandle,ATTR_HEIGHT,&NewHeight);
				OperateSplitter (panelHandle, PANEL_H_SPLITTER, NewHeight-OldHeight);
				OldHeight=NewHeight;
				
			
		

			break;
		
	}
	return 0;
}




 
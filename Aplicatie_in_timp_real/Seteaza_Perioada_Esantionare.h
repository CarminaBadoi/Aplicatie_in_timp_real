//------------------ SETARE PERIOADA DE ESANTIONARE DE PE INTERFATA GRAFICA ---------------------

int CVICALLBACK Setare_esantionare (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			// CITIRE PERIOADA DE ESANTIONARE
				GetCtrlVal(panelHandle,PANEL_NUMERICSLIDE,&Te);
			// ATRIBUIRE PERIOADA DE ESANTIONARE TIMER-ULUI
				SetCtrlAttribute(panelHandle,PANEL_TIMER,ATTR_INTERVAL,Te);

			break;
	}
	return 0;
}
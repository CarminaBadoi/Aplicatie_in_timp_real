/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: OnPanel */
#define  PANEL_H_SPLITTER                 2       /* control type: splitter, callback function: (none) */
#define  PANEL_LED_3                      3       /* control type: LED, callback function: (none) */
#define  PANEL_LED_2                      4       /* control type: LED, callback function: (none) */
#define  PANEL_LED                        5       /* control type: LED, callback function: (none) */
#define  PANEL_DECORATION                 6       /* control type: deco, callback function: (none) */
#define  PANEL_OkButton_2                 7       /* control type: command, callback function: Refresh */
#define  PANEL_OkButton                   8       /* control type: command, callback function: Start_aplicatie */
#define  PANEL_QUITBUTTON                 9       /* control type: command, callback function: QuitCallback */
#define  PANEL_DECORATION_2               10      /* control type: deco, callback function: (none) */
#define  PANEL_BINARYSWITCH               11      /* control type: binary, callback function: (none) */
#define  PANEL_TOGGLEBUTTON               12      /* control type: toggle, callback function: (none) */
#define  PANEL_DECORATION_3               13      /* control type: deco, callback function: (none) */
#define  PANEL_GRAPH_2                    14      /* control type: graph, callback function: (none) */
#define  PANEL_GRAPH                      15      /* control type: graph, callback function: (none) */
#define  PANEL_TEXTMSG                    16      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_2                  17      /* control type: textMsg, callback function: (none) */
#define  PANEL_NUMERICSLIDE               18      /* control type: scale, callback function: Setare_esantionare */
#define  PANEL_DECORATION_5               19      /* control type: deco, callback function: (none) */
#define  PANEL_TEXTMSG_3                  20      /* control type: textMsg, callback function: (none) */
#define  PANEL_TIMER                      21      /* control type: timer, callback function: esantionare */
#define  PANEL_TEXTMSG_6                  22      /* control type: textMsg, callback function: (none) */
#define  PANEL_DECORATION_8               23      /* control type: deco, callback function: (none) */
#define  PANEL_NUMERIC_3                  24      /* control type: numeric, callback function: modificare_panta */
#define  PANEL_NUMERIC_2                  25      /* control type: numeric, callback function: Comutare_Sinusoida */
#define  PANEL_DECORATION_7               26      /* control type: deco, callback function: (none) */
#define  PANEL_NUMERIC                    27      /* control type: numeric, callback function: Comutare_Sinusoida */
#define  PANEL_TEXTMSG_4                  28      /* control type: textMsg, callback function: (none) */
#define  PANEL_RINGSLIDE                  29      /* control type: slide, callback function: selectie_semnal */
#define  PANEL_NUMERIC_7                  30      /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_6                  31      /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_5                  32      /* control type: numeric, callback function: (none) */
#define  PANEL_TEXTBOX                    33      /* control type: textBox, callback function: (none) */
#define  PANEL_V_SPLITTER                 34      /* control type: splitter, callback function: (none) */
#define  PANEL_TOGGLEBUTTON_4             35      /* control type: textButton, callback function: activare_compensare_2 */
#define  PANEL_TOGGLEBUTTON_5             36      /* control type: textButton, callback function: activare_perturbatie_2 */
#define  PANEL_TOGGLEBUTTON_2             37      /* control type: textButton, callback function: activare_compensare */
#define  PANEL_TOGGLEBUTTON_3             38      /* control type: textButton, callback function: activare_perturbatie */

#define  PANEL_2                          2
#define  PANEL_2_NUMERIC_9                2       /* control type: numeric, callback function: (none) */
#define  PANEL_2_NUMERIC_8                3       /* control type: numeric, callback function: (none) */
#define  PANEL_2_NUMERIC_7                4       /* control type: numeric, callback function: (none) */
#define  PANEL_2_NUMERIC_6                5       /* control type: numeric, callback function: (none) */
#define  PANEL_2_COMMANDBUTTON_2          6       /* control type: command, callback function: ascunde_PID */
#define  PANEL_2_COMMANDBUTTON            7       /* control type: command, callback function: seteaza_PID */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_MENU1                    2       /* callback function: setare_PID */


     /* Callback Prototypes: */

int  CVICALLBACK activare_compensare(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK activare_compensare_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK activare_perturbatie(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK activare_perturbatie_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ascunde_PID(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Comutare_Sinusoida(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK esantionare(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK modificare_panta(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnPanel(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Refresh(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK selectie_semnal(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Setare_esantionare(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK setare_PID(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK seteaza_PID(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Start_aplicatie(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
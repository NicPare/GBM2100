/* ========================================
 *

 *
 * ========================================
*/



#include "LED_task.h"

uint32_t red_example[]={99513,98160,99413,98419,99319,98729,99145,99050,98949,99419,98798,99851,98679,99846,98657,100433,98597,100453,98713,100550,98880,100921,98942,100758,99148,100637,99243,100496,99426,100316,99677,100090,99871,99833,100155,99657,100544,99416,100533,99350,101127,99266,100986,99359,101151,99370,101493,99586,101282,99597,101251,99713,101027,99896,100926,100109,100625,100345,100369,100625,100180,100986,99983,101152,99930,101751,99809,101581,99950,101877,100112,102210,100251,102006,100391,102068,100506,101956,100783,101872,101092,101692,101296,101532,101733,101311,102054,101081,101967,100723,102263,100171,101478,99530,101051,98881,100564,98080,99478,97452,98752,96709,97796,96168,97009,95842,96177,95534,95551,95512,95055,95623,94635,95492,94373,96057,94212,95856,94325,96206,94439,96594,94606,96428,94889,96724,95093,96645,95436,96622,95818,96520,96042,96387,96551,96312,96959,96200,97075,96116,97747,96027,97625,96166,98102,96258,98464,96444,98339,96751,98615,96864,98429,97113,98280,97281,98005,97386,97811,97731,97436,97948,97145,97891,96849,98402,96607,98112,96544,98337,96419,98565,96500,98246,96486,98393,96524,98100,96726,97962,96902,97688,97033,97499,97468,97311,97709,97142,97975,97062,98518,96929,98493,97060,98982,97142,99388,97406,99269,97602,99597,97792,99457,98096,99419,98376,99307,98614,99245,99053,99051,99352,98867,99665,98764,100215,98688,100144,98743,100627,98752,100923,99032,100799,99094,101111,99244,100868,99403,100797,99621,100589,99763,100377,100100,100140,100269,99873,100563,99674,101021,99524,100969,99551,101462,99564,101645,99692,101446,99770,101803,99901,101652,100125,101504,100279,101331,100457,101110,100778,100915,101007,100671,101289,100594,101818,100354,101721,100377,102270,100321,102378,100537,102362,100684,102799,100805,102585,101090,102610,101267,102405,101459,102259,101910,102105,102156,101966,102442,101795,102953,101616,102905,101644,103542,101586,103483,101618,103314,101416,103288,101016,102513,100613,101743,99933,100761,99438,99818,98908,98895,98425,97997,98168,97200,98008,96533,97569,96158,97837,95820,97544,95761,97496,95758,97826,95863,97578,96039,97544,96209,97493,96416,97421,96883,97340,97182,97235,97562,97114,98095,96945,98143,96973,98853,96974,98857,97165,98978,97281,99411,97496,99321,97713,99313,97941,99350,98204,99231,98616,99012,98810,98849,99134,98638,99428,98363,99388,98216,99901,98003,99655,97962,99784,97948,99986,97911,99593,97960,99546,97939,99346,98064,99033,98266,98767,98423,98492,98790,98286,99049,98060,99135,98070,99760,97914,99640,98075,99966,98171,100331,98381,100160,98601,100328,98727,100235,99008,100150,99380,100052,99587,99866,99999,99681,100388,99521,100534,99535,101232,99437,101096,99553,101549,99678,101880,99849,101663,99997,101840,100117,101669,100358,101584,100661,101355,100847,101152,101279,100994,101606,100701,101727,100661,102257,100528,102111,100565,102442,100591,102682,100713,102452,100867,102660,100910,102439,101096,102297,101381,102126,101522,101913,101866,101702,102110,101474,102269,101232,102835,101144,102648,101153,103101,101198,103388,101404,103117,101489,103464,101591,103194,101805,103113,102042,102864,102200,102734,102590,102568,102887,102306,103113,102215,103662,102059,103543,102114,104015,102120,104256,102225,104045,102277,104156,102136,103574,101862,102947,101460,102046,100931,101066,100578,100157,100099,99211,99599,98448,99493,97657,98822,97202,98869,96803,98729,96627,98274,96483,98387,96413,98019,96627,97867,96705,97693,96918,97569,97361,97458,97688,97321,97990,97306,98588,97221,98684,97381,99330,97427,99492,97609,99450,97792,99808,97969,99740,98258,99660,98447,99583,98721,99526,99143,99402,99453,99175,99728,99006,100126,98758,100009,98681,100577,98530,100456,98552,100286,98493,100535,98475,100160,98571,99984,98623,99718,98645,99416,98885,99089,99001,98805,99246,98542,99592,98317,99538,98247,100102,98237,100083,98335,100150,98422,100539,98591,100384,98835,100372,98999,100288,99222,100149,99602,100040,99969,99851,100286,99750,100700,99585,100777,99593,101437,99550,101359,99661,101543,99773,101933,99951,101728,100164,101782,100267,101628,100494,101441,100780,101297,100990,101068,101362,100900,101679,100687,101784,100632,102358,100470,102224,100521,102395,100604,102649,100688,102500,100863,102489,100962,102295,101082,102160,101407,101901,101577,101678,101890,101420,102240,101237,102216,101126,102821,101008,102727,101077,102969,101091,103267,101272,103033,101397,103130,101441,102903,101683,102784,101920,102619,102118,102339,102494,102205,102859,101992,102968,101852,103588,101727,103469,101826,103746,101949,104055,102012,103823,102202,103910,101995,103385,101834,102735,101494,101924,100942,100911,100592,99908,100058,98927,99451,98085,99407,97319,98581,96835,98397,96336,98289,96099,97765,95970,97675,95817,97308,95883,97104,96083,96898,96229,96722,96690,96505,96995,96415,97227,96375,97887,96235,97881,96416,98288,96575,98695,96719,98579,96918,98877,97058,98690,97328,98592,97585,98493,97766,98329,98287,98180,98638,98031,98898,97942,99417,97826,99295,97833,99660,97752,99849,97779,99505,97778,99696,97768,99346,97832,99065,97878,98796,97876,98428,98147,98135,98337,97810,98422,97551,98905,97330,98810,97389,99233,97343,99475,97522,99354,97593,99672,97803,99500,98017,99401,98232,99261,98420,99087,98840,98943,99154,98826,99453,98666,99927,98564,99893,98605,100521,98594,100637,98725,100567,98900,100922,99037,100843,99265,100692,99404,100559,99572,100475,100052,100254,100233,100026,100525,99913,101022,99722,100953,99719,101611,99621,101547,99802,101632,99809,101978,99988,101748,100122,101646,100256,101477,100426,101307,100830,101095,101023,100880,101284,100662,101711,100478,101693,100447,102310,100386,102239,100511,102305,100630,102696,100730,102484,100852,102406,100964,102277,101109,102078,101567,101919,101774,101763,102084,101563,102553,101466,102600,101431,103206,101428,103357,101734,103667,101998,104217,102308,104146,102637,104348,102868,104294,103176,104265,103577,104187,103844,104003,104185,103656,104288,102972,103701,102287,103547,101335,102685,100611,102029,99793,101538,99107,100528,98558,99929,98010,99150,97664,98519,97465,97852,97234,97437,97355,96928,97567,96608,97511,96543,98135,96398,97981,96535,98374,96664,98772,96908,98670,97112,98972,97266,98808,97619,98730,97943,98656,98140,98509,98531,98333,98885,98110,99025,98030,99637,97928,99570,98170,99997,98228,100337,98496,100202,98569,100506,98679,100266,98923,100081,98992,99803,99067,99487,99399,99147,99620,98896,99588,98588,100093,98322,99812,98304,100124,98275,100309,98318,100046,98463,100360,98433,100104,98702,99917,98835,99717,98991,99554,99400,99347,99746,99160,99938,99156,100549,98964,100552,99097,101060,99205,101358,99392,101207,99630,101649,99866,101485,100063,101402,100250,101239,100548,101207,100928,101032,101242,100824,101487,100697,102087,100581,102051,100694,102521,100669,102693,100797,102663,100934,102945,101122,102788,101352,102720,101441,102563,101650,102383,102049,102199,102298,102013,102532,101821,103013,101563,102865,101594,103490,101578,103464,101710,103452,101762,103894,101933,103713,102164,103586,102278,103477,102499,103302,102883,103155,103135,102963,103351,102683,103793,102503,103756,102505,104286,102402,104318};
uint32_t ir_example[]={99513,98160,99413,98419,99319,98729,99145,99050,98949,99419,98798,99851,98679,99846,98657,100433,98597,100453,98713,100550,98880,100921,98942,100758,99148,100637,99243,100496,99426,100316,99677,100090,99871,99833,100155,99657,100544,99416,100533,99350,101127,99266,100986,99359,101151,99370,101493,99586,101282,99597,101251,99713,101027,99896,100926,100109,100625,100345,100369,100625,100180,100986,99983,101152,99930,101751,99809,101581,99950,101877,100112,102210,100251,102006,100391,102068,100506,101956,100783,101872,101092,101692,101296,101532,101733,101311,102054,101081,101967,100723,102263,100171,101478,99530,101051,98881,100564,98080,99478,97452,98752,96709,97796,96168,97009,95842,96177,95534,95551,95512,95055,95623,94635,95492,94373,96057,94212,95856,94325,96206,94439,96594,94606,96428,94889,96724,95093,96645,95436,96622,95818,96520,96042,96387,96551,96312,96959,96200,97075,96116,97747,96027,97625,96166,98102,96258,98464,96444,98339,96751,98615,96864,98429,97113,98280,97281,98005,97386,97811,97731,97436,97948,97145,97891,96849,98402,96607,98112,96544,98337,96419,98565,96500,98246,96486,98393,96524,98100,96726,97962,96902,97688,97033,97499,97468,97311,97709,97142,97975,97062,98518,96929,98493,97060,98982,97142,99388,97406,99269,97602,99597,97792,99457,98096,99419,98376,99307,98614,99245,99053,99051,99352,98867,99665,98764,100215,98688,100144,98743,100627,98752,100923,99032,100799,99094,101111,99244,100868,99403,100797,99621,100589,99763,100377,100100,100140,100269,99873,100563,99674,101021,99524,100969,99551,101462,99564,101645,99692,101446,99770,101803,99901,101652,100125,101504,100279,101331,100457,101110,100778,100915,101007,100671,101289,100594,101818,100354,101721,100377,102270,100321,102378,100537,102362,100684,102799,100805,102585,101090,102610,101267,102405,101459,102259,101910,102105,102156,101966,102442,101795,102953,101616,102905,101644,103542,101586,103483,101618,103314,101416,103288,101016,102513,100613,101743,99933,100761,99438,99818,98908,98895,98425,97997,98168,97200,98008,96533,97569,96158,97837,95820,97544,95761,97496,95758,97826,95863,97578,96039,97544,96209,97493,96416,97421,96883,97340,97182,97235,97562,97114,98095,96945,98143,96973,98853,96974,98857,97165,98978,97281,99411,97496,99321,97713,99313,97941,99350,98204,99231,98616,99012,98810,98849,99134,98638,99428,98363,99388,98216,99901,98003,99655,97962,99784,97948,99986,97911,99593,97960,99546,97939,99346,98064,99033,98266,98767,98423,98492,98790,98286,99049,98060,99135,98070,99760,97914,99640,98075,99966,98171,100331,98381,100160,98601,100328,98727,100235,99008,100150,99380,100052,99587,99866,99999,99681,100388,99521,100534,99535,101232,99437,101096,99553,101549,99678,101880,99849,101663,99997,101840,100117,101669,100358,101584,100661,101355,100847,101152,101279,100994,101606,100701,101727,100661,102257,100528,102111,100565,102442,100591,102682,100713,102452,100867,102660,100910,102439,101096,102297,101381,102126,101522,101913,101866,101702,102110,101474,102269,101232,102835,101144,102648,101153,103101,101198,103388,101404,103117,101489,103464,101591,103194,101805,103113,102042,102864,102200,102734,102590,102568,102887,102306,103113,102215,103662,102059,103543,102114,104015,102120,104256,102225,104045,102277,104156,102136,103574,101862,102947,101460,102046,100931,101066,100578,100157,100099,99211,99599,98448,99493,97657,98822,97202,98869,96803,98729,96627,98274,96483,98387,96413,98019,96627,97867,96705,97693,96918,97569,97361,97458,97688,97321,97990,97306,98588,97221,98684,97381,99330,97427,99492,97609,99450,97792,99808,97969,99740,98258,99660,98447,99583,98721,99526,99143,99402,99453,99175,99728,99006,100126,98758,100009,98681,100577,98530,100456,98552,100286,98493,100535,98475,100160,98571,99984,98623,99718,98645,99416,98885,99089,99001,98805,99246,98542,99592,98317,99538,98247,100102,98237,100083,98335,100150,98422,100539,98591,100384,98835,100372,98999,100288,99222,100149,99602,100040,99969,99851,100286,99750,100700,99585,100777,99593,101437,99550,101359,99661,101543,99773,101933,99951,101728,100164,101782,100267,101628,100494,101441,100780,101297,100990,101068,101362,100900,101679,100687,101784,100632,102358,100470,102224,100521,102395,100604,102649,100688,102500,100863,102489,100962,102295,101082,102160,101407,101901,101577,101678,101890,101420,102240,101237,102216,101126,102821,101008,102727,101077,102969,101091,103267,101272,103033,101397,103130,101441,102903,101683,102784,101920,102619,102118,102339,102494,102205,102859,101992,102968,101852,103588,101727,103469,101826,103746,101949,104055,102012,103823,102202,103910,101995,103385,101834,102735,101494,101924,100942,100911,100592,99908,100058,98927,99451,98085,99407,97319,98581,96835,98397,96336,98289,96099,97765,95970,97675,95817,97308,95883,97104,96083,96898,96229,96722,96690,96505,96995,96415,97227,96375,97887,96235,97881,96416,98288,96575,98695,96719,98579,96918,98877,97058,98690,97328,98592,97585,98493,97766,98329,98287,98180,98638,98031,98898,97942,99417,97826,99295,97833,99660,97752,99849,97779,99505,97778,99696,97768,99346,97832,99065,97878,98796,97876,98428,98147,98135,98337,97810,98422,97551,98905,97330,98810,97389,99233,97343,99475,97522,99354,97593,99672,97803,99500,98017,99401,98232,99261,98420,99087,98840,98943,99154,98826,99453,98666,99927,98564,99893,98605,100521,98594,100637,98725,100567,98900,100922,99037,100843,99265,100692,99404,100559,99572,100475,100052,100254,100233,100026,100525,99913,101022,99722,100953,99719,101611,99621,101547,99802,101632,99809,101978,99988,101748,100122,101646,100256,101477,100426,101307,100830,101095,101023,100880,101284,100662,101711,100478,101693,100447,102310,100386,102239,100511,102305,100630,102696,100730,102484,100852,102406,100964,102277,101109,102078,101567,101919,101774,101763,102084,101563,102553,101466,102600,101431,103206,101428,103357,101734,103667,101998,104217,102308,104146,102637,104348,102868,104294,103176,104265,103577,104187,103844,104003,104185,103656,104288,102972,103701,102287,103547,101335,102685,100611,102029,99793,101538,99107,100528,98558,99929,98010,99150,97664,98519,97465,97852,97234,97437,97355,96928,97567,96608,97511,96543,98135,96398,97981,96535,98374,96664,98772,96908,98670,97112,98972,97266,98808,97619,98730,97943,98656,98140,98509,98531,98333,98885,98110,99025,98030,99637,97928,99570,98170,99997,98228,100337,98496,100202,98569,100506,98679,100266,98923,100081,98992,99803,99067,99487,99399,99147,99620,98896,99588,98588,100093,98322,99812,98304,100124,98275,100309,98318,100046,98463,100360,98433,100104,98702,99917,98835,99717,98991,99554,99400,99347,99746,99160,99938,99156,100549,98964,100552,99097,101060,99205,101358,99392,101207,99630,101649,99866,101485,100063,101402,100250,101239,100548,101207,100928,101032,101242,100824,101487,100697,102087,100581,102051,100694,102521,100669,102693,100797,102663,100934,102945,101122,102788,101352,102720,101441,102563,101650,102383,102049,102199,102298,102013,102532,101821,103013,101563,102865,101594,103490,101578,103464,101710,103452,101762,103894,101933,103713,102164,103586,102278,103477,102499,103302,102883,103155,103135,102963,103351,102683,103793,102503,103756,102505,104286,102402,104318};




void updateMenu(int n){
    
    GUI_Clear();
    
    GUI_SetPenSize(2);
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    
    
    //Rectangle
    GUI_DrawRect(1,1,263,175);
    

    GUI_SetPenSize(2);
    GUI_DrawLine(95,30,170,30);
    
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    
    //Write MENU
    GUI_SetFont(GUI_FONT_24B_1);
    GUI_SetTextAlign(GUI_TA_CENTER);
    GUI_DispStringAt("MENU",135 ,5);
    
    
    //Write options
    if(n == 1){
        GUI_SetFont(GUI_FONT_16B_1);
        GUI_DispStringAt("Show oxygenated signal",40 ,40);
        GUI_SetFont(GUI_FONT_16_1);
        GUI_DispStringAt("Show non-oxygenated signal",40 ,75);
        GUI_DispStringAt("Change intensity of LED",40 ,110);
        GUI_DispStringAt("Change the heart rate interval",40 ,145);
    }
    if(n == 2){
        GUI_SetFont(GUI_FONT_16B_1);
        GUI_DispStringAt("Show non-oxygenated signal",40 ,75);
        GUI_SetFont(GUI_FONT_16_1);
        GUI_DispStringAt("Show oxygenated signal",40 ,40);
        GUI_DispStringAt("Change intensity of LED",40 ,110);
        GUI_DispStringAt("Change the heart rate interval",40 ,145);
    }
    if(n == 3){
        GUI_SetFont(GUI_FONT_16B_1);
        GUI_DispStringAt("Change intensity of LED",40 ,110); 
        GUI_SetFont(GUI_FONT_16_1);
        GUI_DispStringAt("Show oxygenated signal",40 ,40);
        GUI_DispStringAt("Show non-oxygenated signal",40 ,75);
        GUI_DispStringAt("Change the heart rate interval",40 ,145);
    }
    if(n == 4){
        GUI_SetFont(GUI_FONT_16_1);
        GUI_DispStringAt("Show oxygenated signal",40 ,40);
        GUI_DispStringAt("Show non-oxygenated signal",40 ,75);
        GUI_DispStringAt("Change intensity of LED",40 ,110);
        GUI_SetFont(GUI_FONT_16B_1);
        GUI_DispStringAt("Change the heart rate interval",40 ,145);
    }
    
    
    UpdateDisplay(CY_EINK_FULL_2STAGE, true);
    
}




void updateLED(){
   
    GUI_Clear();
    
    GUI_SetPenSize(2);
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    
    //RectangleS
    GUI_DrawRect(1,1,263,175);
    GUI_DrawRect(95,70,160,120);

    
    GUI_SetFont(GUI_FONT_16_1);
    GUI_SetTextAlign(GUI_TA_CENTER);;
    
   
    GUI_SetFont(GUI_FONT_32B_1);
    char valeur_LED[4] = "";
    sprintf(valeur_LED,"%d",(int)LED);

    GUI_DispStringAt(valeur_LED, 130, 80);
    
    GUI_SetFont(GUI_FONT_16B_1);
    GUI_DispStringAt("CHANGE LED VALUE", 60 ,15);
    
    UpdateDisplay(CY_EINK_FULL_2STAGE, true);
}

void updateHR(){
   
   
    GUI_Clear();
    
    GUI_SetPenSize(2);
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    
    //RectangleS
    GUI_DrawRect(1,1,263,175);
    GUI_DrawRect(30,70,90,120);
    GUI_DrawRect(150,70,225,120);

    
    GUI_SetFont(GUI_FONT_16_1);
    GUI_SetTextAlign(GUI_TA_CENTER);;
    
   
    GUI_SetFont(GUI_FONT_32B_1);
    char frequence_max[4] = "";
    char frequence_min[4] = "";
    sprintf(frequence_max,"%d",(int)hrmax);
    sprintf(frequence_min,"%d",(int)hrmin);

    GUI_DispStringAt(frequence_min, 60, 80);
    GUI_DispStringAt(frequence_max, 165, 80);
    
    GUI_SetFont(GUI_FONT_16B_1);
    GUI_DispStringAt("Min Heart Rate",10 ,130);
    GUI_DispStringAt("Max Heart Rate", 135 ,130);
    GUI_DispStringAt("CHANGE HEART RATE INTERVAL",30 ,15);
    
    UpdateDisplay(CY_EINK_FULL_2STAGE, true);
    
}
void updateSignal(float32 *vecteur, uint32_t fc, uint32_t spo2, float32 AC, float32 DC){
    
    GUI_Clear();
    
    GUI_SetPenSize(2);
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);

    int j=0;
   
    int tableauX[125];
    
    if (!LED_flag)
    {
    for(int i=0; i<125;i++){
        tableauX[i]=2*i;
    }
    
    for(int i=0; i<124;i++){
        int Y0 = (int)(150-((vecteur[j]-(DC-AC-5000))*150)/(2*AC + 5000));
        int Y1 = (int)(150-((vecteur[j+4]-(DC-AC-5000))*150)/(2*AC + 5000));
        int X0 = tableauX[i]+7;
        int X1 = tableauX[i+1]+7;
        GUI_DrawLine(X0, Y0, X1, Y1);
        j=j+2;
    }
    }
    else
    {
        GUI_DrawLine(75, 75, 200, 75);
        GUI_SetFont(GUI_FONT_16B_1);
        GUI_DispStringAt("Movement detected", 75 ,55);     
    }

    
    GUI_DrawRect(7,7,257,120);
    GUI_SetFont(GUI_FONT_16B_1);
    GUI_SetTextAlign(GUI_TA_CENTER);
    char frequence[4] = "";
    char taux_oxy[5] = "";
    sprintf(frequence,"%d",(int)fc);
    sprintf(taux_oxy,"%d",(int)spo2);
    GUI_DispStringAt("SPO2", 190 ,130);
    GUI_DispStringAt("Heart Rate",40 ,130);
    GUI_SetFont(GUI_FONT_16_1);
    GUI_DispStringAt(frequence, 65, 155);
    
    if(fc>hrmax || fc<hrmin)
    {
        GUI_SetFont(GUI_FONT_32B_1);        
        GUI_DispStringAt("!!!", 25, 145);
        GUI_DispStringAt("!!!", 90, 145);
    }
    


    
    
    GUI_SetFont(GUI_FONT_16_1);
    GUI_DispStringAt(taux_oxy, 180, 155);
    GUI_DispStringAt("%",200 ,155);
    
    UpdateDisplay(CY_EINK_FULL_2STAGE, true);
}

void vINTERFACE_task(void* pvParameters){
    
    NVIC_DisableIRQ(PPG_RDY_isr_cfg.intrSrc);
    (void)pvParameters;
    //GUI_Init();
    //Cy_EINK_Start(20);
    //Cy_EINK_Power(1);
    int8_t selection = 1;
    //updateMenu(selection);
   
    
    for(;;){
        
        // MENU
        
        if(currentpage == PAGE_MENU){
            //vTaskDelay(pdMS_TO_TICKS(50));
       
                if(currenttouch == BUTTON_R){
                    
                    selection++;
                    if(selection == 5){
                        selection = 1;
                    }
                }
    
                if(currenttouch==BUTTON_L){
                    
                    selection--;
                    if(selection == 0){
                        selection = 4;
                    }
                }
            
            // Affichage menu dont selection est en gras
            updateMenu(selection);            
          
            if(currenttouch == BUTTON_MENU){
                
                currentpage = selection;          
            }            

            currenttouch = NO_TOUCH;
        }
        
        
        
        // OPTION CHANGE INTENSITY OF LED
        
        if(currentpage == PAGE_LED){
            //vTaskDelay(pdMS_TO_TICKS(50));
     
                if(currenttouch == BUTTON_R){
                    
                    LED=LED+5;
                    //WRITE_REGISTER_max(0x0C, LED)
                    //WRITE_REGISTER_max(0x0D, LED)
                }
    
                if(currenttouch==BUTTON_L){
                    
                    LED=LED-5;
                    //WRITE_REGISTER_max(0x0C, LED)
                    //WRITE_REGISTER_max(0x0D, LED)
                } 
            
                updateLED();
            
        
            if(currenttouch == BUTTON_MENU){
                
                currentpage = PAGE_MENU;                            
            }
        
        currenttouch = NO_TOUCH;
 
        }
        
        
        // OPTION CHANGE HEART RATE INTERVAL
        
        if(currentpage == PAGE_HR){
            //vTaskDelay(pdMS_TO_TICKS(50));
     
            if(currenttouch == BUTTON_R){
                
                if(maxormin == true){
                    hrmin=hrmin+5;
                }              
                if(maxormin == false){
                    hrmax=hrmax+5;
                }
            }
    
            if(currenttouch==BUTTON_L){  
                
                if(maxormin == true){
                    hrmin=hrmin-5;
                }
                if(maxormin == false){
                    hrmax=hrmax-5;
                }
            } 
           
            updateHR();
            
            if(currenttouch == BUTTON_MENU){ 
               
                currentpage = PAGE_MENU;                            
            }
                        
            currenttouch = NO_TOUCH;
        }
        
        
        // OPTION RED SIGNAL
        
        if(currentpage == PAGE_SIGNAL_R){
            //vTaskDelay(pdMS_TO_TICKS(50));
            //signal déclaré au début de ce fichier c pour tester
            updateSignal(&red_data[0], BPM, S, AC_R, DC_R);
            
            if(currenttouch == BUTTON_MENU){
                currenttouch = NO_TOUCH;
                currentpage = PAGE_MENU;                            
            }
        }
        
        
        // OPTION IR SIGNAL
        
        if(currentpage == PAGE_SIGNAL_IR){
            //vTaskDelay(pdMS_TO_TICKS(50));
            updateSignal(&ir_data[0], BPM, S, AC_IF, DC_IF);
            
            if(currenttouch == BUTTON_MENU){
                currenttouch = NO_TOUCH;
                currentpage = PAGE_MENU;                            
            }
            
        }
        NVIC_EnableIRQ(PPG_RDY_isr_cfg.intrSrc);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }     
}

/* [] END OF FILE */
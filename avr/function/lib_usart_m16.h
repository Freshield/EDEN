/*
 * lib_usart_m16.h
 *
 * Created: 2013/04/07 11:41:48
 * Edited：	2015/10/05
 *  Author: Narcissus
 */ 

//#include <stdio.h>//如果使用sizeof的话需要加入这个头文件


#ifndef LIB_USART_M16_H_
#define LIB_USART_M16_H_

//**************引脚配置
//*****RXD为PD0 TXD为PD1 注意主机从机的RXD TXD需要反接 也就是说主机的TXD接从机的RXD

//////////////////////////////////////////////////
////M16 USART
//////////////////////////////////////////////////
void M16_USART_SEND_INIT()
{
	UBRRL = 95;//********7.3728M 9600 BAUD U2X
	
	UCSRA |= (1 << U2X);//*********倍速模式
	
	UCSRB |= (1 << TXCIE)|(1 << UDRIE)|(1 << TXEN);//********发送中断 寄存器空中断 发送使能
	
	UCSRC |= (1 << URSEL)|(1 << UCSZ1)|(1 << UCSZ0);//*********异步操作 无校验 一位停止位 8位数据 
	
	
	
}

void M16_USART_READ_INIT()
{
	UBRRL = 95;//***********7.3728 9600 BAUD U2X
	
	UCSRA |= (1 << U2X);//*************倍速模式
	
	UCSRB |= (1 << RXCIE)|(1 << RXEN);//*********接收中断 接收使能
	
	UCSRC |= (1 << URSEL)|(1 << UCSZ1)|(1 << UCSZ0);//*********异步操作 无校验 一位停止位 8位数据
	
	
}

void M16_USART_SEND_ALONE(char data)
{
	/* 等待发送缓冲器为空 */
	while ( !( UCSRA & (1<<UDRE)) )
	;
	/* 将数据放入缓冲器，发送数据*/
	UDR = data;
}
uchar M16_USART_READ_ALONE()
{
	/* 等待发送缓冲器为空 */
	while ( !( UCSRA & (1<<RXC)) )
	;
	/* 将数据放入缓冲器，发送数据*/
	return UDR;
}
//参数:字符串首地址,字符串长度(使用'\0'来标识),光标归位标志位,换行标志位
//************本程序是必须把一个文字发完才能结束 
//*********有问题的部分：中断的添加可能会导致程序不通
void M16_USART_SEND_STRING(char data_string[],int r,int n)
{
	for (int i = 0;data_string[i] != '\0';i++)
	{
		M16_USART_SEND_ALONE(data_string[i]);
	}
	
	if (r == 0)
	{
		asm volatile ("nop");
	}
	else
	{
		M16_USART_SEND_ALONE('\r');//光标归位
	}
	
	if (n == 0)
	{
		asm volatile ("nop");
	}
	else
	{
		M16_USART_SEND_ALONE('\n');//换行
	}
}


//*********************接收参考程序*************************************
//********************注意小心显示位置x位置应该是0不是count 否则会边走边显示
/*
static char read0[17];
static char read1[17];
char count = 0;
char line = 0;
char button = 0;
ISR(USART_TXC_vect)
{delay_reduce(1);}
ISR(USART_UDRE_vect)
{delay_reduce(1);}
ISR(USART_RXC_vect)
{if (line == 0)
	{read0[count] = UDR;
	read0[count+1] = '\0';\
	button = 1;}
	else
	{read1[count] = UDR;
		read1[count+1] = '\0';
		button = 1;}
	count ++;
	if (count >=16)
	{line ++;
		count = 0;
		if (line == 1)
		{for (char i = 0;i < 16;i ++)
			{read1[i] = 0x20;}}
		else if (line >= 2)
		{line = 0;
			for (char i = 0;i < 16;i ++)
			{read0[i] = 0x20;}}
	}
}
int main(void)
{M16_USART_READ_INIT();
M16_USART_SEND_INIT();
	LCD_init();
	LCD_SHOW_STRING(0,0,"WAITING THE DATA") ;
	sei();
	while(1)
	{switch (button)
		{case 0: delay_reduce(10);
			break;
		case 1:LCD_CLEAR();
			//LCD_SHOW_STRING(0,0,read0);
			LCD_SHOW_STRING(0,0,"NO WAY");
			LCD_SHOW_STRING(0,1,read1);
			if (line == 0)
			{//M16_USART_SEND_STRING(read0,1,1);
				M16_USART_SEND_STRING("NO WAY",1,1);}
			else
			{M16_USART_SEND_STRING(read1,1,1);}
			button = 0;
			break;
			default: button = 0;
			break;}
	}
}	*/
/*
                                                                                                                                                      
                                                                                                                                                      char test001[] = "                                                                  OB                                                                            "  ;
                                                                                                                                                      char test002[] = "                                                                  BBP                                                                           "   ;
                                                                                                                                                      char test003[] = "                                                                  BNBY                                                                          "    ;
                                                                                                                                                      char test004[] = "                                                                 LMqNBr                                                                         "     ;
                                                                                                                                                      char test005[] = "                                                                 OGkPEBi                                                                        "      ;
                                                                                                                                                      char test006[] = "                                                                iBPXSPGB                                                                        "      ;
                                                                                                                                                      char test007[] = "                                                                VMPSkSqON                                                                       "     ;
                                                                                                                                                      char test008[] = "                                                                OGSkSkSqMX                                                                      "     ;
                                                                                                                                                      char test009[] = "                                                                BqXSXSXSNBr                                                                     "     ;
                                                                                                                                                      char test010[] = "                                                                BPFXSkFkkZB                                                                     "     ;
                                                                                                                                                      char test011[] = "                                                               iBkXFkFkFkkMP                                                                    "     ;
                                                                                                                                                      char test012[] = "         Nui                                                   YMPSkFXSXSXPBr                                                                   "     ;
                                                                                                                                                      char test013[] = "         iNNkLi                                                jMkkSkFXFkFXNB                                                                   "     ;
                                                                                                                                                      char test014[] = "          YoJoSNqFri                                           UOPFXFXFkFkSPMq                                                                  "     ;
                                                                                                                                                      char test015[] = "           kuvvvYuXPqIuri                                      UMXkFkFXFkFXkNBi                                                                 "     ;
                                                                                                                                                      char test016[] = "           iNJvLvvvvLuoPPqVjii                                 jMqSkFSFSFkSXkOO                                                                 "     ;
                                                                                                                                                      char test017[] = "            iZovLvvvvvvvLLuUkSSuLri                            iBqXFkXPVkSkSXXBv                                                                "     ;
                                                                                                                                                      char test018[] = "              kPLvvvvvvvvvvLvLLuUVVPXXjLii                      SMkkVEEFFkSkFXNB                                                                "     ;
                                                                                                                                                      char test019[] = "               rBNYvLvvvLvvvvvvvLvLvYYoFqNGGEjri                iMEkSSGFkFXSkSXMX                                                               "     ;
                                                                                                                                                      char test020[] = "                 IOPLLvJLJLLvLvLvLvLvvvvvvvLJFkNZOGk             oMNFPNSFkSXFkkqBi                                                              "     ;
                                                                                                                                                      char test021[] = "                   vXSuLJLYLYvYLYvLvLvLvLvvvvvvvLvoOBi            IMPXNVSFkSXFXkBo                                                              "     ;
                                                                                                                                                      char test022[] = "                     rVkoUjjYYLLLLvYvLvLvLLLvLvvvLvLuVi            qONNFSXSkFXFPGG                                                              "     ;
                                                                                                                                                      char test023[] = "                       ivUSVVuuJjYJLLLLvLvYvLvLvvvYLYYou            XBqFXFXSkSkSOG                                                              "     ;
                                                                                                                                                      char test024[] = "                           iLkkFUVUIJjLJLYLLvvvvvvvYLjJoVi          vBkSFkFkFkSqBo                                                              "     ;
                                                                                                                                                      char test025[] = "                              iivvJuoUojuYjJjYLvvvvvLLJYUSj        iBNkSkFkSXSNBB                                 ii                            "     ;
                                                                                                                                                      char test026[] = "                                   irjIkSNqXFSVULLvvvvvYLuVXi     iBESSkSXkqZBBU                                 rJuZ   ii                      "     ;
                                                                                                                                                      char test027[] = "                                          iiivLIZuJLLvvvYLJuNi    BGXSXSqZBBOu                                   i  Z  iBVB                     "     ;
                                                                                                                                                      char test028[] = "                                                ikjJLYvvvYvYJNi  GBMPENBMBJ                                      r iv   i v                     "     ;
                                                                                                                                                      char test029[] = "                                                  UXPUuLLvLvFBXJOMvXOEGPi                                        i ii  ii v                     "     ;
                                                                                                                                                      char test030[] = "                                                    ruSqSkjkOPrvrv i                                             j i   iiir                     "     ;
                                                                                                                                                      char test031[] = "                                                        ivuLr  roUPvi                                          iVSivoivv ir                     "     ;
                                                                                                                                                      char test032[] = "                                                            ivMBBOZNVSvYLuLYviiii                         iukPOXNJ riirv iS                     "     ;
                                                                                                                                                      char test033[] = "                                                          rrENvri    ii  iuri iiLoVvi                  iNBBN    VUivvLui rEirii                 "     ;
                                                                                                                                                      char test034[] = "                                                        vBj vi       i     iri     irLri              FBiiirrr iBuir  Lv vUiiiLuvi              "     ;
                                                                                                                                                      char test035[] = "                                                     rMBBv  v       iiv       ii       iii            B      uBiOi   oBriXSvIrvrjkFi            "     ;
                                                                                                                                                      char test036[] = "         our                                       rNNiiL  i        iiir        ii       iii         kr       MBrjiiiPM  OkLrvijoLvkFi          "     ;
                                                                                                                                                      char test037[] = "          uZi            vi                      iBNi  u   i        ri iv         i        iv        N    i   iIurvvFP  rBP i   rqkLPBB         "     ;
                                                                                                                                                      char test038[] = "          IJ ivISJ        riJ                   iML   vv            ii iMi         ii        Ui     iv   rOk    iYvvLPJjuLoMOLiirNOXuVB         "     ;
                                                                                                                                                      char test039[] = "         vi ii ikY                             iqi   iN             i  Lki           i        Ni    ri   vGI      iirLoi  irViIMXvriiXN         "     ;
                                                                                                                                                      char test040[] = "       ir  vjr Jo          Li                 vri    rL             i  Ui i           i        Ni   ii    ii           i  ivi  ujuVuFB          "     ;
                                                                                                                                                      char test041[] = "       iji    rLY          rV                i       v    i            Ui ii           i        P   iqi             i iOBi    ikEkViNu          "     ;
                                                                                                                                                      char test042[] = "         uv  iiivIu        ijiii            i        L   ii        i   V iiii           i       iv   ikJi             iIu  i  vIrriLG           "     ;
                                                                                                                                                      char test043[] = "         iG      rriuL     ii ii           i        ir   Lii           viiiir   ii      ir   i   L      iuSi  iii         i   EvrirG            "     ;
                                                                                                                                                      char test044[] = "          ri       iVEi                    i        ii   Uiiii        ir i  ivi  i       ii  i   ii        IkYYriiii     i   kJiiiqi            "     ;
                                                                                                                                                      char test045[] = "          iL jGirrrISF                    i     ii  ii  irr iiii   i  ii    iir           ii  i   L     iirMi iYuvrii       EPiiuEi             "     ;
                                                                                                                                                      char test046[] = "       qViiviir   Yvr        i  Uq       i      v   i   riL  i     ii i      iri i   rvi   Ui     r   iEOYqM     iiuVoujuFLGBJvvi               "     ;
                                                                                                                                                      char test047[] = "       io                    ku  vi     i  ii  ir   i   i L  J      i i      iir ii  iXiivJuVi    ii  iBi jr    iiLrrurirrqk                    "     ;
                                                                                                                                                      char test048[] = "                 ii                     i ir   ri   i  ii r  Yi      ii       iJiiU  iJ   r  i i   v   jjioi    iFiiirrJiiO                     "     ;
                                                                                                                                                      char test049[] = "            ikr iivo     ri      i      iiii   Ji   i  viiii rv  i   ii         i I   r   ii       r     iN      ku    LvUL                     "     ;
                                                                                                                                                      char test050[] = "            vPU vi iJUriiPi    vu      iri i   ui   i  viiiviiv  Oi  ii         iiri  i    Yi      i     io  i i iXv   iUO                      "     ;
                                                                                                                                                      char test051[] = "            vqi  iii  vLuUr   FIv      r   i   Lr   i  ii        vXi ii    ivNBBBBBBkii    iji     iv vVkBkiiiiiiiiiojvLPNiuU                   "     ;
                                                                                                                                                      char test052[] = "            ui irrrJ  ivr      ii     r    i   ir   i ii         i Giri YBBBBBBBGNPMuii     rvi     JBBBBBiiiiiiiiiiiirvZi iLo                  "     ;
                                                                                                                                                      char test053[] = "           ii   i v  uYiGY           i     i    ii    vujjGBBBBBGr  Vui    BqiirouuOjv      ijr     vGrrqkiirrrrriiiiirkM iiiM                  "     ;
                                                                                                                                                      char test054[] = "          ii   i  iii               i      i    ii   PBBBBMOEGqMFi   v      ivrvLriVii  i    iri     NvvrUqurvrririiiirBM  iji                  "     ;
                                                                                                                                                      char test055[] = "             iii                           i     i   vB  ZiirLuJv           Luiiiiivi   i     iri    EuvvrjSFFIujYjJujoFoGi                     "     ;
                                                                                                                                                      char test056[] = "                                               i i   vJ  iriiiiii            riiii ri  i i     ir    vBSujvvvYYoVkVIuuvriMB                     "     ;
                                                                                                                                                      char test057[] = "                                               i i   iii iNiiiii                   ri  i ii    iir    UiUoPqXouYJLYYJjIVOBr                     "     ;
                                                                                                                                                      char test058[] = "                                               i i         irvi                    vi ii  i     iri   v    iivYUoSFVujYuv                       "     ;
                                                                                                                                                      char test059[] = "                                               i ii   ii                           Ji i  iii     iv    i                                        "     ;
                                                                                                                                                      char test060[] = "                       uUPM                    i ii  iiir                        iGN  rS i ii     ii   r                                        "     ;
                                                                                                                                                      char test061[] = "                       Nj Li                      v iii oGJi                  ivJiJu  UBi i i     iiv   Y                                       "     ;
                                                                                                                                                      char test062[] = "                        j  v                      ii ii rviuSIrrviiii    IFNPBG    r  kiUi iii     iiv  ii                                      "     ;
                                                                                                                                                      char test063[] = "                        vi ir iUur                 i ii Yviiiiivq      iBBiiv XBi     Xirqi  ir      iJ  v                                      "     ;
                                                                                                                                                      char test064[] = "                         o  L kr o                 vi   rvii i ji     vBBi r  FMVIF  iuiiYk    i      iV  i                                     "     ;
                                                                                                                                                      char test065[] = "                         iv iiri Li                iu   vi  iiir     MMri i iNU ikB  i  iiIU           iFiii                                    "     ;
                                                                                                                                                      char test066[] = "                          jiirLi iv                 E   Yi iiiii    LXivi  jMv iLii  i    iNv            viY                                    "     ;
                                                                                                                                                      char test067[] = "                          ivi OY  V                 v   kiiii i   ir vLivvONiiui  j  L     iki            iSo                                   "     ;
                                                                                                                                                      char test068[] = "                           ii JZ  o                 J   Li       Nr vuV jOuviri  iY  S       vi             SB                                  "     ;
                                                                                                                                                      char test069[] = "                            i iUi uL                F   r      iBSriNirvuoqNLir  ir  ri       ri             iBv                                "     ;
                                                                                                                                                      char test070[] = "                        ijrFqiiur iBii              v  ir    uOSrjFMruZMkGML  iiiii  i i       ii    i   iY    YPr                              "     ;
                                                                                                                                                      char test071[] = "                       Lv  qMkroL iOjGMGLri         Y  ir   iMBvrUBB iBNGOJ  iivjr  i  i        ii    i   ivr    rui                            "     ;
                                                                                                                                                      char test072[] = "                     NY  iYviXriUiir  i   voi       u  ii  iviXOUoNi  NMMv  i r iM  i   L        ii    i    vqi    iri                          "     ;
                                                                                                                                                      char test073[] = "                    Zv  vJvrkMGrOiiLi  iuF  ivr     I  ri io   vGML   FMMv  iri  o     iqVj       ivi   i    rS ii    i                         "     ;
                                                                                                                                                      char test074[] = "                   LM ijJLYVLJMGNi rUri  ii   iJv  uJ  i vi     jB   iBZMF   i   r  IXoojFBi        ri  ii    rL  iii    i                      "     ;
                                                                                                                                                      char test075[] = "                   iBEuLJuJiiv iLJ iGviv   ii    UMMv  BL       ki   SBOZ        i  BEuoVvXv         ri   i    iL   irr                         "     ;
                                                                                                                                                      char test076[] = "                  ikvvSXLii rv   YiiMOiiYi  irrv   qi  MUrirFYiuB   jZMGX        i  I  vvruBi          ii  i    iY     iri    ii                "     ;
                                                                                                                                                      char test077[] = "                 vN  iuvi iiJi   ViiZBYiiiijOUMBN  ii  iiiii irBL  VNLOVM  iii   i  SvYVXqOB            vi  ii   ij       iii   ii              "     ;
                                                                                                                                                      char test078[] = "                 L  rviiiiiiJX  rBkirL rriiVi      Li  i iivL  B  GGrIESOiiriv   r   kMvvi ii            rvi ii   iu        iri    i            "     ;
                                                                                                                                                      char test079[] = "                iYrkriiiNkiiivJvuBu    iMLFi    iGjFi  YFkuJoIXv UOvrVPVNU       i i  vi    L             iYr  i   iu          iri   i          "     ;
                                                                                                                                                      char test080[] = "                rBSr iiiivuZr   iFi    GBjiii  iBOGV  iFj  i iN  GLvvVFXFZ      ii i   L     v              iJi ii   Ji          iii  ii        "     ;
                                                                                                                                                      char test081[] = "                 MviSv  vXNi iLiivi iuBBLiiiiiiuBvjj  Xrriiiiiv YrLvYUkSVNi     ri      J    ii       iv      vLi i  JZGL           ii  v       "     ;
                                                                                                                                                      char test082[] = "                 YZiLiiPNL  vNZi iXPMMoiiiiiiirui rv  Sv JLi viivivruFXXoqo     i       ir    i      IrEY      ivr  iV GN             ii Li     "     ;
                                                                                                                                                      char test083[] = "                  uJ LGUi iSqviir rEFi iiiiiirYi iui  Ov ijEBj rvrYurvXFIkGiiri    i     ii    r     I  i        iJiLr Liv             ir o     "     ;
                                                                                                                                                      char test084[] = "                   YGXr iUqUi iPNrLjiiiiiiiivLriiiYL  Bv i iBYiYivFivjvvuEviivi    i      i     v    V ii          iZ ii  r              vii    "     ;
                                                                                                                                                      char test085[] = "                   iNrikPv  iiiivriiiiiiivjLriiriBU iOviiiiFEPJJui  SVLYv    iii ii       r    vi   F ii           L Iv   ii            iui     "    ;
                                                                                                                                                      char test086[] = "                      jOIi LFr rviiiiiiiiujvrrrviPFi iMr iiLi iXqi   virEViiirVOv ii        L    I   q ii          ri IIv   ii            Ji    "     ;
                                                                                                                                                      char test087[] = "                        vYvuoiuLiiiiiiiLoviivrrivrJ  rBOXFIIuvkBX       ii    OBi r         rv    J  u ir          uiir iYv   i                 "     ;
                                                                                                                                                      char test088[] = "                          vVLJNi iiiivYriirYvivJiUNi jBi      PiIv           qBB  r          Li   iv u iv          LiJi   iLi  r                "     ;
                                                                                                                                                      char test089[] = "                            iuBPirririiiirvrriiiPBkv uI      ZU iBi         qBiri L           Li   iJLiij         riiV      iViir               "     ;
                                                                                                                                                      char test090[] = "                               NEBuiirriivri iLMBjuu Jv     vBviiNEi       BBi ji vi           vi   XO iu         viLu       ivjuX              "     ;
                                                                                                                                                      char test091[] = "                                 iFXBGUIjiirqEJU  SJ vv     ZUUoVvvULiriivOZvivoi vBr       i   iv   OiiN        rviki         iGON             "     ;
                                                                                                                                                      char test092[] = "                                     ivNokkEM  F  jviuv   iPFvrvuLvLLNXFNEuLjFIGX iLMo      MMi   r  E iLi       BZFN     iiiri J Bi            "     ;
                                                                                                                                                      char test093[] = "                                           ri rL  v vuL   EUurvojrvrLGJiuLiijvrYNiiZSBZ     vMori iukq rBi      vBOOBjrVIirrruSiN  M            "     ;
                                                                                                                                                      char test094[] = "                                           U  o   i iSi  BBMvrLIrvvrUNiiLviiLiiUrvIBivOMi    vNBGiiJLBPUSr     rS    GovLi  iiiBBi Y            "     ;
                                                                                                                                                      char test095[] = "                                          iF  P   i  v   iqGXFBkuuYrNPriviirYiiSLioLSBBuOq      GB  VGriiZr  iJBB    iOLvVUJqLirBv              "     ;
                                                                                                                                                      char test096[] = "                                          vSiiG            SrvvriuUGGSUUJPvjujjZkSF   qBOBBv     iBiir   iBMLii LOi  iUFUqBu     iv             "     ;
                                                                                                                                                      char test097[] = "                                          vir O            v       B     XqiiiiiiLNI    Guiuki    BNVIi   PGUr   iOj VVvuPBi      vi            "     ;
                                                                                                                                                      char test098[] = "                                          L iru           ii      iu     i   iii iiBBr    ii jMEIvii  Ju  iN jJiiiiEIEPUUvBY       u            "     ;
                                                                                                                                                      char test099[] = "                                         u  YIi          U       Ni     i      iiiZBBMv   vkFBY    iiikEqOOEiovvLJLFvriiii ivIi   ii            "    ;
                                                                                                                                                      char test100[] = "                                          ii  rU          v      iE      i         vBBBBMoiuMEjjLvirJuJLvriivPqvvLvriirii   iOBq    i           "     ;
                                                                                                                                                      char test101[] = "                                               iYi        i      Ur      ii      i  BOuEoLLoGvrvJYuuME        ujviiii     i  iNui   ri          "     ;
                                                                                                                                                      char test102[] = "                                                         i       O       ii      o      iUXVMkrrrvvvvki  i ivj         i i i        ir          "     ;
                                                                                                                                                      char test103[] = "                                                        r      vX       i       S           GGJVPSvrrSi   iBBk   i i i    ii      iNr           "    ;
                                                                                                                                                      char test104[] = "                                                        iNoIoUiiOi               V           vBNkPIviivU    vovi iii    iivr    iLYLi           "     ;
                                                                                                                                                      char test105[] = "                                                        vFuYuYkBk         BNNNNSNO            OMiiirvvvVjii     i i  irii i ivFV                "     ;
                                                                                                                                                      char test106[] = "                                                        PNFIYLjBi        iBULLLoEB             BIJFNPPUSMNi            iivSOGGGv                "     ;
                                                                                                                                                      char test107[] = "                                                       ii  ivFMG         iEvYLJjNS              BYririiiii        iiJIqqESuvvriSvZMi            "     ;
                                                                                                                                                      char test108[] = "                                                       Y      Oi         iOUjuuFGX              FO   i i r  iirLuFVSVIjYvviii  FBGBBv           "     ;
                                                                                                                                                      char test109[] = "                                                      iOUUUr  J          iv      r               SPjJjUkBOBVjviiirirvvvriii i  iu iqG           "     ;
                                                                                                                                                      char test110[] = "                                                      NGJUjSNBi          i       i                 rivri  vv iiiuILrii       i  Ji iG           "     ;
                                                                                                                                                      char test111[] = "                                                      NvuuXIPB            SvujuSEi                         ZrrSZBVvi          i JI iG           "     ;
                                                                                                                                                      char test112[] = "                                                     Y     vEr           iNuYLLSN                          LBvSUi iLv          iiNiJr           "     ;
                                                                                                                                                      char test113[] = "                                                     L      J             XYuuVqq                      vIYjvBBi iiiiZL  i        iZBGFZjri      "     ;
                                                                                                                                                      char test114[] = "                                                    rErri  ii             NVrirVk                     oBJiiiYBFi ii iM   i   i i  Ui iiiiiiivi  "     ;
                                                                                                                                                      char test115[] = "                                                    MkooSqOS              i     i                     B      vOSvii iqi i      ii i          JP  "     ;
                                                                                                                                                      char test116[] = "                                                   iVYJookGr              i i  i                     rBiivJvivOiLFriLi iiiii iii  iEv         Zj  "    ;
                                                                                                                                                      char test117[] = "                                                   i     JV               XuFuVOo                     Ji iBBGIMv vJLi iiiiiiiii i  uZr       iiv   "   ;
                                                                                                                                                      char test118[] = "                                                         i                GLLjUNL                        GIivIIkirvLriiiiiiiiiii iiqBMvrri   v i    "  ;
                                                                                                                                                      char test119[] = "                                                 rGi    ii                MUjrJXi                       EMori   iirvJLvriiiiiiiivvSoLvjuFXo ii ir   " ;
                                                                                                                                                      char test120[] = "                                                EBGGOGkLu                 F    i                        OBi    iMr iirrriiiirJuLvLGJivvvvvLBv  Jv   " ;
                                                                                                                                                      char test121[] = "                                                UvrvYLLFBj                i    r                        Bv   iMNEEjjuUIUouJrii    iMkrvrrvVOBiiU    " ;
                                                                                                                                                      char test122[] = "                                                iPLvrvUVOi              iMXrvirS                       rF   UZvrivEViiii        uY  BkivJSVFOiii    " ;
                                                                                                                                                      char test123[] = "                                                PvrriLMr                BOVkNkoBB                      uuirqUvrvriX        JENi  B   MIYUJoEL       " ;
                                                                                                                                                      char test124[] = "                                               iPiriiOi                 LkiriivBi                      FGoBXUBXMqSMi oZYGBv  Br  iNiYYOukPIv        " ;
                                                                                                                                                      char test125[] = "                                               Zrrriuk                   PuYJvMi                       iSOZuUMBNSqu  MiBii  OGkS  iLi NNFi          " ;
                                                                                                                                                      char test126[] = "                                              XUrviiOi                  iGrvrLX                         iFGoLoGMOEY  v v             ii             " ;
                                                                                                                                                      char test127[] = "                                            iUoiviiUJ                   VLirirL                          iIGEFujuoN           iiiii                 " ;
                                                                                                                                                      char test128[] = "                                           vONYZENNG                   iXirrivv                             vkOBBBBPvriiiiiiii                      " ;
                                                                                                                                                      char test129[] = "                                                iii                   iGriLiiUI                                                                     " ;
                                                                                                                                                      char test130[] = "                                                                      vZoFquvBi                                                                     " ;
                                                                                                                                                      char test131[] = "   "      ;
                                                                                                                                                      char test132[] = "   "     ;
              */
			  
			  /*
			  M16_USART_SEND_STRING(test001,1,1);
			  M16_USART_SEND_STRING(test002,1,1);
			  M16_USART_SEND_STRING(test003,1,1);
			  M16_USART_SEND_STRING(test004,1,1);
			  M16_USART_SEND_STRING(test005,1,1);
			  M16_USART_SEND_STRING(test006,1,1);
			  M16_USART_SEND_STRING(test007,1,1);
			  M16_USART_SEND_STRING(test008,1,1);
			  M16_USART_SEND_STRING(test009,1,1);
			  M16_USART_SEND_STRING(test010,1,1);
			  M16_USART_SEND_STRING(test011,1,1);
			  M16_USART_SEND_STRING(test012,1,1);
			  M16_USART_SEND_STRING(test013,1,1);
			  M16_USART_SEND_STRING(test014,1,1);
			  M16_USART_SEND_STRING(test015,1,1);
			  M16_USART_SEND_STRING(test016,1,1);
			  M16_USART_SEND_STRING(test017,1,1);
			  M16_USART_SEND_STRING(test018,1,1);
			  M16_USART_SEND_STRING(test019,1,1);
			  M16_USART_SEND_STRING(test020,1,1);
			  M16_USART_SEND_STRING(test021,1,1);
			  M16_USART_SEND_STRING(test022,1,1);
			  M16_USART_SEND_STRING(test023,1,1);
			  M16_USART_SEND_STRING(test024,1,1);
			  M16_USART_SEND_STRING(test025,1,1);
			  M16_USART_SEND_STRING(test026,1,1);
			  M16_USART_SEND_STRING(test027,1,1);
			  M16_USART_SEND_STRING(test028,1,1);
			  M16_USART_SEND_STRING(test029,1,1);
			  M16_USART_SEND_STRING(test030,1,1);
			  M16_USART_SEND_STRING(test031,1,1);
			  M16_USART_SEND_STRING(test032,1,1);
			  M16_USART_SEND_STRING(test033,1,1);
			  M16_USART_SEND_STRING(test034,1,1);
			  M16_USART_SEND_STRING(test035,1,1);
			  M16_USART_SEND_STRING(test036,1,1);
			  M16_USART_SEND_STRING(test037,1,1);
			  M16_USART_SEND_STRING(test038,1,1);
			  M16_USART_SEND_STRING(test039,1,1);
			  M16_USART_SEND_STRING(test040,1,1);
			  M16_USART_SEND_STRING(test041,1,1);
			  M16_USART_SEND_STRING(test042,1,1);
			  M16_USART_SEND_STRING(test043,1,1);
			  M16_USART_SEND_STRING(test044,1,1);
			  M16_USART_SEND_STRING(test045,1,1);
			  M16_USART_SEND_STRING(test046,1,1);
			  M16_USART_SEND_STRING(test047,1,1);
			  M16_USART_SEND_STRING(test048,1,1);
			  M16_USART_SEND_STRING(test049,1,1);
			  M16_USART_SEND_STRING(test050,1,1);
			  M16_USART_SEND_STRING(test051,1,1);
			  M16_USART_SEND_STRING(test052,1,1);
			  M16_USART_SEND_STRING(test053,1,1);
			  M16_USART_SEND_STRING(test054,1,1);
			  M16_USART_SEND_STRING(test055,1,1);
			  M16_USART_SEND_STRING(test056,1,1);
			  M16_USART_SEND_STRING(test057,1,1);
			  M16_USART_SEND_STRING(test058,1,1);
			  M16_USART_SEND_STRING(test059,1,1);
			  M16_USART_SEND_STRING(test060,1,1);
			  M16_USART_SEND_STRING(test061,1,1);
			  M16_USART_SEND_STRING(test062,1,1);
			  M16_USART_SEND_STRING(test063,1,1);
			  M16_USART_SEND_STRING(test064,1,1);
			  M16_USART_SEND_STRING(test065,1,1);
			  M16_USART_SEND_STRING(test066,1,1);
			  M16_USART_SEND_STRING(test067,1,1);
			  M16_USART_SEND_STRING(test068,1,1);
			  M16_USART_SEND_STRING(test069,1,1);
			  M16_USART_SEND_STRING(test070,1,1);
			  M16_USART_SEND_STRING(test071,1,1);
			  M16_USART_SEND_STRING(test072,1,1);
			  M16_USART_SEND_STRING(test073,1,1);
			  M16_USART_SEND_STRING(test074,1,1);
			  M16_USART_SEND_STRING(test075,1,1);
			  M16_USART_SEND_STRING(test076,1,1);
			  M16_USART_SEND_STRING(test077,1,1);
			  M16_USART_SEND_STRING(test078,1,1);
			  M16_USART_SEND_STRING(test079,1,1);
			  M16_USART_SEND_STRING(test080,1,1);
			  M16_USART_SEND_STRING(test081,1,1);
			  M16_USART_SEND_STRING(test082,1,1);
			  M16_USART_SEND_STRING(test083,1,1);
			  M16_USART_SEND_STRING(test084,1,1);
			  M16_USART_SEND_STRING(test085,1,1);
			  M16_USART_SEND_STRING(test086,1,1);
			  M16_USART_SEND_STRING(test087,1,1);
			  M16_USART_SEND_STRING(test088,1,1);
			  M16_USART_SEND_STRING(test089,1,1);
			  M16_USART_SEND_STRING(test090,1,1);
			  M16_USART_SEND_STRING(test091,1,1);
			  M16_USART_SEND_STRING(test092,1,1);
			  M16_USART_SEND_STRING(test093,1,1);
			  M16_USART_SEND_STRING(test094,1,1);
			  M16_USART_SEND_STRING(test095,1,1);
			  M16_USART_SEND_STRING(test096,1,1);
			  M16_USART_SEND_STRING(test097,1,1);
			  M16_USART_SEND_STRING(test098,1,1);
			  M16_USART_SEND_STRING(test099,1,1);
			  M16_USART_SEND_STRING(test100,1,1);
			  M16_USART_SEND_STRING(test101,1,1);
			  M16_USART_SEND_STRING(test102,1,1);
			  M16_USART_SEND_STRING(test103,1,1);
			  M16_USART_SEND_STRING(test104,1,1);
			  M16_USART_SEND_STRING(test105,1,1);
			  M16_USART_SEND_STRING(test106,1,1);
			  M16_USART_SEND_STRING(test107,1,1);
			  M16_USART_SEND_STRING(test108,1,1);
			  M16_USART_SEND_STRING(test109,1,1);
			  M16_USART_SEND_STRING(test110,1,1);
			  M16_USART_SEND_STRING(test111,1,1);
			  M16_USART_SEND_STRING(test112,1,1);
			  M16_USART_SEND_STRING(test113,1,1);
			  M16_USART_SEND_STRING(test114,1,1);
			  M16_USART_SEND_STRING(test115,1,1);
			  M16_USART_SEND_STRING(test116,1,1);
			  M16_USART_SEND_STRING(test117,1,1);
			  M16_USART_SEND_STRING(test118,1,1);
			  M16_USART_SEND_STRING(test119,1,1);
			  M16_USART_SEND_STRING(test120,1,1);
			  M16_USART_SEND_STRING(test121,1,1);
			  M16_USART_SEND_STRING(test122,1,1);
			  M16_USART_SEND_STRING(test123,1,1);
			  M16_USART_SEND_STRING(test124,1,1);
			  M16_USART_SEND_STRING(test125,1,1);
			  M16_USART_SEND_STRING(test126,1,1);
			  M16_USART_SEND_STRING(test127,1,1);
			  M16_USART_SEND_STRING(test128,1,1);
			  M16_USART_SEND_STRING(test129,1,1);
			  M16_USART_SEND_STRING(test130,1,1);
			  M16_USART_SEND_STRING(test131,1,1);
			  M16_USART_SEND_STRING(test132,1,1); 
			  */                                                                                                                                       
#endif /* LIB_USART_M16_H_ */
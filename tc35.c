

uchar code at[] = "AT\r";                      //????  "\r"--"enter"         
uchar code cmgf[]="AT+CMGF=1\r";		       //?????????---??
uchar code cmgs[]="AT+CMGS=13632438226\r";	   // ???????
uchar code msg[]="break in!!!";
uchar code af[]="AT&F";  					   // ???


	
	
void delay_1(uint z)   //Zms??
{
	uint x,y;
	for(x=z;x>0;x--)
	for(y=110;y>0;y--);
}
void   send_c(uchar cc)   //??????
{
    
   SBUF =cc;
   while(!TI );
    TI = 0; 
              
}

void   send_u(uchar *tab)     //???????
{ 
    while((*tab)!= '\0')
    { 
            SBUF =*tab; 
            while(!TI ); 
            TI = 0; 
            tab++; 
     } 
	send_c(0x0d);		 //???? 00001101
	send_c(0x0a);		 //00001010
}   
void uart_init()             //?????
{
 SCON=0x50;  //????	 ---??????1 REN=1
 PCON=0x00;  //??????
 TMOD=0x20;  //???1??2
 TH1=0xfd;   // ??????9600
 TL1=0xfd;
 TR1=1;
 ES=1;       //?????
}
void gsm()
{	 
   int i;
   
	uart_init(); 			  //?????
	send_u(af);                 //"AT&F"---???
	EA=0;
 	RI=0;
	send_u(at);
 delay_1(1000);
 send_u(cmgf);     //"AT+CMGF=1\r"
     delay_1(1000);
     send_u(cmgs);	   //"AT+CMGS=15260369536\r"
     delay_1(1000);
     send_u(msg);	  //"!!!!woring!!!!"
     delay_1(1000);
      send_c(0x1A);   // ????
     delay_1(1000);
     send_u(af);
     delay_1(1000);
     while(1);
 }

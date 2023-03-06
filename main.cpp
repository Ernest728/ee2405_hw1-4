#include "mbed.h"
 
BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);
DigitalIn mypin(BUTTON1);
DigitalOut myled(LED1);
DigitalOut success(LED2);

char table_num[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
char table_letter[26] = {
    0x77, 0x7C, 0x58, 0x5E, 0x79,
    0x71, 0x3D, 0x76, 0x45, 0x07,
    0x7E, 0x38, 0x74, 0x54, 0x3F,
    0x73, 0x67, 0x50, 0x6C, 0x13,
    0x3E, 0x62, 0x36, 0x64, 0x66, 0x53};
int five_in_row[5] = {0, 0, 0, 0, 0};
int main(){
    int push = 0;
    int not_push = 0;
    int count = 0;
    int status = 0; // Letter: status = 0 // Figure: status = 1
    int Decoder[5] = {0, 0, 0, 0, 0}; // five words in a row
    while(1){
            success = 1;
            ThisThread::sleep_for(500ms);
            if (mypin == 0)
                push++;
            if (push == 3){
                myled = 1;
                ThisThread::sleep_for(250ms);
                myled = 0;
                ThisThread::sleep_for(250ms);
                myled = 1;
                ThisThread::sleep_for(250ms);
                myled = 0;
                push = 0;
                not_push = 0;
                Decoder[count++] = 1;
            }
            if (mypin == 1)
                not_push++;
            if (not_push == 3){
                myled = 1;
                ThisThread::sleep_for(500ms);
                myled = 0;
                push = 0;
                not_push = 0;
                Decoder[count++] = 0;
            }
            // 7 segment
            if (Decoder[0]==1 && Decoder[1]==0 && Decoder[2]==0 && Decoder[3]==0 && Decoder[4]==0 && count==5)
                {status = 0; count = 0;} // change to Letter
            else if (Decoder[0]==0 && Decoder[1]==1 && Decoder[2]==0 && Decoder[3]==0 && Decoder[4]==0 && count==5)
                {status = 1; count = 0;} // change to Figure
            else if (Decoder[0]==0 && Decoder[1]==1 && Decoder[2]==1 && Decoder[3]==1 && Decoder[4]==1 && count==5 && status==1)
                {display = table_num[0]; count = 0;}// 0
            else if (Decoder[0]==0 && Decoder[1]==0 && Decoder[2]==0 && Decoder[3]==0 && Decoder[4]==1 && count==5 && status==1)
                {display = table_num[1]; count = 0;}// 1
            else if (Decoder[0]==0 && Decoder[1]==0 && Decoder[2]==0 && Decoder[3]==1 && Decoder[4]==0 && count==5 && status==1)
                {display = table_num[2]; count = 0;}// 2
            else if (Decoder[0]==0 && Decoder[1]==0 && Decoder[2]==1 && Decoder[3]==0 && Decoder[4]==0 && count==5 && status==1)
                {display = table_num[3]; count = 0;}// 3
            else if (Decoder[0]==0 && Decoder[1]==0 && Decoder[2]==1 && Decoder[3]==0 && Decoder[4]==1 && count==5 && status==1)
                {display = table_num[4]; count = 0;}// 4
            else if (Decoder[0]==0 && Decoder[1]==0 && Decoder[2]==1 && Decoder[3]==1 && Decoder[4]==1 && count==5 && status==1)
                {display = table_num[5]; count = 0;}// 5
            else if (Decoder[0]==0 && Decoder[1]==1 && Decoder[2]==0 && Decoder[3]==0 && Decoder[4]==1 && count==5 && status==1)
                {display = table_num[6]; count = 0;}// 6
            else if (Decoder[0]==0 && Decoder[1]==1 && Decoder[2]==0 && Decoder[3]==1 && Decoder[4]==0 && count==5 && status==1)
                {display = table_num[7]; count = 0;}// 7
            else if (Decoder[0]==0 && Decoder[1]==1 && Decoder[2]==1 && Decoder[3]==0 && Decoder[4]==0 && count==5 && status==1)
                {display = table_num[8]; count = 0;}// 8
            else if (Decoder[0]==0 && Decoder[1]==1 && Decoder[2]==1 && Decoder[3]==0 && Decoder[4]==1 && count==5 && status==1)
                {display = table_num[9]; count = 0;}// 9
            else if (Decoder[0]==0 && Decoder[1]==0 && Decoder[2]==0 && Decoder[3]==0 && Decoder[4]==1 && count==5 && status==0)
                {display = table_letter[0]; count = 0;}// A
            else if (Decoder[0]==0 && Decoder[1]==1 && Decoder[2]==1 && Decoder[3]==0 && Decoder[4]==0 && count==5 && status==0)
                {display = table_letter[1]; count = 0;}// B
            else if (Decoder[0]==0 && Decoder[1]==1 && Decoder[2]==1 && Decoder[3]==0 && Decoder[4]==1 && count==5 && status==0)
                {display = table_letter[2]; count = 0;}// C
            else if (Decoder[0]==0 && Decoder[1]==1 && Decoder[2]==1 && Decoder[3]==1 && Decoder[4]==1 && count==5 && status==0)
                {display = table_letter[3]; count = 0;}// D
            else if (Decoder[0]==0 && Decoder[1]==0 && Decoder[2]==0 && Decoder[3]==1 && Decoder[4]==0 && count==5 && status==0)
                {display = table_letter[4]; count = 0;}// E
            else if (Decoder[0]==0 && Decoder[1]==1 && Decoder[2]==1 && Decoder[3]==1 && Decoder[4]==0 && count==5 && status==0)
                {display = table_letter[5]; count = 0;}// F
            else if (Decoder[0]==0 && Decoder[1]==1 && Decoder[2]==0 && Decoder[3]==1 && Decoder[4]==0 && count==5 && status==0)
                {display = table_letter[6]; count = 0;}// G
            else if (Decoder[0]==0 && Decoder[1]==1 && Decoder[2]==0 && Decoder[3]==1 && Decoder[4]==1 && count==5 && status==0)
                {display = table_letter[7]; count = 0;}// H
            else if (Decoder[0]==0 && Decoder[1]==0 && Decoder[2]==1 && Decoder[3]==1 && Decoder[4]==0 && count==5 && status==0)
                {display = table_letter[8]; count = 0;}// I
            else if (Decoder[0]==0 && Decoder[1]==1 && Decoder[2]==0 && Decoder[3]==0 && Decoder[4]==1 && count==5 && status==0)
                {display = table_letter[9]; count = 0;}// J
            else if (Decoder[0]==1 && Decoder[1]==1 && Decoder[2]==0 && Decoder[3]==0 && Decoder[4]==1 && count==5 && status==0)
                {display = table_letter[10]; count = 0;}// K
            else if (Decoder[0]==1 && Decoder[1]==1 && Decoder[2]==0 && Decoder[3]==1 && Decoder[4]==1 && count==5 && status==0)
                {display = table_letter[11]; count = 0;}// L
            else if (Decoder[0]==1 && Decoder[1]==1 && Decoder[2]==0 && Decoder[3]==1 && Decoder[4]==0 && count==5 && status==0)
                {display = table_letter[12]; count = 0;}// M
            else if (Decoder[0]==1 && Decoder[1]==1 && Decoder[2]==1 && Decoder[3]==1 && Decoder[4]==0 && count==5 && status==0)
                {display = table_letter[13]; count = 0;}// N
            else if (Decoder[0]==0 && Decoder[1]==0 && Decoder[2]==1 && Decoder[3]==1 && Decoder[4]==1 && count==5 && status==0)
                {display = table_letter[14]; count = 0;}// O
            else if (Decoder[0]==1 && Decoder[1]==1 && Decoder[2]==1 && Decoder[3]==1 && Decoder[4]==1 && count==5 && status==0)
                {display = table_letter[15]; count = 0;}// P
            else if (Decoder[0]==1 && Decoder[1]==1 && Decoder[2]==1 && Decoder[3]==0 && Decoder[4]==1 && count==5 && status==0)
                {display = table_letter[16]; count = 0;}// Q
            else if (Decoder[0]==1 && Decoder[1]==1 && Decoder[2]==1 && Decoder[3]==0 && Decoder[4]==0 && count==5 && status==0)
                {display = table_letter[17]; count = 0;}// R
            else if (Decoder[0]==1 && Decoder[1]==0 && Decoder[2]==1 && Decoder[3]==0 && Decoder[4]==0 && count==5 && status==0)
                {display = table_letter[18]; count = 0;}// S
            else if (Decoder[0]==1 && Decoder[1]==0 && Decoder[2]==1 && Decoder[3]==0 && Decoder[4]==1 && count==5 && status==0)
                {display = table_letter[19]; count = 0;}// T
            else if (Decoder[0]==0 && Decoder[1]==0 && Decoder[2]==1 && Decoder[3]==0 && Decoder[4]==1 && count==5 && status==0)
                {display = table_letter[20]; count = 0;}// U
            else if (Decoder[0]==1 && Decoder[1]==0 && Decoder[2]==1 && Decoder[3]==1 && Decoder[4]==1 && count==5 && status==0)
                {display = table_letter[21]; count = 0;}// V
            else if (Decoder[0]==1 && Decoder[1]==0 && Decoder[2]==1 && Decoder[3]==1 && Decoder[4]==0 && count==5 && status==0)
                {display = table_letter[22]; count = 0;}// W
            else if (Decoder[0]==1 && Decoder[1]==0 && Decoder[2]==0 && Decoder[3]==1 && Decoder[4]==0 && count==5 && status==0)
                {display = table_letter[23]; count = 0;}// X
            else if (Decoder[0]==0 && Decoder[1]==0 && Decoder[2]==1 && Decoder[3]==0 && Decoder[4]==0 && count==5 && status==0)
                {display = table_letter[24]; count = 0;}// Y
            else if (Decoder[0]==1 && Decoder[1]==0 && Decoder[2]==0 && Decoder[3]==1 && Decoder[4]==1 && count==5 && status==0)
                {display = table_letter[25]; count = 0;}// Z
            success = 0;
            ThisThread::sleep_for(500ms);
    }
}


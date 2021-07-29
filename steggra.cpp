#include <iostream>
#include <vector>
#include <sstream>
#include <bitset>
//#include "steggra.hpp"
#define sWIDTH 640

using namespace std;

void find( uint8_t (*hdata)[][sWIDTH<<1][3],  uint8_t (*data)[][sWIDTH][3], int key[25], int WIDTH, int LENGTH)
{   
    static int rgb_shift[24];
   
    for(size_t n=24;n--;)
    	rgb_shift[n] = key[n]%8;	
    	
    for(size_t y=LENGTH;y--;)
        for(size_t x=WIDTH;x--;)
        {
            		(*data)[y][x][key[0]>>3]|= ((1&((*hdata)[(y<<1)][(x<<1)][0]))<<(rgb_shift[0]));
            		(*data)[y][x][key[1]>>3]|= ((1&((*hdata)[(y<<1)][(x<<1)][0]>>1))<<(rgb_shift[1])); 
            		(*data)[y][x][key[2]>>3]|= ((1&((*hdata)[(y<<1)][(x<<1)][1]))<<(rgb_shift[2])); 
            		(*data)[y][x][key[3]>>3]|= ((1&((*hdata)[(y<<1)][(x<<1)][1]>>1))<<(rgb_shift[3])); 
            		(*data)[y][x][key[4]>>3]|= ((1&((*hdata)[(y<<1)][(x<<1)][2]))<<(rgb_shift[4])); 
            		(*data)[y][x][key[5]>>3]|= ((1&((*hdata)[(y<<1)][(x<<1)][2]>>1))<<(rgb_shift[5])); 
            		(*data)[y][x][key[6]>>3]|= ((1&((*hdata)[(y<<1)][(x<<1)+1][0]))<<(rgb_shift[6])); 
            		(*data)[y][x][key[7]>>3]|= ((1&((*hdata)[(y<<1)][(x<<1)+1][0]>>1))<<(rgb_shift[7]));
            		(*data)[y][x][key[8]>>3]|= ((1&((*hdata)[(y<<1)][(x<<1)+1][1]))<<(rgb_shift[8]));
            		(*data)[y][x][key[9]>>3]|= ((1&((*hdata)[(y<<1)][(x<<1)+1][1]>>1))<<(rgb_shift[9])); 
            		(*data)[y][x][key[10]>>3]|= ((1&((*hdata)[(y<<1)][(x<<1)+1][2]))<<(rgb_shift[10])); 
            		(*data)[y][x][key[11]>>3]|= ((1&((*hdata)[(y<<1)][(x<<1)+1][2]>>1))<<(rgb_shift[11])); 
            		(*data)[y][x][key[12]>>3]|= ((1&((*hdata)[(y<<1)+1][(x<<1)][0]))<<(rgb_shift[12])); 
            		(*data)[y][x][key[13]>>3]|= ((1&((*hdata)[(y<<1)+1][(x<<1)][0]>>1))<<(rgb_shift[13])); 
            		(*data)[y][x][key[14]>>3]|= ((1&((*hdata)[(y<<1)+1][(x<<1)][1]))<<(rgb_shift[14])); 
            		(*data)[y][x][key[15]>>3]|= ((1&((*hdata)[(y<<1)+1][(x<<1)][1]>>1))<<(rgb_shift[15])); 
            		(*data)[y][x][key[16]>>3]|= ((1&((*hdata)[(y<<1)+1][(x<<1)][2]))<<(rgb_shift[16]));
            		(*data)[y][x][key[17]>>3]|= ((1&((*hdata)[(y<<1)+1][(x<<1)][2]>>1))<<(rgb_shift[17])); 
            		(*data)[y][x][key[18]>>3]|= ((1&((*hdata)[(y<<1)+1][(x<<1)+1][0]))<<(rgb_shift[18])); 
            		(*data)[y][x][key[19]>>3]|= ((1&((*hdata)[(y<<1)+1][(x<<1)+1][0]>>1))<<(rgb_shift[19])); 
            		(*data)[y][x][key[20]>>3]|= ((1&((*hdata)[(y<<1)+1][(x<<1)+1][1]))<<(rgb_shift[20])); 
            		(*data)[y][x][key[21]>>3]|= ((1&((*hdata)[(y<<1)+1][(x<<1)+1][1]>>1))<<(rgb_shift[21])); 
            		(*data)[y][x][key[22]>>3]|= ((1&((*hdata)[(y<<1)+1][(x<<1)+1][2]))<<(rgb_shift[22])); 
            		(*data)[y][x][key[23]>>3]|= ((1&((*hdata)[(y<<1)+1][(x<<1)+1][2]>>1))<<(rgb_shift[23]));   
            		

            		(*data)[y][x][0]^=key[24];
            		(*data)[y][x][1]^=key[24];
            		(*data)[y][x][2]^=key[24];
        }

}


void hide( uint8_t (*hdata)[][sWIDTH<<1][3],  uint8_t (*data)[][sWIDTH][3],int key[25], int WIDTH, int LENGTH)
{
    static int rgb_shift[24];
   
    for(size_t n=24;n--;)
    	rgb_shift[n] = key[n]%8;
    	
    for(size_t y=LENGTH;y--;)
        for(size_t x=WIDTH;x--;)
        {	
        		(*hdata)[y<<1][x<<1][0]&= 0xFC;
        		(*hdata)[y<<1][(x<<1)+1][0]&= 0xFC;
        		(*hdata)[(y<<1)+1][x<<1][0]&= 0xFC;
        		(*hdata)[(y<<1)+1][(x<<1)+1][0]&= 0xFC;
        		(*data)[y][x][0]^=key[24];
        		
        		(*hdata)[y<<1][x<<1][1]&= 0xFC;
        		(*hdata)[y<<1][(x<<1)+1][1]&= 0xFC;
        		(*hdata)[(y<<1)+1][x<<1][1]&= 0xFC;
        		(*hdata)[(y<<1)+1][(x<<1)+1][1]&= 0xFC;
        		(*data)[y][x][1]^=key[24];
        		
        		(*hdata)[y<<1][x<<1][2]&= 0xFC;
        		(*hdata)[y<<1][(x<<1)+1][2]&= 0xFC;
        		(*hdata)[(y<<1)+1][x<<1][2]&= 0xFC;
        		(*hdata)[(y<<1)+1][(x<<1)+1][2]&= 0xFC;
        		(*data)[y][x][2]^=key[24];
        	
			(*hdata)[(y<<1)+0][(x<<1)][0]|= ((1&((*data)[y][x][key[0]>>3]>>(rgb_shift[0])))) |
				((1&((*data)[y][x][key[1]>>3]>>(rgb_shift[1])))<<1);

			(*hdata)[(y<<1)][(x<<1)][1]|= ((1&((*data)[y][x][key[2]>>3]>>(rgb_shift[2])))) |
				((1&((*data)[y][x][key[3]>>3]>>(rgb_shift[3])))<<1);

			(*hdata)[(y<<1)][(x<<1)][2]|= ((1&((*data)[y][x][key[4]>>3]>>(rgb_shift[4])))) |
				((1&((*data)[y][x][key[5]>>3]>>(rgb_shift[5])))<<1);

			(*hdata)[(y<<1)][(x<<1)+1][0]|= ((1&((*data)[y][x][key[6]>>3]>>(rgb_shift[6])))) |
				((1&((*data)[y][x][key[7]>>3]>>(rgb_shift[7])))<<1);

			(*hdata)[(y<<1)][(x<<1)+1][1]|= ((1&((*data)[y][x][key[8]>>3]>>(rgb_shift[8])))) |
				((1&((*data)[y][x][key[9]>>3]>>(rgb_shift[9])))<<1);

			(*hdata)[(y<<1)][(x<<1)+1][2]|= ((1&((*data)[y][x][key[10]>>3]>>(rgb_shift[10])))) |
				((1&((*data)[y][x][key[11]>>3]>>(rgb_shift[11])))<<1);

			(*hdata)[(y<<1)+1][(x<<1)][0]|= ((1&((*data)[y][x][key[12]>>3]>>(rgb_shift[12])))) |
				((1&((*data)[y][x][key[13]>>3]>>(rgb_shift[13])))<<1);

			(*hdata)[(y<<1)+1][(x<<1)][1]|= ((1&((*data)[y][x][key[14]>>3]>>(rgb_shift[14])))) |
				((1&((*data)[y][x][key[15]>>3]>>(rgb_shift[15])))<<1);

			(*hdata)[(y<<1)+1][(x<<1)][2]|= ((1&((*data)[y][x][key[16]>>3]>>(rgb_shift[16])))) |
				((1&((*data)[y][x][key[17]>>3]>>(rgb_shift[17])))<<1);

			(*hdata)[(y<<1)+1][(x<<1)+1][0]|= ((1&((*data)[y][x][key[18]>>3]>>(rgb_shift[18])))) |
				((1&((*data)[y][x][key[19]>>3]>>(rgb_shift[19])))<<1);

			(*hdata)[(y<<1)+1][(x<<1)+1][1]|= ((1&((*data)[y][x][key[20]>>3]>>(rgb_shift[20])))) |
				((1&((*data)[y][x][key[21]>>3]>>(rgb_shift[21])))<<1);

			(*hdata)[(y<<1)+1][(x<<1)+1][2]|= ((1&((*data)[y][x][key[22]>>3]>>(rgb_shift[22])))) | 
				((1&((*data)[y][x][key[23]>>3]>>(rgb_shift[23])))<<1);

	}
}

void circularShift_Y(uint8_t (*data)[][sWIDTH][3], int y, int n)
{
    int temp = 0;
    for (int k = 0; k < n; k++)
    {
    	for (int m = 0; m < 3; m++)
    	{
        	temp=(*data)[y][sWIDTH-1][m];
        	for(int i = sWIDTH; --i ;)
            		(*data)[y][i][m] = (*data)[y][i-1][m];
        	(*data)[y][0][m]=temp;
        }
    }
}

void circularShift_X(uint8_t (*data)[][sWIDTH][3], int x, int n)
{
    int temp = 0;
    for (int k = 0; k <n; k++)
    {
    	for (int m = 0; m < 3; m++)
    	{
        	temp=(*data)[480-1][x][m];
        	for(int i = 480; --i;)
            		(*data)[i][x][m] = (*data)[i-1][x][m];
        	(*data)[0][x][m]=temp;
        }
    }
}

void magic_cube(uint8_t (*data)[][sWIDTH][3], int key[25])
{
    static int key_y[480]={0};
    static int key_x[640]={0};

    for(int y=0;y<480;y++)
    {
    	key_y[y]=rand()%480;
    	circularShift_Y(data,y,key_y[y]);
    }
    for(int x=0;x<640;x++)
    {
        key_x[x]=rand()%640;
        circularShift_X(data,x,key_x[x]);
    }
	
}

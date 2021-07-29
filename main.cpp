#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <cmath>
#include <sstream>
#include <bitset>
#include <chrono>
#include <ctime>
#include "steggra.cpp"
#include <list>
#include <vector>
#include <CL/cl.hpp>

#define LENGTH 480
#define WIDTH 640

int main()
{
    int y,x,z, i;
    int Lscreen=LENGTH, Wscreen=WIDTH;
    static uint8_t info[LENGTH][WIDTH][3]={0};
    static uint8_t image[LENGTH<<1][WIDTH<<1][3]={0};
    static uint8_t result[LENGTH][WIDTH][3]={0};
    int key[25]={21,2,9,18,13,5,7,14,10,6,1,20,4,3,17,23,0,19,15,22,12,8,16,11,122}; //0-23 LSB switch to RGB // 24 XOR key

    std::cout<<std::endl <<std::endl;

    std::cout<<"Information: read" <<std::endl;
    cv::Mat inf  = cv::imread("No-Filter.png",cv::IMREAD_COLOR);
    std::cout<<"Medium: read" <<std::endl;
    cv::Mat img  = cv::imread("baymax.png",cv::IMREAD_COLOR);

    for(int y=LENGTH;y--;)
        for(int x=WIDTH;x--;)
            for(int z=3;z--;)
            {
               *(*(*(image+(y<<1))+(x<<1))+z)=(uint8_t)img.at<cv::Vec3b>((y<<1),(x<<1))[z];
               *(*(*(image+(y<<1))+(x<<1)+1)+z)=(uint8_t)img.at<cv::Vec3b>((y<<1),(x<<1)+1)[z];
               *(*(*(image+(y<<1)+1)+(x<<1))+z)=(uint8_t)img.at<cv::Vec3b>((y<<1)+1,(x<<1))[z];
               *(*(*(image+(y<<1)+1)+(x<<1)+1)+z)=(uint8_t)img.at<cv::Vec3b>((y<<1)+1,(x<<1)+1)[z];

               *(*(*(info+y)+x)+z)=(uint8_t)inf.at<cv::Vec3b>(y,x)[z];
            }

    std::cout<<"magic_cube: start" <<std::endl;
    auto start3 = std::chrono::system_clock::now();
    magic_cube(&info);
    auto end3 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds3 = end3-start3;
    printf("ready %f s\n", elapsed_seconds3.count());
    std::cout<<"magic_cube: ready" <<std::endl;

    cv::Mat infoMC_m = cv::Mat(LENGTH,WIDTH,CV_8UC3,&info);
    cv::imwrite("-Data Hiding- infoMC.png",infoMC_m);

    std::cout<<"hide: start" <<std::endl;
    auto start = std::chrono::system_clock::now();
    hide( &image,  &info,  key,  Wscreen,  Lscreen);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    printf("ready %f s\n", elapsed_seconds.count());
    std::cout<<"hide: ready" <<std::endl;

    std::cout<<"medium-image: save" <<std::endl;
    cv::Mat hidedata_m2 = cv::Mat(LENGTH<<1,WIDTH<<1,CV_8UC3,&image);
    cv::imwrite("-Data Hiding-medium.png",hidedata_m2);

    std::cout<<"find: start" <<std::endl;
    auto start2 = std::chrono::system_clock::now();
    find( &image,  &result,  key,  Wscreen,  Lscreen);
    auto end2 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = end2-start2;
    printf("ready %f s\n", elapsed_seconds2.count());
    std::cout<<"hide: ready" <<std::endl;

    std::cout<<"result-image: save" <<std::endl;
    cv::Mat result_m = cv::Mat(LENGTH,WIDTH,CV_8UC3,&result);
    cv::imwrite("-Data Hiding- result.png",result_m);

    /*auto start3 = std::chrono::system_clock::now();
    std::vector<std::vector<std::vector< int>>> v(LENGTH, std::vector<std::vector< int>>(WIDTH, std::vector< int>(3)));
    std::test(v);

    for(y=0;y<LENGTH;++y)
        for(x=0;x<WIDTH;++x)
        	for(z=0;z<24;z++)
    			v[y][x][z]=z-((z/8)*8);



    auto end3 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds3 = end3-start3;
    printf("time-test : ready %f s\n", elapsed_seconds3.count());*/


    return 0;
}

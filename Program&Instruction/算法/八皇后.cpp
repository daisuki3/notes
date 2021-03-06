#include<iostream>
#include<vector>
using namespace std;
#define QUEUE 8

void queue();
void lay(int i);
/*
八皇后问题是一个以国际象棋为背景的问题：如何能够在 8×8 的国际象棋棋盘上放置八个皇后，
使得任何一个皇后都无法直接吃掉其他的皇后？为了达到此目的，任两个皇后都不能处于同一条
横行、纵行或斜线上。
*/
vector<int> a(1+QUEUE,0),//a数组用来判断纵行
            b(1+3*QUEUE,0),//b c 数组用来判断两条斜线 
            c(1+3*QUEUE,0);
            /* why 3 * QUEUE ?

            1 <= j,i <= QUEUE
            matrix(i, j)
            i 代表横坐标 j代表纵坐标

            在 ↗ 斜线上 有 i + j = 常量
            在 ↖ 斜线上 有 j - i = 常量
                
            数组 3 * QUEUE 容量, QUEUE + i + j 和
            QUEUE + j - i 不会越界。
            */

int ans=0;

void queue(){

    lay(1);

    cout<<ans<<endl;
}

void lay(int i){
    int j=0;

    while(++j <= QUEUE){

        if(a[j]+b[QUEUE+j-i]+c[QUEUE+j+i]==0){//判断是否可以放置 

            a[j]=b[QUEUE+j-i]=c[QUEUE+j+i]=1;//现在不可放置了

            if(i<QUEUE) 
                lay(i+1);  //继续放下一个
            else
                ++ans; //已经放好八个 找到一种答案
        
            a[j]=b[QUEUE+j-i]=c[QUEUE+j+i]=0;  // 这个位置的方案已经寻找完毕 回溯
        }

    }
    
}


int main(){
    queue();
    
    return 0;
}

/*
 * 利用OpenMP并行处理高維正定二次方程
 * 
 * 
 */

#include <stdio.h>
#include "gc_inf.h"
#include "vect_op.h"
#include "line_search.h"
#include "gc_setting.h"
#include "fr_gc.h"
#include <math.h>

double 	x[N],// 测试点向量
		gk[N],// 当前梯度向量
        dk[N];//当前搜索方向


double  gk_gk=0.0,//上一次的gkgk
        tmp=0.0,
        beta_k_1,
        ak=0.0;//步长
extern struct obj_param param;


//设置初始点
void init_x(double *x){

}

int fr_gc_main(){

	printf("FR_GC start N=%d, END=%f, MAX_REPEAT=%d",N,END,MAX_REPEAT);

    // 初始化
    init_x(x);
    init_obj_function();


    for(int i=0;i<MAX_REPEAT;i++){

        dec_function(x,gk);// 计算梯度

        //计算范数
        tmp = vect_mult_sum(gk,gk);
        printf("%f\n",tmp);
        if(sqrt(tmp)<=END){
            printf("step=%d\n",i);
            show_vect(x);
            break;
        }
        //计算方向
        if(i==0) vect_mult_one(gk,-1.0,dk);
        else{
            beta_k_1 = tmp/gk_gk;
            vect_mult_one(dk,beta_k_1,dk);
            vect_mult_one(gk,-1.0,gk);
            vect_add(gk,dk,dk);
        }
        gk_gk = tmp;

        //计算步长
        ak = armijo_func(x,dk,ARMIJO_BEAT,ARMIJO_SIGMA);

        //更新测试点
        vect_mult_one(dk,ak,gk);// 这里的gk当成临时变量使用
        vect_add(x,gk,x);

    }

	return 0;
}



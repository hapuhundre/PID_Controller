#include <vector>
#include <algorithm>

#include "PID.h"

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double K_p, double K_d, double K_i, bool is_tunning) {
    tunning_mode = is_tunning;
    if(tunning_mode){
    // Initial controller values
	    err[0] = 0.1;
	    err[1] = 10.0;	
        err[2] = 0.0;
    
        // Error values
        error = 0.0;
              
        // Twiddle values
        tol = 0.0001;   // 阈值
	    tunning_update = 1000; // 更新的步数
        min_error = 0.0;    // 
        iter = 0;   // 迭代的index
	    idx = 0;  // 当前更新的控制系数的index
	    stage = 1;  // ?
        sum_d_err = 0;
	    d_err[0] = 0.1;
	    d_err[1] = 1.0;
	    d_err[2] = 0.00001;
    }else{
        // 误差初始值均为0
        err[0] = K_p;
        err[1] = K_d;
        err[2] = K_i;
    }
    p_error = 0.0;
    d_error = 0.0;
    i_error = 0.0;
    cte_sum = 0.0;
    cte_pre = 0.0;
}



double PID::SteerValue(double cte) {
    if(tunning_mode){
        iter += 1;
        /*
        cout << "K_p=" << err[0] << endl;
        cout << "K_d=" << err[1] << endl;
        cout << "K_i=" << err[2] << endl;
        */
    }
    return p_error+d_error+i_error;	
}


void PID::Tunning() {

	sum_d_err = 0;
  

	for (int i=0; i<3; i++) {
	    sum_d_err += d_err[i];
	} 
	  
	// 调整更新步幅 Stage1
    if (sum_d_err > tol && stage == 1) {
	  	err[idx] += d_err[idx];
	  	error = 0;
	}
    
	// Stage2
	if (sum_d_err>tol && stage == 2) { 
	    if (error < min_error) {
            min_error = error;
            d_err[idx] *= 1.1;
	  		error = 0;
        }else{
            err[idx] -= 2*d_err[idx];
	  		error = 0;
	  	}
	}
	  
	// Stage3		
    if (sum_d_err > tol && stage == 3) { 
        if (error < min_error) {
            min_error = error;
            d_err[idx] *= 1.1;
	  		error = 0;
        }else{
            err[idx] += d_err[idx];
            d_err[idx] *= 0.9;
	  		error = 0;
        }
    }
}

void PID::UpdateError(double cte){
    if(tunning_mode){
        iter += 1;
        error += cte*cte / iter;

        if(iter==tunning_update) {
            min_error = error;
            Tunning();
            stage += 1;
        }

        if(iter > tunning_update && (iter % tunning_update==0) ){
            Tunning();
            error = 0;
            iter = 1000;
            stage += 1;
            if(stage > 3){
                stage = 1;
                idx += 1;
                if(idx>2) idx=0;
            }
        }
    }
    cte_sum += cte;
    p_error = -err[0]*cte;
    d_error = -err[1]*(cte-cte_pre);
    i_error = -err[2]*cte_sum;
    cte_pre = cte;
}

#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double d_error;
  double i_error;
  double error;
  bool tunning_mode;
  /*
  * Coefficients
  */ 
  double err[3];

  // 
  double d_err[3];
  double sum_d_err;
  double tol;
  double min_error;
  int tunning_update;
  int iter;
  int idx;
  int stage;

  /*
  * previous cte &
  * cte sum
  */
  double cte_pre;
  double cte_sum;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double K_p, double K_i, double K_d, bool is_tunning);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double SteerValue(double cte);

  void Tunning();
};

#endif /* PID_H */

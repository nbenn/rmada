
#include <RcppArmadillo.h>

RCPP_MODULE(arma){

    Rcpp::class_<arma::mat>("mat")
      .constructor<arma::uword, arma::uword>()
      .field_readonly("nrow", &arma::mat::n_rows)
      .field_readonly("ncol", &arma::mat::n_cols)
      .field_readonly("length", &arma::mat::n_elem)
    ;

    Rcpp::class_<arma::colvec>("col")
      .derives<arma::mat>("mat")
      .constructor<arma::uword>()
    ;
}

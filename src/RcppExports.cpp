// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include "../inst/include/rmada_types.h"
#include <RcppArmadillo.h>
#include <Rcpp.h>

using namespace Rcpp;

// mat_init
SEXP mat_init(Rcpp::XPtr<Memory> mem, arma::uword n_rows, arma::uword n_cols, std::size_t data_type);
RcppExport SEXP _rmada_mat_init(SEXP memSEXP, SEXP n_rowsSEXP, SEXP n_colsSEXP, SEXP data_typeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::XPtr<Memory> >::type mem(memSEXP);
    Rcpp::traits::input_parameter< arma::uword >::type n_rows(n_rowsSEXP);
    Rcpp::traits::input_parameter< arma::uword >::type n_cols(n_colsSEXP);
    Rcpp::traits::input_parameter< std::size_t >::type data_type(data_typeSEXP);
    rcpp_result_gen = Rcpp::wrap(mat_init(mem, n_rows, n_cols, data_type));
    return rcpp_result_gen;
END_RCPP
}
// n_rows
arma::uword n_rows(SEXP x);
RcppExport SEXP _rmada_n_rows(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(n_rows(x));
    return rcpp_result_gen;
END_RCPP
}
// n_cols
arma::uword n_cols(SEXP x);
RcppExport SEXP _rmada_n_cols(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(n_cols(x));
    return rcpp_result_gen;
END_RCPP
}
// mem_init
SEXP mem_init(std::string name, std::size_t n_elem, std::size_t data_type, std::size_t mem_type);
RcppExport SEXP _rmada_mem_init(SEXP nameSEXP, SEXP n_elemSEXP, SEXP data_typeSEXP, SEXP mem_typeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type name(nameSEXP);
    Rcpp::traits::input_parameter< std::size_t >::type n_elem(n_elemSEXP);
    Rcpp::traits::input_parameter< std::size_t >::type data_type(data_typeSEXP);
    Rcpp::traits::input_parameter< std::size_t >::type mem_type(mem_typeSEXP);
    rcpp_result_gen = Rcpp::wrap(mem_init(name, n_elem, data_type, mem_type));
    return rcpp_result_gen;
END_RCPP
}
// mem_attach
void mem_attach(Rcpp::XPtr<Memory> mem);
RcppExport SEXP _rmada_mem_attach(SEXP memSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::XPtr<Memory> >::type mem(memSEXP);
    mem_attach(mem);
    return R_NilValue;
END_RCPP
}
// mem_detach
void mem_detach(Rcpp::XPtr<Memory> mem);
RcppExport SEXP _rmada_mem_detach(SEXP memSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::XPtr<Memory> >::type mem(memSEXP);
    mem_detach(mem);
    return R_NilValue;
END_RCPP
}
// is_mem_attached
bool is_mem_attached(Rcpp::XPtr<Memory> mem);
RcppExport SEXP _rmada_is_mem_attached(SEXP memSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::XPtr<Memory> >::type mem(memSEXP);
    rcpp_result_gen = Rcpp::wrap(is_mem_attached(mem));
    return rcpp_result_gen;
END_RCPP
}
// get_mem_address
SEXP get_mem_address(Rcpp::XPtr<Memory> mem, std::size_t data_type);
RcppExport SEXP _rmada_get_mem_address(SEXP memSEXP, SEXP data_typeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::XPtr<Memory> >::type mem(memSEXP);
    Rcpp::traits::input_parameter< std::size_t >::type data_type(data_typeSEXP);
    rcpp_result_gen = Rcpp::wrap(get_mem_address(mem, data_type));
    return rcpp_result_gen;
END_RCPP
}
// get_mem_length
std::size_t get_mem_length(Rcpp::XPtr<Memory> mem, std::size_t data_type);
RcppExport SEXP _rmada_get_mem_length(SEXP memSEXP, SEXP data_typeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::XPtr<Memory> >::type mem(memSEXP);
    Rcpp::traits::input_parameter< std::size_t >::type data_type(data_typeSEXP);
    rcpp_result_gen = Rcpp::wrap(get_mem_length(mem, data_type));
    return rcpp_result_gen;
END_RCPP
}
// get_mem_id
std::string get_mem_id(Rcpp::XPtr<Memory> mem);
RcppExport SEXP _rmada_get_mem_id(SEXP memSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::XPtr<Memory> >::type mem(memSEXP);
    rcpp_result_gen = Rcpp::wrap(get_mem_id(mem));
    return rcpp_result_gen;
END_RCPP
}
// mem_remove
void mem_remove(Rcpp::XPtr<Memory> mem);
RcppExport SEXP _rmada_mem_remove(SEXP memSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::XPtr<Memory> >::type mem(memSEXP);
    mem_remove(mem);
    return R_NilValue;
END_RCPP
}
// mem_resize
void mem_resize(Rcpp::XPtr<Memory> mem, std::size_t n_elem, std::size_t data_type);
RcppExport SEXP _rmada_mem_resize(SEXP memSEXP, SEXP n_elemSEXP, SEXP data_typeSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::XPtr<Memory> >::type mem(memSEXP);
    Rcpp::traits::input_parameter< std::size_t >::type n_elem(n_elemSEXP);
    Rcpp::traits::input_parameter< std::size_t >::type data_type(data_typeSEXP);
    mem_resize(mem, n_elem, data_type);
    return R_NilValue;
END_RCPP
}

RcppExport SEXP run_testthat_tests();

static const R_CallMethodDef CallEntries[] = {
    {"_rmada_mat_init", (DL_FUNC) &_rmada_mat_init, 4},
    {"_rmada_n_rows", (DL_FUNC) &_rmada_n_rows, 1},
    {"_rmada_n_cols", (DL_FUNC) &_rmada_n_cols, 1},
    {"_rmada_mem_init", (DL_FUNC) &_rmada_mem_init, 4},
    {"_rmada_mem_attach", (DL_FUNC) &_rmada_mem_attach, 1},
    {"_rmada_mem_detach", (DL_FUNC) &_rmada_mem_detach, 1},
    {"_rmada_is_mem_attached", (DL_FUNC) &_rmada_is_mem_attached, 1},
    {"_rmada_get_mem_address", (DL_FUNC) &_rmada_get_mem_address, 2},
    {"_rmada_get_mem_length", (DL_FUNC) &_rmada_get_mem_length, 2},
    {"_rmada_get_mem_id", (DL_FUNC) &_rmada_get_mem_id, 1},
    {"_rmada_mem_remove", (DL_FUNC) &_rmada_mem_remove, 1},
    {"_rmada_mem_resize", (DL_FUNC) &_rmada_mem_resize, 3},
    {"run_testthat_tests", (DL_FUNC) &run_testthat_tests, 0},
    {NULL, NULL, 0}
};

RcppExport void R_init_rmada(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}

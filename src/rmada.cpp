
#include <RcppArmadillo.h>

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess;

// [[Rcpp::export]]
void createFile(arma::uword nrow, arma::uword ncol, std::string fileName) {

  try {

    std::filebuf fbuf;
    fbuf.open(fileName.c_str(), std::ios_base::out | std::ios_base::binary);
    fbuf.pubseekpos(nrow * ncol * sizeof(double) - 1); fbuf.sputc(0);
    fbuf.close();

  } catch(std::exception& ex) {

    throw std::runtime_error("Problem creating the backing file.");
  }
}

// [[Rcpp::export]]
SEXP mapFile(std::string fileName) {

  try {

    file_mapping file_map(fileName.c_str(), read_write);
    mapped_region *map = new mapped_region(file_map, read_write);
    Rcpp::XPtr<mapped_region> ret(map, true);
    return ret;

  } catch(interprocess_exception& e) {

    throw std::runtime_error("File '" + fileName + "' not found.");
  }
}

// [[Rcpp::export]]
SEXP createMat(SEXP memory, arma::uword nrow, arma::uword ncol) {

  Rcpp::XPtr<mapped_region> map(memory);
  double *ptr = static_cast<double *>(map->get_address());
  arma::mat *mat = new arma::mat(ptr, nrow, ncol);
  Rcpp::XPtr<arma::mat> ret(mat, true);
  return ret;
}

// [[Rcpp::export]]
arma::uword nRows(SEXP x) {
  Rcpp::XPtr<arma::mat> p(x);
  return p->n_rows;
}

// [[Rcpp::export]]
arma::uword nCols(SEXP x) {
  Rcpp::XPtr<arma::mat> p(x);
  return p->n_cols;
}


#' @useDynLib rmada, .registration = TRUE
#' @import methods Rcpp
#' @importFrom assertthat assert_that is.count is.string

# This dummy function definition is included with the package to ensure that
# 'tools::package_native_routine_registration_skeleton()' generates the
# required registration info for the 'run_testthat_tests' symbol.
(function() {
  .Call("run_testthat_tests", PACKAGE = "rmada")
})

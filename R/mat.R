
#' Some rando docs
#' @export
mat <- R6::R6Class(

  "mat",

  inherit = memory,

  public = list(

    initialize = function(n_rows, n_cols, ...) {

      assert_that(is.count(n_rows), is.count(n_cols))

      private$nrow <- n_rows
      private$ncol <- n_cols

      super$initialize(n_rows * n_cols, ...)
      private$init_mat()
    }
  ),

  active = list(

    mat_ptr = function() {

      if (identical(methods::new("externalptr"), private$mat)) {
        private$init_mat()
      }

      private$mat
    },

    n_rows = function() {
      assert_that(private$nrow == n_rows(self$mat_ptr))
      private$nrow
    },

    n_cols = function() {
      assert_that(private$ncol == n_cols(self$mat_ptr))
      private$ncol
    },

    n_elem = function() {
      res <- private$ncol * private$nrow
      assert_that(res == n_elem(self$mat_ptr),
                  res == super$length)
      res
    }
  ),

  private = list(

    nrow = NULL,
    ncol = NULL,

    mat = NULL,

    init_mat = function() {
      private$mat <- mat_init(super$mem_ptr, private$nrow, private$ncol,
                              private$dtyp)
      invisible(self)
    }
  )
)

#' @export
dim.mat <- function(x) {
  c(x$n_rows, x$n_cols)
}

#' @export
length.mat <- function(x) {
  x$n_elem
}

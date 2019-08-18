
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
    },

    fill = function(how = 0) {
      fill_object(self$mat_ptr, how)
      invisible(self)
    },

    elem = function(i, j) {
      assert_that(is.count(i), is.count(j))
      mat_extract_elem(self$mat_ptr, i, j)
    },

    col = function(j, first_row, last_row) {
      assert_that(is.count(j), missing(first_row) == missing(last_row))
      if (missing(first_row)) {
        mat_extract_col(self$mat_ptr, j)
      } else {
        mat_extract_subcol(self$mat_ptr, j, first_row, last_row)
      }
    },

    row = function(i, first_col, last_col) {
      assert_that(is.count(i), missing(first_col) == missing(last_col))
      if (missing(first_col)) {
        mat_extract_row(self$mat_ptr, i)
      } else {
        mat_extract_subrow(self$mat_ptr, i, first_col, last_col)
      }
    },

    cols = function(j, last_col) {
      if (missing(last_col)) {
        mat_extract_nccols(self$mat_ptr, sanitize_index(j))
      } else {
        assert_that(is.count(j), is.count(last_col))
        mat_extract_cols(self$mat_ptr, j, last_col)
      }
    },

    rows = function(i, last_row) {
      if (missing(last_row)) {
        mat_extract_ncrows(self$mat_ptr, sanitize_index(i))
      } else {
        assert_that(is.count(i), is.count(last_row))
        mat_extract_rows(self$mat_ptr, i, last_row)
      }
    },

    submat = function(i, j, last_row, last_col) {
      assert_that(missing(last_row) == missing(last_col))
      if (missing(last_row)) {
        mat_extract_ncsubmat(self$mat_ptr, sanitize_index(i),
                             sanitize_index(j))
      } else {
        assert_that(is.count(i), is.count(last_row),
                    is.count(j), is.count(last_col))
        mat_extract_submat(self$mat_ptr, i, j, last_row, last_col)
      }
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
dim.mat <- function(x, ...) {
  c(x$n_rows, x$n_cols)
}

#' @export
length.mat <- function(x, ...) {
  x$n_elem
}

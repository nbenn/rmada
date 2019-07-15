
#' Some rando docs
#' @export
mat <- R6::R6Class(

  "mat",

  public = list(

    initialize = function(nrow, ncol, file_name = tempfile()) {

      assert_that(is.count(nrow), is.count(ncol), is.string(file_name))

      private$p_file_name <- file_name
      private$p_nrow <- nrow
      private$p_ncol <- ncol

      if (!file.exists(file_name)) {
        createFile(nrow, ncol, private$p_file_name)
      }

      private$p_mem_ptr <- mapFile(private$p_file_name)
      private$p_obj_ptr <- createMat(private$p_mem_ptr, nrow, ncol)
    }
  ),

  active = list(

    nrow = function() {
      assert_that(private$p_nrow == nRows(private$p_obj_ptr))
      private$p_nrow
    },

    ncol = function() {
      assert_that(private$p_ncol == nCols(private$p_obj_ptr))
      private$p_ncol
    },

    mem_ptr = function(value) {

      assert_that(missing(value))

      if (identical(private$p_mem_ptr, methods::new("externalptr"))) {
        private$p_mem_ptr <- mapFile(private$p_file_name)
      }

      private$p_mem_ptr
    },

    obj_ptr = function(value) {

      assert_that(missing(value))

      if (identical(private$p_obj_ptr, methods::new("externalptr"))) {
        private$p_obj_ptr <- createMat(self$mem_ptr, private$p_nrow,
                                     private$p_ncol)
      }

      private$p_obj_ptr
    }
  ),

  private = list(
    p_file_name = NULL,
    p_mem_ptr = NULL,
    p_obj_ptr = NULL,
    p_nrow = NULL,
    p_ncol = NULL
  )
)

#' @export
dim.mat <- function(x) {
  c(x$nrow, x$ncol)
}

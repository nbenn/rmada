
#' @export
mat <- R6::R6Class("mat",
  public = list(
    initialize = function(nrow, ncol, init = NULL, file_name = tempfile()) {
      assert_that(is.count(nrow), is.count(ncol))
      private$file_name <- file_name
      if (!file.exists(file_name)) {
        createFile(nrow, ncol, private$file_name)
      }
      private$mem_ptr <- mapFile(private$file_name)
      private$obj_ptr <- createMat(private$mem_ptr, nrow, ncol)
    },
    nrow = function() nRows(private$obj_ptr),
    ncol = function() nCols(private$obj_ptr)
  ),
  active = list(
    data = function(value) {

    }
  ),
  private = list(
    file_name = NULL,
    mem_ptr = NULL,
    obj_ptr = NULL
  )
)

#' @export
dim.mat <- function(x) {
  c(x$nrow(), x$ncol())
}
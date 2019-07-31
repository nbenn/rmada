
#' Some rando docs
#' @export
obj <- R6::R6Class(

  "obj",

  public = list(

    initialize = function(length, id = rand_name(mode = mem_type),
                          data_type = 8L, mem_type = "SharedMemory") {

      assert_that(is.count(length), is.string(id),
                  is.count(data_type), is.string(mem_type))

      private$leng <- length
      private$name <- id
      private$dtyp <- data_type
      private$mtyp <- mem_type

      private$init()
    },

    attach = function() {
      mem_attach(self$obj_ptr)
      invisible(self)
    },

    detach = function() {
      mem_detach(self$obj_ptr)
      invisible(self)
    },

    resize = function(new_length) {

      assert_that(
        is.integer(new_length), length(new_length) == 1L, new_length > 0L
      )

      private$leng <- new_length
      mem_resize(self$obj_ptr, new_length, private$dtyp)

      invisible(self)
    }
  ),

  active = list(

    obj_ptr = function() {

      if (identical(methods::new("externalptr"), private$memory)) {
        private$init()
      }

      private$memory
    },

    data_ptr = function() get_mem_address(self$obj_ptr, private$dtyp),

    is_attached = function() is_mem_attached(self$obj_ptr),

    length = function() {

      assert_that(
        get_mem_length(self$obj_ptr, private$dtyp) == private$leng
      )

      private$leng
    },

    id = function() {

      assert_that(get_mem_id(self$obj_ptr) == private$name)

      private$name
    },

    data_type = function() private$dtyp,
    mem_type = function() private$mtyp
  ),

  private = list(

    leng = NULL,
    name = NULL,
    dtyp = NULL,
    mtyp = NULL,

    memory = NULL,

    init = function() {
      private$memory <- init_mem(private$name, private$leng, private$dtyp,
                                 private$mtyp)
      invisible(self)
    },

    finalize = function() mem_remove(self$obj_ptr)
  )
)

rand_name <- function(mode = "SharedMemory", length = 10L,
                      alphabet = c(LETTERS, letters, 0L:9L)) {

  assert_that(is.string(mode), is.count(length),
              is.character(alphabet), length(alphabet) > 0L)

  name <- paste(sample(alphabet, length, replace = TRUE), collapse = "")

  if (mode == "FileMemory") {
    file.path(tempdir(), name)
  } else {
    name
  }
}

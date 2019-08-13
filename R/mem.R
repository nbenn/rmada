
#' Some rando docs
#' @export
memory <- R6::R6Class(

  "memory",

  public = list(

    initialize = function(length, id = rand_name(mode = mem_type),
                          data_type = "double", mem_type = "SharedMemory") {

      assert_that(is.count(length), is.string(id),
                  is.count(data_type) || is.string(data_type),
                  is.count(mem_type) || is.string(mem_type))

      private$leng <- length
      private$name <- id
      private$dtyp <- resolve_type(data_type, list_num_types())
      private$mtyp <- resolve_type(mem_type, list_mem_types())

      private$init_mem()
    },

    attach = function() {
      mem_attach(self$mem_ptr)
      invisible(self)
    },

    detach = function() {
      mem_detach(self$mem_ptr)
      invisible(self)
    },

    resize = function(new_length) {

      assert_that(
        is.integer(new_length), length(new_length) == 1L, new_length > 0L
      )

      private$leng <- new_length
      mem_resize(self$mem_ptr, new_length, private$dtyp)

      invisible(self)
    }
  ),

  active = list(

    mem_ptr = function() {

      if (identical(methods::new("externalptr"), private$memory)) {
        private$init_mem()
      }

      private$memory
    },

    data_ptr = function() get_mem_address(self$mem_ptr, private$dtyp),

    is_attached = function() is_mem_attached(self$mem_ptr),

    length = function() {

      assert_that(
        get_mem_length(self$mem_ptr, private$dtyp) == private$leng
      )

      private$leng
    },

    id = function() {

      assert_that(get_mem_id(self$mem_ptr) == private$name)

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

    init_mem = function() {
      private$memory <- mem_init(private$name, private$leng, private$dtyp,
                                 private$mtyp)
      invisible(self)
    },

    finalize = function() mem_remove(self$mem_ptr)
  )
)

resolve_type <- function(type, type_list) {

  assert_that(length(type) == 1L,
              is.character(type_list), length(type_list) > 0L)

  if (is.character(type)) {
    type <- charmatch(type, type_list, nomatch = 0L)
  }

  assert_that(is.count(type), type <= length(type_list))

  type - 1L
}

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

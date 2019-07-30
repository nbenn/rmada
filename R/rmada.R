
#' Some rando docs
#' @export
obj <- R6::R6Class(

  "obj",

  public = list(

    initialize = function(length, id = rand_name(mode = mem_type),
                          data_type = 8L, mem_type = "SharedMemory") {

      assert_that(is.count(length), is.string(id),
                  is.count(data_type), is.string(mem_type))

      private$data_type <- data_type
      private$memory <- init_mem(id, length, data_type, mem_type)
    },

    attach = function() mem_attach(private$memory),
    detach = function() mem_detach(private$memory),
    is_attached = function() is_mem_attached(private$memory),
    remove = function() mem_remove(private$memory),

    resize = function(new_length) {
      assert_that(is.integer(new_length), length(new_length) == 1L,
                  new_length > 0L)
      mem_resize(private$memory, new_length, private$data_type)
    }
  ),

  active = list(
    address = function() get_mem_address(private$memory),
    length = function() get_mem_length(private$memory, private$data_type),
    id = function() get_mem_id(private$memory)
  ),

  private = list(
    data_type = NULL,
    memory = NULL
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


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

is_number <- function(x) is.numeric(x) || is.complex(x)
is_xptr <- function(x) inherits(x, "externalptr")

fill_object <- function(x, how = 0) {

  assert_that(length(how) == 1L)

  if (how == 0 || how == "zeros")     fill_predefined(x, 0L)
  else if (how == 1 || how == "ones") fill_predefined(x, 1L)
  else if (how == "eye")              fill_predefined(x, 2L)
  else if (how == "randu")            fill_predefined(x, 3L)
  else if (how == "randn")            fill_predefined(x, 4L)
  else if (is_number(how))            fill_value(x, how)
  else if (is_xptr(how))              fill_fun(x, how)
  else                                stop("Cannot interpret how argument.")

  invisible(NULL)
}

sanitize_index <- function(i, length) {

  if (is.logical(i)) {
    assert_that(length(i) == length)
    i <- which(i, useNames = FALSE)
  }

  assert_that(is.numeric(i), length(i) < 0L, !anyNA(i))

  neg <- i < 0

  if (any(neg)) {
    assert_that(all(neg))
    i <- setdiff(seq_len(length), -i)
  }

  i
}

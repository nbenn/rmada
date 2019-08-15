
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

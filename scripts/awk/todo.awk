#!/usr/bin/awk -f

# Prints todo comments in beautiful way
# Use grep first to get todo comments

BEGIN {
  FS = ":"

  longest_file = 0
  longest_line = 0
}

{
  # Add file name, line and comment into arrays
  file[NR - 1] = $1
  line[NR - 1] = $2
  comm[NR - 1] = $4

  # Set longest file name
  i = length(file[NR - 1])
  if (i > longest_file) longest_file = i;

  # Set longest line
  i = length(line[NR - 1])
  if (i > longest_line) longest_line = i;

  # Remove trailing space at comment start
  sub(/^ /, "", comm[NR - 1])
}

END {
  for (i = 0; i < NR; i++)
    printf "%-" longest_file "s:\x1B[36m%*s\x1B[0m: %s\n",
      file[i], longest_line, line[i], comm[i]
}

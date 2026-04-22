*This project has been created as part of the 42 curriculum by pkostura.*

# get_next_line

## Description
`get_next_line` is a C function that reads and returns one line at a time from a file descriptor.
The goal is to build a reusable line reader that works with repeated calls, handles partial reads, and manages memory safely.

In practice, this project focuses on:
- file descriptor I/O with `read`
- persistent state between function calls
- dynamic memory allocation and cleanup
- edge-case handling (EOF, empty files, invalid fd, long lines, newline/no-newline endings)

## Features
- Returns exactly one line per call.
- Includes the trailing newline (`\n`) when present.
- Returns the last line correctly even if it does not end with `\n`.
- Returns `NULL` on end of input or on error.
- Uses `BUFFER_SIZE` to control read chunk size.

## Detailed Algorithm And Justification
The implementation uses a persistent buffer (stash) that stores unread bytes between calls.
This is necessary because a single `read` call may return:
- less than one full logical line, or
- multiple lines at once.

### Chosen approach
1. Keep a static stash (`static_buffer`) across calls.
2. On each `get_next_line(fd)` call, read from `fd` and append chunks until:
- a newline exists in stash, or
- EOF is reached.
3. Extract exactly one line from the start of stash:
- copy characters up to `\n` (inclusive if present),
- null-terminate the returned string.
4. Remove the extracted part from stash and keep only the remainder for the next call.
5. If stash becomes empty at EOF, free it and return `NULL` on subsequent calls.

### Why this algorithm is appropriate
- Correctness: It preserves unread data, so no bytes are lost between calls.
- Efficiency: It reads in chunks instead of one byte at a time.
- Robustness: It handles lines larger than `BUFFER_SIZE` by concatenating multiple reads.
- Memory safety model: Every allocated temporary buffer is either transferred to stash, joined and freed, or explicitly freed on error/EOF paths.

### Complexity discussion
Let $n$ be the number of bytes consumed to produce one returned line.
- Time complexity: $O(n)$ per produced line (plus append overhead).
- Space complexity: $O(n)$ for stash + returned line.

This tradeoff is acceptable for the project constraints because persistent buffering is mandatory to avoid data loss across calls.

## Technical Choices
- Language: C
- API used: `read`, `malloc`, `free`
- Persistent state: static pointer stash
- String helpers: custom `ft_strlen`, `ft_strchr`, `ft_strlcpy`, `ft_strlcat`, `ft_strjoin_free`

## Instructions
### Compilation (mandatory files)
From the project root:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o gnl
```

You can change `BUFFER_SIZE`:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1 main.c get_next_line.c get_next_line_utils.c -o gnl_bs1
```

### Execution
Read from a file:

```bash
./gnl get_next_line.c
```

Read from standard input:

```bash
./gnl
```

Type lines and finish with `Ctrl+D`.

## Usage Example
```c
int fd = open("text.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

## Resources
Classic references used for this topic:
- Linux man pages:
  - `man 2 read`
  - `man 2 open`
  - `man 3 malloc`
  - `man 3 free`

### AI usage disclosure
AI assistance was used for:
- reviewing crash causes and memory-management bugs,
- suggesting refactoring of line extraction and stash update logic,
- helping draft and structure this README.
- norminette compliance


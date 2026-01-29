// #include <fcntl.h>
// #include <stddef.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/stat.h>
// #include <sys/types.h>
// #include <unistd.h>

// #define _STDIO_SEEKABLE 0x01
// #define _STDIO_QLIB_BUF 0x02
// #define _STDIO_READ_BUF 0x04
// #define _STDIO_WRITE_BUF 0x08

// #define CREATE_FILE_DEF_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

// FILE *__STDIN_SP = NULL;
// FILE *__STDOUT_SP = NULL;
// FILE *__STDERR_SP = NULL;

// __attribute__((constructor)) static void __stdio_init__(void) {
//   static FILE __stdin_stream = {.fd = STDIN_FILENO,
//                                 .oflags = O_RDONLY,
//                                 .flags = 0,
//                                 .error = 0,
//                                 .eof = 0,
//                                 .offset = 0};
//   static FILE __stdout_stream = {.fd = STDOUT_FILENO,
//                                  .oflags = O_WRONLY,
//                                  .flags = 0,
//                                  .error = 0,
//                                  .eof = 0,
//                                  .offset = 0};
//   static FILE __stderr_stream = {.fd = STDERR_FILENO,
//                                  .oflags = O_WRONLY,
//                                  .flags = 0,
//                                  .error = 0,
//                                  .eof = 0,
//                                  .offset = 0};
//   // check whether the streams are seekable or through redirection
//   struct stat st;
//   if (fstat(STDIN_FILENO, &st) == 0 &&
//       (S_ISREG((st.st_mode)) || S_ISBLK((st.st_mode)))) {
//     __stdin_stream.flags |= _STDIO_SEEKABLE;
//   }
//   if (fstat(STDOUT_FILENO, &st) == 0 &&
//       (S_ISREG((st.st_mode)) || S_ISBLK((st.st_mode)))) {
//     __stdout_stream.flags |= _STDIO_SEEKABLE;
//   }
//   if (fstat(STDERR_FILENO, &st) == 0 &&
//       (S_ISREG((st.st_mode)) || S_ISBLK((st.st_mode)))) {
//     __stderr_stream.flags |= _STDIO_SEEKABLE;
//   }
//   __STDIN_SP = &__stdin_stream;
//   __STDOUT_SP = &__stdout_stream;
//   __STDERR_SP = &__stderr_stream;
// }

// FILE *fopen(const char *restrict filename, const char *restrict mode) {
//   int flags = 0;
//   struct stat st;
//   int fd;
//   // basic mode
//   switch (mode[0]) {
//   case 'r':
//     flags |= O_RDONLY;
//     break;
//   case 'w':
//     flags |= O_WRONLY | O_CREAT | O_TRUNC;
//     break;
//   case 'a':
//     flags |= O_WRONLY | O_CREAT | O_APPEND;
//     break;
//   default:
//     return NULL;
//   }
//   // extended mode
//   for (size_t i = 1; mode[i]; ++i) {
//     if (mode[i] == '+') {
//       flags = (flags & ~O_ACCMODE) | O_RDWR;
//       break;
//     }
//     if (mode[i] != 'b')
//       return NULL;
//   }
//   fd = open(filename, flags, CREATE_FILE_DEF_MODE);
//   if (fd == -1) {
//     return NULL;
//   }
//   FILE *stream = (FILE *)malloc(sizeof(FILE));
//   if (!stream) {
//     close(fd);
//     return NULL;
//   }
//   memset(stream, 0, sizeof(FILE));
//   stream->buf = (unsigned char *)malloc(BUFSIZ);
//   if (!stream->buf) {
//     close(fd);
//     free(stream);
//     return NULL;
//   }
//   stream->bufsz = BUFSIZ;
//   stream->bufmode = _IOFBF;
//   stream->flags |= _STDIO_QLIB_BUF;
//   stream->fd = fd;
//   stream->oflags = flags;
//   if (fstat(fd, &st) == 0 && (S_ISREG((st.st_mode)) ||
//   S_ISBLK((st.st_mode)))) {
//     stream->flags |= _STDIO_SEEKABLE;
//   }
//   return stream;
// }

// int fclose(FILE *stream) {
//   if (stream && stream->flags & _STDIO_QLIB_BUF) {
//     free(stream->buf);
//   }
//   int fd = stream->fd;
//   free(stream);
//   return close(fd);
// }

// /*
//  * Based on ANSI C standard: fread does not distinguish between
//  * end-of-file and error, and callers must use feof and ferror to determine
//  * which occurred.
//  *
//  * So the fread will not add sanity check for these.
//  */
// size_t fread(void *restrict buffer, size_t size, size_t count,
//              FILE *restrict stream) {
//   if (!size || !count) {
//     return 0;
//   }
//   ssize_t nbytes = read(stream->fd, buffer, size * count);
//   if (nbytes == -1) {
//     stream->error = 1;
//     return 0;
//   }
//   if (nbytes == 0)
//     stream->eof = 1;

//   stream->offset += nbytes;
//   return (nbytes == (ssize_t)(size * count)) ? count : (nbytes / size);
// }

// size_t fwrite(const void *restrict buffer, size_t size, size_t count,
//               FILE *restrict stream) {
//   if (!size || !count) {
//     return 0;
//   }
//   ssize_t nbytes = write(stream->fd, buffer, size * count);
//   if (nbytes == -1) {
//     stream->error = 1;
//     return 0;
//   }
//   stream->offset += nbytes;
//   return (nbytes == (ssize_t)(size * count)) ? count : (nbytes / size);
// }

// long ftell(FILE *stream) {
//   if (!stream || !(stream->flags & _STDIO_SEEKABLE)) {
//     if (stream)
//       stream->error = 1;
//     return -1L;
//   }
//   return stream->offset;
// }
// int fseek(FILE *stream, long offset, int origin) {
//   /* TODO: implement later since needs buffer modification support*/
//   return 0;
// }
// void clearerr(FILE *stream) {
//   stream->error = 0;
//   stream->eof = 0;
// }
// int feof(FILE *stream) { return stream->eof; }
// int ferror(FILE *stream) { return stream->error; }
// int fgetc(FILE *stream) {
//   unsigned char ch;
//   if (fread(&ch, 1, 1, stream) != 1) {
//     return EOF;
//   }
//   return ch;
// }
// int getc(FILE *stream) { return fgetc(stream); }
// int fputc(int ch, FILE *stream) {
//   unsigned char c = (unsigned char)ch;
//   if (fwrite(&c, 1, 1, stream) != 1) {
//     return EOF;
//   }
//   return ch;
// }
// int putc(int ch, FILE *stream) { return fputc(ch, stream); }
// int getchar() { return fgetc(__STDIN_SP); }
// int putchar(int ch) { return fputc(ch, __STDOUT_SP); }
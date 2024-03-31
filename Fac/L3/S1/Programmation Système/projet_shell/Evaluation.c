#include "Evaluation.h"
#include "Shell.h"

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void cmd_simple(Expression *expr, int *shellStatus)
{

  pid_t child = fork();
  if (!child)
  {
    execvp(expr->argv[0], expr->argv);
    perror("execvp");
  }
  else
  {
    wait(&child);
    shellStatus = 0;
  }
}

void redirect(Expression *expr, int *shellStatus)
{
  if (expr->redirect.type == REDIR_OUT)
  {
    if (expr->redirect.fd == 1)
    {
      pid_t child = fork();
      if (!child)
      {
        int fd = open(expr->redirect.fileName, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        int fd_backup = dup(STDOUT_FILENO);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        evaluateExpr(expr->left);
        dup2(fd_backup, STDOUT_FILENO);
        close(fd_backup);
      }
      else
      {
        wait(&child);
        shellStatus = 0;
      }
    }
    else if (expr->redirect.fd == 2)
    {
      pid_t child = fork();
      if (!child)
      {
        int fd = open(expr->redirect.fileName, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        int fd_backup = dup(STDERR_FILENO);
        dup2(fd, STDERR_FILENO);
        close(fd);
        evaluateExpr(expr->left);
        dup2(fd_backup, STDERR_FILENO);
        close(fd_backup);
      }
      else
      {
        wait(&child);
        shellStatus = 0;
      }
    }
    else if (expr->redirect.fd == -1)
    {
      pid_t child = fork();
      if (!child)
      {
        int fd = open(expr->redirect.fileName, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        int fd_backup_out = dup(STDOUT_FILENO);
        int fd_backup_err = dup(STDERR_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        close(fd);
        evaluateExpr(expr->left);
        dup2(fd_backup_out, STDERR_FILENO);
        dup2(fd_backup_err, STDERR_FILENO);
        close(fd_backup_out);
        close(fd_backup_err);
      }
      else
      {
        wait(&child);
        shellStatus = 0;
      }
    }
  }
  else if (expr->redirect.type == REDIR_IN)
  {
    pid_t child = fork();
    if (!child)
    {
      int fd = open(expr->redirect.fileName, O_RDONLY);
      int fd_backup = dup(STDIN_FILENO);
      dup2(fd, STDIN_FILENO);
      close(fd);
      evaluateExpr(expr->left);
      dup2(fd_backup, STDIN_FILENO);
      close(fd_backup);
    }
    else
    {
      wait(&child);
      shellStatus = 0;
    }
  }
  else if (expr->redirect.type == REDIR_APP)
  {
    pid_t child = fork();
    if (!child)
    {
      int fd = open(expr->redirect.fileName, O_WRONLY | O_CREAT, 0666);
      lseek(fd, 0, SEEK_END);
      int fd_backup = dup(STDOUT_FILENO);
      dup2(fd, STDOUT_FILENO);
      close(fd);
      evaluateExpr(expr->left);
      dup2(fd_backup, STDOUT_FILENO);
      close(fd_backup);
    }
    else
    {
      wait(&child);
      shellStatus = 0;
    }
  }
}

int evaluateExpr(Expression *expr)
{
  static int first = 1;
  if (first)
  {
    // code d'initialisation
    first = 0;
  }

  switch (expr->type)
  {
  case ET_EMPTY:
    break;
  case ET_SIMPLE:
    cmd_simple(expr, &shellStatus);
    break;
  case ET_REDIRECT:
    redirect(expr, &shellStatus);
    break;
  default:
  {
    fprintf(stderr, "sorry, this shell is not yet implemented\n");
    shellStatus = 1;
    break;
  }
  }

  return shellStatus;
}

/*************************************************************************
 *
 *  Copyright (c) 2025 Karthi Srinivasan
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA  02110-1301, USA.
 *
 **************************************************************************
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <act/act.h>
#include <act/iter.h>
#include <act/passes.h>
// #include "engines.h"

static void usage(char *name)
{
  fprintf (stderr, "Usage: %s -p <proc> <actfile>\n", name);
  fprintf (stderr, "Options:\n");
  fprintf (stderr, " -h : help; display this message\n");
  fprintf (stderr, "\n");
  exit(1);
}

int main(int argc, char **argv)
{
  Act *a;
  char *proc;

  /* initialize ACT library */
  Act::Init(&argc, &argv);

  char *outfile = NULL;
  char *procname = NULL;

  int ch;
  while ((ch = getopt (argc, argv, "hp:o:")) != -1) {
    switch (ch) {
    case 'h':
      usage (argv[0]);
      break;

    case 'p':
      if (procname) {
	FREE (procname);
      }
      procname = Strdup (optarg);
      break;

    case 'o':
      if (outfile) {
	      FREE (outfile);
      }
      outfile = Strdup (optarg);
      break;
      
    default:
      usage (argv[0]);
      break;
    }
  }

  if (optind != argc - 1) {
    usage (argv[0]);
  }

  if (!procname) {
    fprintf (stderr, "Missing process name: use -p to specify it.\n");
    usage (argv[0]);
  }

  /* read in the ACT file */
  a = new Act(argv[optind]);

  /* expand it */
  a->Expand();

  config_read("starter.conf");

  /* find the process specified on the command line */
  Process *p = a->findProcess(procname, true);

  if (!p) {
    fatal_error("Could not find process `%s' in file `%s'", procname,
		argv[optind]);
  }

  if (!p->isExpanded()) {
    p = p->Expand (ActNamespace::Global(), p->CurScope(), 0, NULL);
  }
  Assert (p, "What?");

  ActDynamicPass *c2p = new ActDynamicPass (a, "starter", "libactstarterpass.so", "starter");

  if (!c2p || (c2p->loaded() == false)) {
    fatal_error ("Could not load dynamic pass!");
  }

  c2p->run(p);

  return 0;
}

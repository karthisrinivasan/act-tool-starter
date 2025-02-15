/*************************************************************************
 *
 *  Copyright (c) 2025 Karthi Srinivasan
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
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
#include "starter_pass.h"
#include <act/act.h>
#include <act/extmacro.h>
#include <act/iter.h>
#include <act/passes.h>

void starter_init (ActPass *ap)
{
    fprintf(stdout, "// running pass.....\n\n");
    ActDynamicPass *dp;
    dp = dynamic_cast <ActDynamicPass *> (ap);
    Assert (dp, "What?");

    /* add dependency to Booleanize */
    ActPass *b = dp->getAct()->pass_find ("booleanize");
    if (!b) {
        b = new ActBooleanizePass (dp->getAct());
    }
    dp->addDependency ("booleanize");
}

void starter_run (ActPass *ap, Process *p)
{
    fprintf(stdout, "// finishing up pass.....\n\n");
}

void *starter_proc (ActPass *ap, Process *p, int mode)
{
    fprintf (stdout, "// visiting process.....\n\n");
    p->Print(stdout);
    fprintf (stdout, "// done with process.....\n\n");
    return NULL;
}

/*
 * Emit structure refinement, if needed
 */
void *starter_data (ActPass *ap, Data *d, int mode)
{
    fprintf (stdout, "// visiting data.....\n\n");
    d->Print(stdout);
    return NULL;
}

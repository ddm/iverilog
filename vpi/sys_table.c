/*
 * Copyright (c) 1999 Stephen Williams (steve@icarus.com)
 *
 *    This source code is free software; you can redistribute it
 *    and/or modify it in source code form under the terms of the GNU
 *    General Public License as published by the Free Software
 *    Foundation; either version 2 of the License, or (at your option)
 *    any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */
#ifdef HAVE_CVS_IDENT
#ident "$Id: sys_table.c,v 1.19 2003/03/06 20:04:42 steve Exp $"
#endif

# include "config.h"
# include "vpi_user.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

extern void sys_finish_register();
extern void sys_deposit_register();
extern void sys_display_register();
extern void sys_plusargs_register();
extern void sys_random_register();
extern void sys_readmem_register();
extern void sys_time_register();
extern void sys_vcd_register();
extern void sys_lxt_register();
extern void sys_vcdoff_register();

static void sys_lxt_or_vcd_register()
{
      int idx;
      struct t_vpi_vlog_info vlog_info;

      char*dumper;

	/* Get the dumper of choice from the IVERILOG_DUMPER
	   environment variable. */
      dumper = getenv("IVERILOG_DUMPER");
      if (dumper) {
	    char*cp = strchr(dumper,'=');
	    if (cp != 0)
		  dumper = cp + 1;

      } else {
	    dumper = "vcd";
      }

	/* Scan the extended arguments, looking for flags that select
	   major features. This can override the environment variable
	   settings. */
      vpi_get_vlog_info(&vlog_info);

      for (idx = 0 ;  idx < vlog_info.argc ;  idx += 1) {

	    if (strcmp(vlog_info.argv[idx],"-lxt") == 0) {
		  dumper = "lxt";

	    } else if (strcmp(vlog_info.argv[idx],"-lxt-space") == 0) {
		  dumper = "lxt";

	    } else if (strcmp(vlog_info.argv[idx],"-lxt-speed") == 0) {
		  dumper = "lxt";

	    } else if (strcmp(vlog_info.argv[idx],"-lxt-none") == 0) {
		  dumper = "none";

	    } else if (strcmp(vlog_info.argv[idx],"-vcd") == 0) {
		  dumper = "vcd";

	    } else if (strcmp(vlog_info.argv[idx],"-vcd-off") == 0) {
		  dumper = "none";

	    } else if (strcmp(vlog_info.argv[idx],"-vcd-none") == 0) {
		  dumper = "none";

	    }
      }

      if (strcmp(dumper, "vcd") == 0)
	    sys_vcd_register();

      else if (strcmp(dumper, "VCD") == 0)
	    sys_vcd_register();

      else if (strcmp(dumper, "lxt") == 0)
	    sys_lxt_register();

      else if (strcmp(dumper, "LXT") == 0)
	    sys_lxt_register();

      else if (strcmp(dumper, "none") == 0)
	    sys_vcdoff_register();

      else if (strcmp(dumper, "NONE") == 0)
	    sys_vcdoff_register();

      else {
	    fprintf(stderr, "system.vpi: Unknown dumper format: %s\n",
		    dumper);
	    sys_vcd_register();
      }
}

void (*vlog_startup_routines[])() = {
      sys_finish_register,
      sys_deposit_register,
      sys_display_register,
      sys_plusargs_register,
      sys_random_register,
      sys_readmem_register,
      sys_time_register,
      sys_lxt_or_vcd_register,
      0
};


/*
 * $Log: sys_table.c,v $
 * Revision 1.19  2003/03/06 20:04:42  steve
 *  Add means to suppress wveform output
 *
 * Revision 1.18  2003/02/20 00:50:06  steve
 *  Update lxt_write implementation, and add compression control flags.
 *
 * Revision 1.17  2002/08/12 01:35:05  steve
 *  conditional ident string using autoconfig.
 *
 * Revision 1.16  2002/04/07 04:37:53  steve
 *  Add $plusargs system functions.
 *
 * Revision 1.15  2002/04/06 21:33:29  steve
 *  allow runtime selection of VCD vs LXT.
 *
 * Revision 1.14  2002/03/09 21:54:49  steve
 *  Add LXT dumper support. (Anthony Bybell)
 *
 * Revision 1.13  2001/09/30 16:45:10  steve
 *  Fix some Cygwin DLL handling. (Venkat Iyer)
 *
 * Revision 1.12  2001/07/25 03:10:50  steve
 *  Create a config.h.in file to hold all the config
 *  junk, and support gcc 3.0. (Stephan Boettcher)
 *
 * Revision 1.11  2001/05/22 02:14:47  steve
 *  Update the mingw build to not require cygwin files.
 *
 * Revision 1.10  2001/05/20 15:09:40  steve
 *  Mingw32 support (Venkat Iyer)
 *
 * Revision 1.9  2001/04/26 00:01:33  steve
 *  Support $deposit to a wire or reg.
 *
 * Revision 1.8  2000/12/14 23:36:34  steve
 *  include vpi_user.h.
 *
 * Revision 1.7  2000/11/01 03:19:36  steve
 *  Add the general $time system function.
 *
 * Revision 1.6  2000/09/30 03:20:47  steve
 *  Cygwin port changes from Venkat
 *
 * Revision 1.5  2000/05/04 03:37:59  steve
 *  Add infrastructure for system functions, move
 *  $time to that structure and add $random.
 *
 * Revision 1.4  2000/02/23 02:56:56  steve
 *  Macintosh compilers do not support ident.
 *
 * Revision 1.3  1999/12/15 04:01:14  steve
 *  Add the VPI implementation of $readmemh.
 *
 * Revision 1.2  1999/11/07 20:33:30  steve
 *  Add VCD output and related system tasks.
 *
 * Revision 1.1  1999/08/15 01:23:56  steve
 *  Convert vvm to implement system tasks with vpi.
 *
 */


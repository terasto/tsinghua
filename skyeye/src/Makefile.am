
SUBDIRS =  arch/arm/ arch/bfin arch/coldfire arch/mips arch/ppc/ arch/x86/ device/ utils/ arch/sparc/ libltdl common/

#AM_LDFLAGS = $(LIBLS) --start-group $(top_srcdir)/arch/arm/libarm.a $(top_srcdir)/arch/bfin/libbfin.a $(top_srcdir)/arch/coldfire/libcoldfire.a $(top_srcdir)/arch/mips/libmips.a $(top_srcdir)/arch/ppc/libppc.a $(top_srcdir)/device/libdev.a $(top_srcdir)/utils/libutils.a --end-group
#AM_LDFLAGS = $(LIBLS) -L$(top_srcdir)/arch/arm/ -L$(top_srcdir)/arch/bfin/ -L$(top_srcdir)/arch/coldfire/ -L$(top_srcdir)/arch/mips/ -L$(top_srcdir)/device/ -L$(top_srcdir)/utils/ --start-group  -larm -lbfin -lcoldfire  -lmips -L$(top_srcdir)/arch/ppc/ -lppc -ldev -lutils --end-group

#skyeye_LDADD =  -L$(top_srcdir)/common -lcommon -L$(top_srcdir)/third-party/bfd/.libs/ -lbfd
skyeye_LDADD =  -L$(top_srcdir)/common -lcommon
#skyeye_LDADD =  $(top_srcdir)/arch/arm/libarm.a $(top_srcdir)/device/libdev.a $(top_srcdir)/arch/mips/libmips.a $(top_srcdir)/arch/ppc/libppc.a $(top_srcdir)/arch/bfin/libbfin.a $(top_srcdir)/arch/mips/libmips.a $(top_srcdir)/arch/coldfire/libcoldfire.a $(top_srcdir)/arch/sparc/libsparc.a $(top_srcdir)/memory/libmemory.a $(top_srcdir)/third-party/bfd/libbfd.a $(top_srcdir)/third-party/libiberty/libiberty.a $(top_srcdir)/third-party/readline/libreadline.a

# workaround getopt issue on Cygwin platform
skyeye_LDADD += -lc 
# add curses library for ubentu system.
# skyeye_LDADD += -lncurses

# readline library need ncurses

# some functions in "libutils.a" which is required by other libs
#skyeye_LDADD += $(top_srcdir)/utils/libutils.a

skyeye_LDFLAGS =

INCLUDES = @COMMON_INCLUDES@ -Ithird-party/bfd/
DEFS = -DMODET -g -O2 -D_FILE_OFFSET_BITS=64 -DSTANDALONE -DDEFAULT_INLINE=0   
AM_CFLAGS = -W -Wall -Wstrict-prototypes -Wmissing-prototypes 
ACLOCAL_AMFLAGS=-I m4
bin_PROGRAMS = skyeye uart_instance mknandflashdump prof_convert

skyeye_SOURCES = utils/main/skyeye.c
uart_instance_SOURCES = utils/uart_console/uart_console.c
mknandflashdump_SOURCES = utils/nandflash_dump/mknandflashdump.c
prof_convert_SOURCES = utils/code_cov/prof_convert.c
if LCD
skyeye_LDADD += @LCD_LIBS@
endif

skyeye_gui:
	cd gui/qt4_src && rm -f skyeye_gui && make
	cp -f gui/qt4_src/skyeye-gui $(prefix)/bin/
lib:
	cd third-party/libiberty && ./configure --prefix=$(prefix) --enable-shared ;make;
	cd third-party/bfd/ && ./configure --prefix=$(prefix) --disable-werror --enable-shared --enable-targets=all;make;
	cd third-party/opcodes/ && ./configure --prefix=$(prefix) --disable-werror --enable-shared --enable-targets=all;make;
	cd third-party/readline/ && ./configure --prefix=$(prefix) --enable-shared;make;
build_lib:
	cd third-party/libiberty && make;
	cd third-party/bfd/ && make;
	cd third-party/opcodes/ && make;
	cd third-party/readline/ && make;
install_lib:
	cd third-party/libiberty && make install
	cd third-party/bfd/ && make install
	cd third-party/opcodes/ && make install
	cd third-party/readline/ && make install

clean_lib:
	cd third-party/libiberty && make distclean
	cd third-party/bfd/ && make distclean
	cd third-party/opcodes/ && make distclean
	cd third-party/readline/ && make distclean
install-data-hook:
	rm -f -r $(prefix)/testsuite && mkdir $(prefix)/testsuite
	cp -a $(top_srcdir)/testsuite/arm_hello $(prefix)/testsuite/arm_hello/
#	rm -f -r $(prefix)/conf && mkdir $(prefix)/conf
#	cp -a $(top_srcdir)/conf/* $(prefix)/conf

# workaround for bfd library. we need to reconfigure it.
all-local:
#	cd gui/qt4_src && $(MAKE) $(AM_MAKEFLAGS) all
#	cd third-party/bfd/ && ./configure --prefix=$(prefix) --disable-werror --enable-shared --enable-targets=all;make;
#	cd third-party/opcodes/ && ./configure --prefix=$(prefix) --disable-werror --enable-shared --enable-targets=all;make;make install
install-exec-local:
#	cd third-party/bfd/ && make install
#	cd third-party/opcodes/ && make install
